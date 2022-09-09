/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:56:16 by azabir            #+#    #+#             */
/*   Updated: 2022/09/08 21:17:15 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_list_from_env(t_data *data, char *value)
{
	char	**arr;
	char	**tmp;

	if (value && check_char(value, ' '))
	{
		arr = ft_split(value, ' ');
		tmp = arr;
		while (*arr != NULL)
		{
			lstadd_back(&(data)->cmd_list, ft_lstnew(ft_strdup(*arr), 9, \
					ft_strdup(data->saved)));
			arr++;
			if (*arr)
				lstadd_back(&(data)->cmd_list, ft_lstnew(ft_strdup(" "), \
						14, data->saved));
		}
		free(value);
		free(data->saved);
		free_array(tmp);
	}
	else if (value == NULL)
		lstadd_back(&(data)->cmd_list, ft_lstnew(NULL, 9, data->saved));
	else
		lstadd_back(&(data)->cmd_list, ft_lstnew(value, 9, data->saved));
}

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
		if (token->type == 9)
			fill_list_from_env(data, token->value);
		else
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
