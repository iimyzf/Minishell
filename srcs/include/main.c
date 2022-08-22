/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/22 20:02:30 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process(char **cmd, char *path, t_data *data)
{
	pid_t	pid;

	pid = fork();

	if (pid == 0)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		ft_execve(cmd, data->env, path, data);	
	}
	else
	{
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		close(data->out);
	}
}

void	ft_parce(t_data *data)
{

	int		i;
	t_cmd	*temp;
	char	*tmp;
	char	*path;
	int		status;
	int		pid;
	int		status1;
	int		open_proce;
	int		saved_out;
	int		saved_in;
	int		j;

	tmp = "";
	fill_data_list(data);
	temp = (data)->cmd_list;
	if (!syntax_checker(temp))
		return;
	if (!check_heredoc(data))
		return ;
	temp = (data)->cmd_list;
	data->in = 0;
	data->out = 1;
	open_proce = 0;
	status1 = 0;
	saved_out = dup(STDOUT_FILENO);
	saved_in = dup(STDIN_FILENO);
	while (temp && (temp->id != -1))
	{
		i = 0;
		status = 0;
		j = 0; 
		tmp = "";
		data->full_cmd = calloc((cmd_parts_count(temp) + 1), sizeof(char *));
		while (temp->id != -1 && (temp->id != 8))
		{
			//fprintf(stderr ,"cmd = [%s] >>>>>> id = %d\n", temp->cmd, temp->id);
			if (temp->id == 4)
			{
				if (temp->next->id == 14)
					temp = temp->next;
				if (is_last_heredoc(temp))
				{
					dup2(temp->in, STDIN_FILENO);
					close (temp->in);
				}
				temp = temp->next;
			}
			else if(temp->id == 2)
			{
				temp = temp->next;
				if(temp->id == 14)
					temp = temp->next;
				pid = open(temp->cmd, O_RDWR | O_CREAT | O_TRUNC, 0777);
				if (pid < 0)
					return ;
				data->out = dup(pid);
				close(pid);
				status = 1;
			}
			else if(temp->id == 3)
			{
				temp = temp->next;
				if(temp->id == 14)
					temp = temp->next;
				pid = open(temp->cmd, O_RDWR | O_CREAT | O_APPEND , 0777);
				if (pid < 0)
					return ;
				data->out = dup(pid);
				close(pid);
				status = 1;
			}
			else if(temp->id == 1)
			{
				temp = temp->next;
				if(temp->id == 14)
					temp = temp->next;
				pid = open(temp->cmd, O_RDONLY);
				if (pid < 0)
					return ;
				dup2(pid, STDIN_FILENO);
				close (pid);
			}
			else if ((temp->id == 0 || temp->id == 6 || temp->id == 9 || temp->id == 7))
			{
				while (temp->id == 0 || temp->id == 6 || temp->id == 9 || temp->id == 7)
				{
					data->full_cmd[j] = ft_strjoin(data->full_cmd[j], temp->cmd);
					temp = temp->next;
				}
				j++;
			}
			if (temp->id != 1 && temp->id != 2 && temp->id != 3 && temp->id != 4 && temp->id != -1)
				temp = temp->next;
		}
		data->full_cmd[j] = NULL;
		i = 0;
		if (temp->id == 8)
		{
			pipe(data->fd); 
			if (status == 0)
				data->out = data->fd[1];
			data->in = data->fd[0];
			temp = temp->next;
			status1 = 2;
 		}
		else if (data->full_cmd[0] && is_buildin(data->full_cmd[0]) && temp->id == -1 && status1 != 2)
		{
			dup2(data->out, STDOUT_FILENO);
			if (!ft_strcmp(data->full_cmd[0], "pwd"))
				ft_pwd();
			else if (!ft_strcmp(data->full_cmd[0], "echo"))
				ft_echo(data->full_cmd);
			else if (!ft_strcmp(data->full_cmd[0], "env") && data->full_cmd[1] == NULL)
				ft_env(data->env);
			else if (!ft_strcmp(data->full_cmd[0], "export"))
				ft_export(&data->full_cmd[1], data);
			else if (!ft_strcmp(data->full_cmd[0], "unset"))
					ft_unset(data, data->full_cmd);
			else if (!ft_strcmp(data->full_cmd[0], "exit"))
					ft_exit(data);
			else if (!ft_strcmp(data->full_cmd[0], "cd"))
					ft_cd(data, data->full_cmd[1]);
			status1 = 1;
		}
		path = path_checker(data->full_cmd[0], data->env);
		if (data->full_cmd[0] && !path && !is_buildin(data->full_cmd[0]))
			printf("HA HA HA HA HA HA! d3iiiif !!\n");
		if (temp && temp->id == -1 && status == 0)
		{
			pipe(data->fd);
			if (status == 0)
				data->out = 1;
			data->in = data->fd[0];
		}
		if (data->full_cmd[0] != NULL && status1 != 1)
		{
			process(data->full_cmd, path, data);
			open_proce ++;
		}
		free(path);
		free_array(data->full_cmd);
	}
	t_cmd	*temp1;
	temp1 = data->cmd_list;
	while(open_proce > 0)
	{
		waitpid(-1, NULL, 0);
		open_proce --;
	}
		dup2(saved_out, STDOUT_FILENO);
		dup2(saved_in, STDIN_FILENO);
		close (saved_out);
		close (saved_in);
}

int main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (1);
	av[0] = "\033[0;33m\e[1mminishell-1.0$ \033[0m";
	data.env = env;
	data.in = 1;
	signal(SIGINT, sighandl);
	signal(SIGQUIT, sighandl);
	while (1)
	{
		data.input = readline(av[0]);
		if (!data.input)
			exit(0);
		if (data.input[0] && !unclosed_quotes(data.input))
		{
			//check_last(&data);
			add_history(data.input);
			ft_parce(&data);
		}
		free (data.input);
	}
	return (0);
}



/*  TO DO */

/*	
	# $cmd
	# path protect  --> doing
	# echo "hello">"gg"
	# remove split --> doing
	# << << error
	# complete isalnum
	# unclosed qoutes protectf
	# leaks handle
	# permissions
	# exit status
	# empty cmd handle
	# remove unused TOKENS
	# handel dollar sign in lexer
	# memory protections
	# errors handle
	# remove forbiden funcs like calloc
	# fix path checking (check from env)
	# signal should close heredoc --> done
	# $ sign protect --> done
	# grep not woking --> done
	# handel last pipewith no cmd --> done
	# handel error syntax (special carrachters with no options) --> done
	# exuce minishell in  minishell --> done
	# (ls | top) hang --> done
*/
