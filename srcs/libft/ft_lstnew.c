/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:58:00 by azabir            #+#    #+#             */
/*   Updated: 2022/07/30 10:57:18 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_lstnew(char	*value, int id)
{
	t_cmd	*head;

	head = malloc(sizeof(t_cmd));
	if (!head)
		return (0);
	head->cmd = value;
	head->id = id;
	head -> next = NULL;
	return (head);
}
