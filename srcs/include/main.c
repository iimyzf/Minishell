/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/07/31 19:41:19 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void sighandl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig ==  SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	
}

void	free_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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
		ft_execve(cmd, data->env, path, data);
	}
	else
	{
		dup2(data->in, STDIN_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
	}
}

void	ft_parce(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;
	int		i;
	t_cmd	*temp;
	char	*tmp;
	char	*path;
	int 	status;
	int		pid;

	i = 0;
	tmp = "";
	lexer = lexer_init(data->input);
	(data)->cmd_list = NULL;
	while ((token = lexer_get_next_token(lexer)) != NULL)
	{
		if (!((data)->cmd_list))
			(data)->cmd_list = ft_lstnew(token->value, token->type);
		else
			lstadd_back(&(data)->cmd_list, ft_lstnew(token->value, token->type));
		free(token);
	}
	lstadd_back(&(data)->cmd_list, ft_lstnew("", -1));
	free(lexer);
	free (token);
	temp = (data)->cmd_list;
	if (temp->id == 8)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		exit(1);
	}
	while(temp && (temp->id != -1))
	{
		//write (1, "here\n", 5);
		while (temp->id != -1 && (temp->id != 8))
		{
			if (temp->id == 4)
			{
				if (is_last_heredoc(temp))
					pipe(data->here_fd);
				heredoc(temp->next->cmd, data, is_last_heredoc(temp));
				if (is_last_heredoc(temp))
					temp->in = data->here_fd[0];
				temp = temp->next;
			}
			temp = temp->next;
		}
		if (temp && temp->id != -1)
			temp = temp->next;
	}
	temp = (data)->cmd_list;
	while (temp && (temp->id != -1))
	{
		status = 0;
		tmp = "";
		while (temp->id != -1 && (temp->id != 8))
		{
		//printf("cmd = %s ID = %d\n", temp->cmd, temp->id);
			if (temp->id == 4)
			{
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
				pid = open(temp->cmd, O_RDWR | O_CREAT | O_TRUNC, 0777);
				data->out = dup(pid);
				status = 1;
			}
			else if(temp->id == 3)
			{
				temp = temp->next;
				pid = open(temp->cmd, O_RDWR | O_CREAT | O_APPEND , 0777);
				data->out = dup(pid);
				status = 1;
			}
			else if(temp->id == 1)
			{
				temp = temp->next;
				pid = open(temp->cmd, O_RDONLY);
				dup2(pid, STDIN_FILENO);
			}
			else
				tmp = ft_strjoin2(tmp, temp->cmd);
			temp = temp->next;
		}
		data->full_cmd = ft_split(tmp, '	');
		if (temp->id == 8)
		{
			pipe(data->fd);
			data->out = data->fd[1];
			data->in = data->fd[0];
			temp = temp->next;
		}
		else if (is_buildin(data->full_cmd[0]))
		{
			if (!ft_strcmp(data->full_cmd[0], "pwd"))
				ft_pwd();
			else if (!ft_strcmp(data->full_cmd[0], "echo"))
				ft_echo(data->full_cmd);
			else if (!ft_strcmp(data->full_cmd[0], "env") && data->full_cmd[1] == NULL)
				ft_env(data->env);
			else if (!ft_strcmp(data->full_cmd[0], "export"))
				ft_export(&data->full_cmd[1], data);
		}
		//fprintf (stdout ,"tmp = %s\n", tmp);
		path = check_path(data->full_cmd[0]);
		//int j = -1;
		/*while (data->full_cmd[++j])
			fprintf (stdout ,"cmd = %s\n", data->full_cmd[j]);*/
		if (data->full_cmd[0] && !path && !is_buildin(data->full_cmd[0]))
			printf("HA HA HA HA HA HA! d3iiiif !!\n");
		if (temp && temp->id == -1 && status == 0)
		{
			status = 1;
			data->out = 1;
		}
		if (data->full_cmd[0] != NULL && !is_buildin(data->full_cmd[0]))
			process(data->full_cmd, path, data, status);
		free(path);
		free_array(data->full_cmd);
	}
	t_cmd	*temp1;
	temp1 = data->cmd_list;
	while(temp1->id != -1)
	{
		waitpid(-1, NULL, 0);
		temp1 = temp1->next;
	}
	dup2(1, STDIN_FILENO);
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
			if (!ft_strcmp(data.input, "exit"))
				break;
			add_history(data.input);
			ft_parce(&data);
		}
		free (data.input);
	}
	//system("leaks minishell");
	return (0);
}