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

void	process(char **cmd, char *path, t_data *data)
{
	pid_t	pid;
	//int		fd[2];

	pid = fork();
	if (pid == 0)
	{
		close(data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO); //dup2 copies the content of its arg 2 to its arg 1!
		//dup2(fd[1], STDOUT_FILENO); //dup2 copies the content of its arg 2 to its arg 1!
		execve(path, cmd, NULL);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	/*else
	{
		dup2(data->fd[0], STDIN_FILENO);
		// write (1, "here1\n", 6);
		close(data->fd[1]);
		waitpid(pid, NULL, 0);
		// write (1, "here2\n", 6);
	}*/
}

void	ft_parce(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;
	int		i;
	t_cmd	*temp;
	char	*tmp;
	char	*path;

	i = 0;
	tmp = "";
	pipe(data->fd);
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
	temp = (data)->cmd_list;
	while (temp && (temp->id != -1))
	{
		while (temp->id != -1 && (temp->id != 8))
		{
			tmp = ft_strjoin2(tmp, temp->cmd);
			temp = temp->next;
		}
		if (temp && temp->id != -1)
			temp = temp->next;
		data->full_cmd = ft_split(tmp, ' ');
		tmp = "";
		path = check_path(data->full_cmd[0]);
		if (temp && temp->id == -1)
			break;
		process(data->full_cmd, path, data);
		//free(path);
		free_array(data->full_cmd);
	}
	close(data->fd[1]);
	dup2(data->fd[0], STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	//path = check_path(data->full_cmd[0]);
	execve(path, data->full_cmd, NULL);
	waitpid(i, NULL, 0);
	close(data->fd[0]);
	free_array(data->full_cmd);
	free (path);
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
	}
	//system("leaks minishell");
	return (0);
}
