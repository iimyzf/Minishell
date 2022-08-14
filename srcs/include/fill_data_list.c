/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:56:16 by azabir            #+#    #+#             */
/*   Updated: 2022/08/14 11:48:47 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_list_from_env(t_data *data, char *value)
{
	char	**arr;
	while (*arr != NULL)
	{
		lstadd_back(&(data)->cmd_list, ft_lstnew(*arr, 0));
		lstadd_back(&(data)->cmd_list, ft_lstnew(" ", 14));
		arr++;
	}
}

int	fill_data_list(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = lexer_init(data->input);
	(data)->cmd_list = NULL;
	while ((token = lexer_get_next_token(lexer, data)) != NULL)
	{
		if (token->type == 9)
			fill_list_from_env(data, token->value);
		else
			lstadd_back(&(data)->cmd_list, ft_lstnew(token->value, token->type));
		free(token);
	}
	lstadd_back(&(data)->cmd_list, ft_lstnew("", -1));
	free(lexer);
	free (token);
	return (1);
}
