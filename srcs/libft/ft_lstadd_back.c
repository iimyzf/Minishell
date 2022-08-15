/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:58:40 by azabir            #+#    #+#             */
/*   Updated: 2022/08/14 14:44:34 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lstadd_back(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd	*temp;

	if (!(*cmd_list))
		*cmd_list = cmd;
	else
	{
		temp = *cmd_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = cmd;
	}
}
