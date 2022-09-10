/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:56:16 by azabir            #+#    #+#             */
/*   Updated: 2022/09/10 20:53:41 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_data_list(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;
	t_cmd	*temp;

	lexer = lexer_init(data->input);
	(data)->cmd_list = NULL;
	token = next_tkn(lexer, data);
	while (token != NULL)
	{
		lstadd_back(&(data)->cmd_list, ft_lstnew(token->value, token->type, \
			data->saved));
		free(token);
		token = next_tkn(lexer, data);
	}
	lstadd_back(&(data)->cmd_list, ft_lstnew("", -1, data->saved));
	temp = (data)->cmd_list;
	free(lexer);
	free (token);
}
