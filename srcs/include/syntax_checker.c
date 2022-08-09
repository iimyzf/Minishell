/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:04:27 by azabir            #+#    #+#             */
/*   Updated: 2022/08/09 17:25:45 by azabir           ###   ########.fr       */
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
		/*if (temp->id == 14)
			temp = temp->next;*/
		if ((temp->id != 0 && temp->id != 5 && temp->id != 9 && temp->id != 8 && temp->id != 6 && temp->id != 7 && temp->id != 14) && (temp->next->id != 0 && temp->next->id != 5 && temp->next->id != -1 && temp->next->id != 14))
		{
			write (1, "heee\n", 5);
			printf("minishell: syntax error near unexpected token `%s'\n", temp->next->cmd);
			return (0);
		}
		if ((temp->id != 0 && temp->id != 5 && temp->id != 9 && temp->id != 6 && temp->id != 7 && temp->id != 14) && temp->next->id == -1)
		{
			write (1, "here\n", 5);
			printf("minishell: syntax error near unexpected token `newline'\n");
			return(0);
		}
		temp = temp->next;
	}
	return (1);
}

