/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:01:42 by azabir            #+#    #+#             */
/*   Updated: 2022/08/31 22:01:42 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirec(int	id)
{
	if (id >= 1 && id <= 4)
		return (1);
	return (0);
}

int	write_in(t_data *data, int append)
{
	data->cmd_list = data->cmd_list->next;
	if(data->cmd_list->id == 14)
		data->cmd_list = data->cmd_list->next;
	if (append)
		data->pid = open(data->cmd_list->cmd, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		data->pid = open(data->cmd_list->cmd, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->pid < 0)
	{
		perror("minishell");
		g_exit_code = errno;
		return (0) ;
	}
	data->redirect = 1;
	data->out = dup(data->pid);
	close(data->fd[1]);
	close(data->pid);
	return (1);
}

int		read_from(t_data *data)
{
	data->cmd_list = data->cmd_list->next;
	if(data->cmd_list->id == 14)
		data->cmd_list = data->cmd_list->next;
	data->pid = open(data->cmd_list->cmd, O_RDONLY);
	if (data->pid < 0)
	{
		perror("minishell");
		g_exit_code = errno;
		return (0) ;
	}
	dup2(data->pid, STDIN_FILENO);
	close(data->pid);
	return (1);
}
