/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:56:16 by azabir            #+#    #+#             */
/*   Updated: 2022/08/26 22:16:43 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_list_from_env(t_data *data, char *value)
{
	char	**arr;

	arr = ft_split(value, ' ');
	if (value == NULL)
		lstadd_back(&(data)->cmd_list, ft_lstnew("", 9, data->saved));
	while (*arr != NULL)
	{
		lstadd_back(&(data)->cmd_list, ft_lstnew(*arr, 9, data->saved));
		arr++;
		if (*arr != NULL)
			lstadd_back(&(data)->cmd_list, ft_lstnew(" ", 14, data->saved));
	}
}

void	fill_data_list(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;
	t_cmd	*temp;

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
		//free(token->value);
		free(token);
		//free (data->saved);
		token = lexer_get_next_token(lexer, data);
	}
	lstadd_back(&(data)->cmd_list, ft_lstnew("", -1, data->saved));
	temp = (data)->cmd_list;
	// while (temp)
	// {
	// 	fprintf(stderr, "check [%s] of id[%d]\n", temp->cmd, temp->id);
	// 	temp = temp->next;
	// }
	//temp = data->cmd_list;
	free(lexer);
	free (token);
}
