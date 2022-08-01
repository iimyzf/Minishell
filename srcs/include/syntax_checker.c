/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:04:27 by azabir            #+#    #+#             */
/*   Updated: 2022/08/01 01:52:42 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_checker(t_cmd *cmd)
{
	t_cmd	*temp;
	
	temp = cmd;

	if (temp->id == 8 || temp->id == 11)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", temp->cmd);
		return(0);
	}
	while (temp->id != -1)
	{
		if ((temp->id != 0 && temp->id != 5 && temp->id != 8) && (temp->next->id != 0 && temp->next->id != 5 && temp->next->id != -1))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", temp->next->cmd);
			return (0);
		}
		if ((temp->id != 0 && temp->id != 5) && temp->next->id == -1)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return(0);
		}
		temp = temp->next;
	}
	return (1);
}

