/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/09/09 18:49:51 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exuce_built(t_data *data, t_cmd *temp)
{
	if (data->redirect)
		dup2(data->out, STDOUT_FILENO);
	ft_execve(data, NULL);
	g_exit_code = 0;
	close(data->in);
	close(data->out);
	free_array(data->full_cmd);
	data->status = 0;
	ft_wait(data, temp);
}

int	process(char *path, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		g_exit_code = 1;
		return (0);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(data->out, STDOUT_FILENO);
		close(data->in);
		ft_execve(data, path);
		exit(0);
	}
	close(data->out);
	dup2(data->in, STDIN_FILENO);
	close (data->in);
	return (1);
}

void	ft_pipe(t_data *data)
{
	pipe(data->fd);
	data->out = data->fd[1];
	data->in = data->fd[0];
}

void	ft_parce(t_data *data, char *path)
{
	t_cmd	*temp;

	if (!parce_init(data))
		return ;
	temp = (data)->cmd_list;
	while (data->cmd_list && (data->cmd_list->id != -1))
	{
		ft_pipe(data);
		if (cmd_create(data))
		{
			if (is_buildin(data->full_cmd[0]) && data->cmd_list->id == -1
				&& data->status == -1)
				return (exuce_built(data, temp));
			path = path_checker(data, data->full_cmd[0], data->env);
			if (!path)
				path_errors(data);
			else if (!proce_create(data, path, temp))
				return ;
			free(path);
		}
		if (data->cmd_list->id != -1)
			data->cmd_list = data->cmd_list->next;
		free_array(data->full_cmd);
	}
	ft_wait(data, temp);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (1);
	g_exit_code = 0;
	av[0] = "minishell-1.0$ ";
	data.env = cpy_env(env);
	signal(SIGINT, sighandl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data.input = readline(av[0]);
		if (!data.input)
			exit(0);
		if (data.input[0] && !unclosed_quotes(data.input))
		{
			add_history(data.input);
			ft_parce(&data, NULL);
		}
		free (data.input);
	}
	return (0);
}
