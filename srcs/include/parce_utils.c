/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:37:34 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 19:44:04 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data, t_cmd *temp)
{
	int	status;

	while (data->active_proc > 0)
	{
		waitpid(-1, &status, 0);
		data->active_proc --;
		if (WIFEXITED(status))
			g_exit_code = (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			g_exit_code = WTERMSIG(status) + 128;
	}
	dup2(data->saved_out, STDOUT_FILENO);
	dup2(data->saved_in, STDIN_FILENO);
	close (data->saved_out);
	close (data->saved_in);
	lstfree(temp);
}

int	is_cmd(int id)
{
	if ((id == 0 || id == 6 || id == 9 || id == 7))
		return (1);
	return (0);
}

void	path_errors(t_data *data)
{
	g_exit_code = 127;
	if (check_char(data->full_cmd[0], '/'))
	{
		if (!access(data->full_cmd[0], F_OK))
		{
			g_exit_code = 126;
			printf("minishell: %s: is a directory\n", data->full_cmd[0]);
		}
		else
			printf("minishell: %s: No such file or directory\n", data->full_cmd[0]);
	}
	else if (data->full_cmd[0])
		printf("minishell: %s: command not found\n", data->full_cmd[0]);
	close (data->in);
	close (data->out);
}

void	parce_init(t_data *data)
{
	t_cmd	*temp;

	fill_data_list(data);
	temp = (data)->cmd_list;
	if (!syntax_checker((data)->cmd_list, 0) || !check_heredoc(data))
	{
		lstfree(temp);
		return ;
	}
	data->saved_out = dup(STDOUT_FILENO);
	data->saved_in = dup(STDIN_FILENO);
	data->active_proc = 0;
	data->status = -1;
}

int	proce_create(t_data *data, char *path, t_cmd *temp)
{
	if (data->full_cmd[0] == NULL)
		return (1);
	if (data->cmd_list->id != -1)
			data->cmd_list = data->cmd_list->next;
	if (data->cmd_list && data->cmd_list->id == -1 && !data->redirect)
	{
		data->out = 1;
		close (data->fd[1]);
	}
	if (process(path, data))
		data->active_proc += 1;
	else
	{
		free(path);
		free_array(data->full_cmd);
		ft_wait(data, temp);
		g_exit_code = 1;
		return (0);
	}
	return (1);
}
