/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_last_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:37:04 by azabir            #+#    #+#             */
/*   Updated: 2022/07/17 16:37:07 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_last_heredoc(t_cmd	*cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp && temp->id != -1 && temp->id != 8)
	{	
		temp = temp->next;
		if (temp->id == 4)
			return(0);
	}
	return(1);
}
