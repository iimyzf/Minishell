/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:41:34 by azabir            #+#    #+#             */
/*   Updated: 2022/08/30 22:22:28 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_maker(t_cmd *temp, int *is_expand)
{
	char	*del;

	del = NULL;
	*is_expand = 1;
	temp = temp->next;
	while (!(temp->id >= 1 && temp->id <= 4) && temp->id != -1 && temp->id != 14)
	{
		if (temp->id == 6)
			*is_expand = 0;
		del = ft_strjoin(del, temp->saved);
		temp = temp->next;
	}
	return(del);
}

int	exuc_heredoc(t_cmd	**temp, t_data *data)
{
	int		status;
	int		exp;
	char	*del;

	//expand = check_char((*temp)->next->cmd);
	if (is_last_heredoc(*temp))
		pipe(data->here_fd);
	if ((*temp)->next->id == 14)
		*temp = (*temp)->next;
	if ((*temp)->next->id == -1)
	{
		g_exit_code = 258;
		return(258);
	}
	del = del_maker(*temp, &exp);
	heredoc(del , data, exp, is_last_heredoc(*temp));
	free(del);
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
		//fprintf(stderr ,"from her: cmd = [%s] >>>>>> id = %d\n", temp->cmd, temp->id);
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
