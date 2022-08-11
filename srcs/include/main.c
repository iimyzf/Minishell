/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/11 13:19:29 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process(char **cmd, char *path, t_data *data, int status)
{
	pid_t	pid;
	int kra;

	kra = status;
	kra = 0;
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
		dup2(data->in, STDIN_FILENO);
		close(data->fd[0]);
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

	tmp = "";
	fill_data_list(data);
	temp = (data)->cmd_list;
	if (!syntax_checker(temp))
		return;
	check_heredoc(data);
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
		tmp = "";
		while (temp->id != -1 && (temp->id != 8))
		{
			//printf("cmd = %s >>>>>> id = %d\n", temp->cmd, temp->id);
			if (temp->id == 9)
			{
				temp = temp->next;
				if (temp->id != -1 && temp->id != 6 && temp->id != 7)
				{
					dollar(data, &(temp->cmd), temp->id);
					while (temp->cmd && temp->cmd[i])
					{
						//write (1, "heee\n", 5);
						if (temp->cmd[i] == ' ')
							temp->cmd[i] = '	';
						i++;
					}
				}
			//	fprintf(stderr, "tmp->cmd = [%s]\n", temp->cmd);
			}	
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
				data->out = dup(pid);
				status = 1;
			}
			else if(temp->id == 3)
			{
				temp = temp->next;
				if(temp->id == 14)
					temp = temp->next;
				pid = open(temp->cmd, O_RDWR | O_CREAT | O_APPEND , 0777);
				data->out = dup(pid);
				status = 1;
			}
			else if(temp->id == 1)
			{
				temp = temp->next;
				if(temp->id == 14)
					temp = temp->next;
				pid = open(temp->cmd, O_RDONLY);
				dup2(pid, STDIN_FILENO);
				//close(pid);
			}
			else if (temp->id == 6 || temp->id == 7)
				tmp = ft_strjoin3(tmp, temp->cmd);
			else
				tmp = ft_strjoin2(tmp, temp->cmd);
			temp = temp->next;
			/*if (temp->id == 14)
				temp = temp->next;*/
		}
		//fprintf(stderr, "tmp = [%s]\n", tmp);
		data->full_cmd = ft_split(tmp, '	');
		free(tmp);
		i = 0;
		/*while (data->full_cmd[i])
		{
			fprintf(stderr, "cmd = [%s]\n", data->full_cmd[i]);
			i++;
		}*/
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
			//write (2, "heee\n", 5);
			if (!ft_strcmp(data->full_cmd[0], "pwd"))
				ft_pwd();
			else if (!ft_strcmp(data->full_cmd[0], "echo"))
				ft_echo(data->full_cmd);
			else if (!ft_strcmp(data->full_cmd[0], "env") && data->full_cmd[1] == NULL)
				ft_env(data->env);
			else if (!ft_strcmp(data->full_cmd[0], "export"))
				ft_export(&data->full_cmd[1], data);
			status1 = 1;
			//dup2(0, STDOUT_FILENO);
		}
		path = check_path(data->full_cmd[0]);
		//fprintf(stderr, "cmd = [%s]\n", path);
		//fprintf(stderr, "cmd = %s\n", data->full_cmd[0]);
		if (data->full_cmd[0] && !path && !is_buildin(data->full_cmd[0]))
			printf("HA HA HA HA HA HA! d3iiiif !!\n");
		if (temp && temp->id == -1 && status == 0)
		{
			//data->out = 1;
			pipe(data->fd);
			if (status == 0)
				data->out = 1;
			data->in = data->fd[0];
			//temp = temp->next;
			//status1 = 2;
		}
		/*if (temp->id == -1)
			break;*/
		if (data->full_cmd[0] != NULL && status1 != 1)
		{
			process(data->full_cmd, path, data, status);
			open_proce ++;
		}
		free(path);
		free_array(data->full_cmd);
		//close (pid);
	//	fprintf(stderr, "id = [%d]\n", temp->id);
	}
	t_cmd	*temp1;
	temp1 = data->cmd_list;
	while(open_proce > 0)
	{
		waitpid(-1, NULL, 0);
		//write (2, "\nhere\n", 6);
		open_proce --;
	}
	//fprintf(stderr, "stdin = %d\n", STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		dup2(saved_in, STDIN_FILENO);
		close (saved_out);
		close (saved_in);
		
	//fprintf(stderr, "stdin = %d\n", STDIN_FILENO);
}

int main(int ac, char **av, char **env)
{
	t_data	data;
	//int		pid;

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
		if (data.input[0])
		{
			//check_last(&data);
			if (!ft_strcmp(data.input, "exit"))
				break;
			add_history(data.input);
			ft_parce(&data);
		}
		free (data.input);
	}
	return (0);
}



/*  TO DO */

/*	# signal should close heredoc
	# $ sign protect --> doing
	# path protect
	# complete isalnum
	# unclosed qoutes protect
	# leaks handle
	# exit status
	# grep not woking
	# fix path checking (check from env)
	# handel last pipewith no cmd --> done
	# handel error syntax (special carrachters with no options) --> done
	# exuce minishell in  minishell --> done
	# (ls | top) hang --> done
*/
