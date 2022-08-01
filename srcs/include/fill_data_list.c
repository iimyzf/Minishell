/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:56:16 by azabir            #+#    #+#             */
/*   Updated: 2022/07/31 22:03:45 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_data_list(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = lexer_init(data->input);
	(data)->cmd_list = NULL;
	while ((token = lexer_get_next_token(lexer)) != NULL)
	{
		if (!((data)->cmd_list))
			(data)->cmd_list = ft_lstnew(token->value, token->type);
		else
			lstadd_back(&(data)->cmd_list, ft_lstnew(token->value, token->type));
		free(token);
	}
	lstadd_back(&(data)->cmd_list, ft_lstnew("", -1));
	free(lexer);
	free (token);
}
