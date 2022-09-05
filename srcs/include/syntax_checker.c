/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:04:27 by azabir            #+#    #+#             */
/*   Updated: 2022/08/30 22:22:28 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_del(int id)
{
	if (id >= 1 && id <= 4)
		return (1);
	return (0);
}

void	max_here(void)
{
	printf("minishell: maximum here-document count exceeded\n");
	g_exit_code = 2;
	exit(2);
}

int	check_next(t_cmd *temp, int id)
{
	if ((temp)->id == 14)
		temp = (temp)->next;
	if (id == 8 || is_del(id))
	{
		if ((temp)->id == -1)
		{
			printf("minishell: syntax error near unexpected token `newline\n");
			return (0);
		}
		if ((temp)->id == 8)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", (temp)->cmd);
			return (0);
		}
	}
	if (is_del(id))
	{
		if ((temp)->id == 8 || is_del((temp)->id))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", (temp)->cmd);
			return (0);
		}
	}
	return (1);
}

int	syntax_checker(t_cmd *cmd, int	here_count)
{
	t_cmd	*temp;
	
	temp = cmd;
	if (temp->id == 14)
		temp = temp->next;
	if (temp->id == 8)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", temp->cmd);
		g_exit_code = 258;
		return (0);
	}
	while (temp->id != -1)
	{
		if (temp->id == 4 && ++here_count > 16)
			max_here();
		if ((is_del(temp->id) || temp->id == 8) && !check_next((temp->next), temp->id))
		{
				g_exit_code = 258;
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}
