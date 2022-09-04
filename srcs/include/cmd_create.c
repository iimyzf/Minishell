/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:02:25 by azabir            #+#    #+#             */
/*   Updated: 2022/08/30 22:12:27 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirec(int id)
{
	if(id >= 1 && id <= 4)
		return (1);
	return (0);
}

void	join_cmd(t_data *data, int	*index)
{
	while (is_cmd(data->cmd_list->id))
	{
		if (*data->cmd_list->cmd)
			data->full_cmd[*index] =\
				ft_strjoin2(data->full_cmd[*index], data->cmd_list->cmd);
		data->cmd_list = data->cmd_list->next;
	}
	*index += 1;
}

int	cmd_create(t_data *data)
{
	int		index;
	int		status;
	t_cmd	*temp;

	index = 0;
	data->redirect = 0;
	status = 1;
	temp = data->cmd_list;
	data->full_cmd = ft_calloc((cmd_parts_count(temp) + 1), sizeof(char *));
	while (data->cmd_list->id != -1 && data->cmd_list->id != 8)
	{
		//fprintf(stderr, "cmd = [%s] >>> id = [%d]\n", data->cmd_list->cmd, data->cmd_list->id);
		if (redirec( data->cmd_list->id))
			status = is_redirec(data);
		else if (is_cmd(data->cmd_list->id) && status)
			join_cmd(data, &index);
		if (is_cmd(data->cmd_list->id) || data->cmd_list->id == 14)
			data->cmd_list = data->cmd_list->next;
	}
	data->full_cmd[index] = NULL;
	return (status);
}
