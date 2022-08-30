/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:02:25 by azabir            #+#    #+#             */
/*   Updated: 2022/08/30 21:22:35 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_create(t_data *data)
{
	int 	status;
	t_cmd	*temp;
	int		index;
	int		pid;

	temp = data->cmd_list;
	index = 0;
	data->full_cmd = calloc((cmd_parts_count(temp) + 1), sizeof(char *));
	fprintf(stderr ,"out cmd = [%s] >>>>>> id = %d\n", data->cmd_list->cmd, data->cmd_list->id);
	while (data->cmd_list->id != -1 && data->cmd_list->id != 8)
	{
		fprintf(stderr ,"cmd = [%s] >>>>>> id = %d\n", data->cmd_list->cmd, data->cmd_list->id);
		if (data->cmd_list->id == 4)
		{
			if (data->cmd_list->next->id == 14)
				data->cmd_list = data->cmd_list->next;
			if (is_last_heredoc(data->cmd_list))
			{
				dup2(data->cmd_list->in, STDIN_FILENO);
				close (data->cmd_list->in);
			}
			data->cmd_list = data->cmd_list->next;
			while (!(data->cmd_list->id >= 1 && data->cmd_list->id <= 4) && data->cmd_list->id != -1 && data->cmd_list->id != 14)
				data->cmd_list = data->cmd_list->next;
		}
		else if(data->cmd_list->id == 2)
		{
			data->cmd_list = data->cmd_list->next;
			if(data->cmd_list->id == 14)
				data->cmd_list = data->cmd_list->next;
			pid = open(data->cmd_list->cmd, O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (pid < 0)
			{
				perror("minishell");
				return (0) ;
			}
			data->out = dup(pid);
			close(pid);
			status = 1;
		}
		else if(data->cmd_list->id == 3)
		{
			data->cmd_list = data->cmd_list->next;
			/*if(data->cmd_list->id == 14)
				data->cmd_list = data->cmd_list->next;*/
			pid = open(data->cmd_list->cmd, O_RDWR | O_CREAT | O_APPEND , 0777);
			if (pid < 0)
				return (0) ;
			data->out = dup(pid);
			close(pid);
			status = 1;
		}
		else if(data->cmd_list->id == 1)
		{
			data->cmd_list = data->cmd_list->next;
			if(data->cmd_list->id == 14)
				data->cmd_list = data->cmd_list->next;
			pid = open(data->cmd_list->cmd, O_RDONLY);
			dup2(pid, STDIN_FILENO);
			close(pid);
		}
		else if ((data->cmd_list->id == 0 || data->cmd_list->id == 6 || data->cmd_list->id == 9 || data->cmd_list->id == 7))
		{
			//write (2, "here\n", 5);
			while ((data->cmd_list->id == 0 || data->cmd_list->id == 6 || data->cmd_list->id == 9 || data->cmd_list->id == 7))
			{
				data->full_cmd[index] = ft_strjoin(data->full_cmd[index], data->cmd_list->cmd);
				data->cmd_list = data->cmd_list->next;
			}
			index++;
		}
		if (data->cmd_list->id != 1 && data->cmd_list->id != 2 && data->cmd_list->id != 3 && data->cmd_list->id != 4 && data->cmd_list->id != -1 && data->cmd_list->id != 8)
			data->cmd_list = data->cmd_list->next;
		// temp->id != 8 ADDED
	}
	data->full_cmd[index] = NULL;
	return (1);
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
		// 		pid = open(temp->cmd, O_RDWR | O_CREAT | O_TRUNC, 0777);
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
