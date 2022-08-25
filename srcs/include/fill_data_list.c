/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:56:16 by azabir            #+#    #+#             */
/*   Updated: 2022/08/25 21:37:03 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_list_from_env(t_data *data, char *value)
{
	char	**arr;

	arr = ft_split(value, ' ');
	if (value == NULL)
	{
		lstadd_back(&(data)->cmd_list, ft_lstnew("", 9, data->saved));
		//lstadd_back(&(data)->cmd_list, ft_lstnew(" ", 14, data->saved));
	}
	while (*arr != NULL)
	{
		lstadd_back(&(data)->cmd_list, ft_lstnew(*arr, 9, data->saved));
		//lstadd_back(&(data)->cmd_list, ft_lstnew(" ", 14, data->saved));
		arr++;
	}
}

void	fill_data_list(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = lexer_init(data->input);
	(data)->cmd_list = NULL;
	token = lexer_get_next_token(lexer, data);
	while (token != NULL)
	{
		if (token->type == 9)
			fill_list_from_env(data, token->value);
		else
			lstadd_back(&(data)->cmd_list, ft_lstnew(token->value, token->type, \
						data->saved));
		free(token);
		token = lexer_get_next_token(lexer, data);
	}
	lstadd_back(&(data)->cmd_list, ft_lstnew("", -1, data->saved));
	free(lexer);
	free (token);
}
