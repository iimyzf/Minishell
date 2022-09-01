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
	data->full_cmd = calloc((cmd_parts_count(temp) + 1), sizeof(char *));
	while (data->cmd_list->id != -1 && data->cmd_list->id != 8)
	{
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

// data->full_cmd = calloc((cmd_parts_count(temp) + 1), sizeof(char *));
		// while (temp->id != -1 && (temp->id != 8))
		// {
		// 	fprintf(stderr ,"cmd = [%s] >>>>>> id = %d\n", temp->cmd, temp->id);
		// 	if (temp->id == 4)
		// 	{
		// 		if (temp->next->id == 14)
		// 			temp = temp->next;
		// 		if (is_last_heredoc(temp))
		// 		{
		// 			dup2(temp->in, STDIN_FILENO);
		// 			close (temp->in);
		// 		}
		// 		temp = temp->next;
		// 		while (!(temp->id >= 1 && temp->id <= 4) && temp->id != -1 && temp->id != 14)
		// 			temp = temp->next;
		// 	}
		// 	else if(temp->id == 2)
		// 	{
		// 		temp = temp->next;
		// 		if(temp->id == 14)
		// 			temp = temp->next;
		// 		data->pid = open(temp->cmd, O_RDWR | O_CREAT | O_TRUNC, 0777);
		// 		if (pid < 0)
		// 		{
		// 			perror("minishell");
		// 			return ;
		// 		}
		// 		data->out = dup(pid);
		// 		close(pid);
		// 		status = 1;
		// 	}
		// 	else if(temp->id == 3)
		// 	{
		// 		temp = temp->next;
		// 		/*if(temp->id == 14)
		// 			temp = temp->next;*/
		// 		pid = open(temp->cmd, O_RDWR | O_CREAT | O_APPEND , 0777);
		// 		if (pid < 0)
		// 			return ;
		// 		data->out = dup(pid);
		// 		close(pid);
		// 		status = 1;
		// 	}
		// 	else if(temp->id == 1)
		// 	{
		// 		temp = temp->next;
		// 		if(temp->id == 14)
		// 			temp = temp->next;
		// 		pid = open(temp->cmd, O_RDONLY);
		// 		dup2(pid, STDIN_FILENO);
		// 		close(pid);
		// 	}
		// 	else if ((temp->id == 0 || temp->id == 6 || temp->id == 9 || temp->id == 7))
		// 	{
		// 		//write (2, "here\n", 5);
		// 		while ((temp->id == 0 || temp->id == 6 || temp->id == 9 || temp->id == 7))
		// 		{
		// 			data->full_cmd[j] = ft_strjoin(data->full_cmd[j], temp->cmd);
		// 			temp = temp->next;
		// 		}
		// 		j++;
		// 	}
		// 	if (temp->id != 1 && temp->id != 2 && temp->id != 3 && temp->id != 4 && temp->id != -1 && temp->id != 8)
		// 		temp = temp->next;
		// 	// temp->id != 8 ADDED
		// }
		// data->full_cmd[j] = NULL;
