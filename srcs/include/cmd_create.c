/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:02:25 by azabir            #+#    #+#             */
/*   Updated: 2022/08/29 21:38:53 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_create(t_data *data, int	*status)
{
	int	pid;
	int j;

	j = 0;
	while (data->cmd_list->id != -1 && (data->cmd_list->id != 8))
		{
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
					return (0);
				data->out = dup(pid);
				close(pid);
				*status = 1;
			}
			else if(data->cmd_list->id == 3)
			{
				data->cmd_list = data->cmd_list->next;
				if(data->cmd_list->id == 14)
					data->cmd_list = data->cmd_list->next;
				pid = open(data->cmd_list->cmd, O_RDWR | O_CREAT | O_APPEND , 0777);
				if (pid < 0)
					return (0);
				data->out = dup(pid);
				close(pid);
				*status = 1;
			}
			else if(data->cmd_list->id == 1)
			{
				data->cmd_list = data->cmd_list->next;
				if(data->cmd_list->id == 14)
					data->cmd_list = data->cmd_list->next;
				pid = open(data->cmd_list->cmd, O_RDONLY);
				if (pid < 0)
				{
					printf("minishell: %s: No such file or directory\n", data->cmd_list->cmd);
					g_data.exit_code = 1;
					while (data->cmd_list->id != -1 && (data->cmd_list->id != 8))
						data->cmd_list = data->cmd_list->next;
					if (data->cmd_list->id != -1)
						data->cmd_list = data->cmd_list->next;
					free_array(data->full_cmd);
					break;
				}
				dup2(pid, STDIN_FILENO);
				close (pid);
			}
			else if ((data->cmd_list->id == 0 || data->cmd_list->id == 6 || data->cmd_list->id == 9 || data->cmd_list->id == 7))
			{
				while ((data->cmd_list->id == 0 || data->cmd_list->id == 6 || data->cmd_list->id == 9 || data->cmd_list->id == 7))
				{
					//fprintf(stderr ,"cmd = [%s] >>>>>> id = %d\n", data->cmd_list->cmd, data->cmd_list->id);
					data->full_cmd[j] = ft_strjoin(data->full_cmd[j], data->cmd_list->cmd);
					data->cmd_list = data->cmd_list->next;
				}
				j++;
			}
			if (data->cmd_list->id != 1 && data->cmd_list->id != 2 && data->cmd_list->id != 3 && data->cmd_list->id != 4 && data->cmd_list->id != -1)
				data->cmd_list = data->cmd_list->next;
		}
		return (0);
}