/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/06/12 10:37:23 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	pid = fork();
	if (pid == 0)
	{
		if (status == 0)
			dup2(data->out, STDOUT_FILENO);
		else
			dup2(data->out, STDOUT_FILENO);
		ft_execve(cmd, NULL, path);
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
		pipe(data->fd);
		data->out = data->fd[1];
		data->in = data->fd[0];
		while (temp->id != -1 && (temp->id != 8))
		{
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
			else
				tmp = ft_strjoin2(tmp, temp->cmd);
			temp = temp->next;
		}
		if (temp && temp->id != -1)
			temp = temp->next;
		data->full_cmd = ft_split(tmp, ' ');
		path = check_path(data->full_cmd[0]);
		int j = -1;
		while (data->full_cmd[++j])
			fprintf (stdout ,"cmd = %s\n", data->full_cmd[j]);
		if (data->full_cmd[0] && !path && ft_strcmp(data->full_cmd[0], "<<"))
			printf("HA HA HA HA HA HA! d3iiiif !!\n");
		if (temp && temp->id == -1 && status == 0)
		{
			status = 1;
			data->out = 1;
		}
		if (data->full_cmd[0] != NULL)
			process(data->full_cmd, path, data, status);
		else
			dup2(data->in, STDIN_FILENO);
		free(path);
		usleep(300);
		free_array(data->full_cmd);
	}
	t_cmd	*temp1;
	temp1 = data->cmd_list;
	while(temp1->id != -1)
	{
		waitpid(-1, NULL, 0);
		temp1 = temp1->next;
	}
	exit (0);
}


int main(int ac, char **av, char **env)
{
	t_data	data;
	int		pid;

	if (ac != 1)
		return (1);
	av[0] = "minishell> ";
	data.env = env;
	free (data.full_cmd);
	data.in = 1;
	while (1)
	{
		data.input = readline(av[0]);
		if (data.input[0])
		{
			if (!ft_strcmp(data.input, "exit"))
				break;
			pid = fork();
			add_history(data.input);
			if (pid == 0)
				ft_parce(&data);
		}
		waitpid(pid, NULL, 0);
		free (data.input);
	}
	system("leaks minishell");
	return (0);
}
