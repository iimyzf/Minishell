/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:58:40 by azabir            #+#    #+#             */
/*   Updated: 2022/06/07 17:58:42 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	lstadd_back(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd	*temp;

	temp = *cmd_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = cmd;
}
