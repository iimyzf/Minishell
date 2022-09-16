/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_last_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:37:04 by azabir            #+#    #+#             */
/*   Updated: 2022/09/08 13:56:59 by yagnaou          ###   ########.fr       */
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
			return (0);
	}
	return (1);
}

void	ft_strswap(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}
