/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:41:34 by azabir            #+#    #+#             */
/*   Updated: 2022/08/01 15:46:19 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd_list;
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
}