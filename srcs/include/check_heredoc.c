/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:41:34 by azabir            #+#    #+#             */
/*   Updated: 2022/08/23 18:27:18 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exuc_heredoc(t_cmd	**temp, t_data *data)
{
	int		status;

	if (is_last_heredoc(*temp))
		pipe(data->here_fd);
	if ((*temp)->next->id == 14)
		*temp = (*temp)->next;
	if ((*temp)->next->id == 9)
		heredoc((*temp)->next->saved, data, is_last_heredoc(*temp));
	else
		heredoc((*temp)->next->cmd, data, is_last_heredoc(*temp));
	waitpid(-1, &status, 0);
	WIFEXITED(status);
	return (WEXITSTATUS(status));
}

int	check_heredoc(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd_list;
	while (temp && temp->id != -1)
	{
		if (temp->id == 4)
		{
			if (exuc_heredoc(&temp, data))
				return (0);
			if (is_last_heredoc(temp))
			{
				temp->in = dup (data->here_fd[0]);
				close (data->here_fd[1]);
				close (data->here_fd[0]);
			}
			temp = temp->next;
		}
		temp = temp->next;
	}
	return (1);
}
