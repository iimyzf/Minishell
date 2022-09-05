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


char	*collect_file_name(t_data *data)
{
	char	*name;

	name = NULL;
	while (is_cmd(data->cmd_list->id))
	{
		name = ft_strjoin3(name, data->cmd_list->cmd);
		data->cmd_list = data->cmd_list->next;
	}
	return (name);
}

int	write_in(t_data *data, int append)
{
	char	*name;
	data->cmd_list = data->cmd_list->next;
	if(data->cmd_list->id == 14)
		data->cmd_list = data->cmd_list->next;
	name = collect_file_name(data);
	if (append)
		data->pid = open(name, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		data->pid = open(name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	
		free(name);
	if (data->pid < 0)
	{
		perror("minishell");
		g_exit_code = 1;
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
	char	*name;

	data->cmd_list = data->cmd_list->next;
	if(data->cmd_list->id == 14)
		data->cmd_list = data->cmd_list->next;
	name = collect_file_name(data);
	data->pid = open(name, O_RDONLY);
	if (name)
		free(name);
	if (data->pid < 0)
	{
		perror("minishell");
		g_exit_code = 1;
		return (0) ;
	}
	dup2(data->pid, STDIN_FILENO);
	close(data->pid);
	return (1);
}

int		read_from_here(t_data *data)
{
	if (data->cmd_list->next->id == 14)
		data->cmd_list = data->cmd_list->next;
	if (is_last_heredoc(data->cmd_list))
		dup2(data->cmd_list->in, STDIN_FILENO);
	data->cmd_list = data->cmd_list->next;
	while (!(data->cmd_list->id >= 1 && data->cmd_list->id <= 4) &&
			data->cmd_list->id != -1 && data->cmd_list->id != 14)
		data->cmd_list = data->cmd_list->next;
	return (1);
}

int	is_redirec(t_data *data)
{
	if (data->cmd_list->id == 4)
		return (read_from_here(data));
	else if(data->cmd_list->id == 2)
		return(write_in(data, 0));
	else if(data->cmd_list->id == 3)
		return(write_in(data, 1));
	else if(data->cmd_list->id == 1)
		return(read_from(data));
	return(1);
}