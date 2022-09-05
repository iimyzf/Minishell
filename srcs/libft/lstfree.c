/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:04:28 by azabir            #+#    #+#             */
/*   Updated: 2022/08/07 14:46:51 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lstfree(t_cmd *lst)
{
	t_cmd	*p;

	while (lst->id != -1)
	{
		p = (lst)-> next;
		if ((lst->id == 9) && check_char(lst->saved, '$'))
		 	free(lst->saved);
		if (*lst->cmd)
			free(lst->cmd);
		free(lst);
		lst = p;
	}
	free(lst);
}
