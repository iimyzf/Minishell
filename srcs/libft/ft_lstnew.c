/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:58:00 by azabir            #+#    #+#             */
/*   Updated: 2022/08/26 22:17:38 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_lstnew(char	*value, int id, char *saved)
{
	t_cmd	*head;

	head = malloc(sizeof(t_cmd));
	if (!head)
		return (0);
	head->cmd = value;
	head->id = id;
	if (id == 9)
		head->saved = saved;
	else
	 	head->saved = value;
	head -> next = NULL;
	return (head);
}
