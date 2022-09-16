/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:33 by yagnaou           #+#    #+#             */
/*   Updated: 2022/09/07 22:34:55 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*clct_id(t_lexer *lexer, t_data *data)
{
	char	*value;
	char	*tmp;
	char	*str;

	(void) data;
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c && !is_special(lexer->c))
	{
		str = to_str(lexer);
		tmp = ft_strjoin(value, str);
		free(value);
		free(str);
		value = tmp;
		if (lexer->c != ' ')
			lexer_advance(lexer, 1);
	}
	return (tkn_init(TKN_ID, value));
}

char	*lexer_collect_alnum(t_lexer *lexer)
{
	char	*value;
	char	*tmp;
	char	*str;

	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c && ft_isalnum(lexer->c))
	{
		str = to_str(lexer);
		tmp = ft_strjoin(value, str);
		free(value);
		free(str);
		value = tmp;
		lexer_advance(lexer, 1);
	}
	return (value);
}

t_token	*nxt_tkn(t_lexer *lexer, t_token *token, int count)
{
	lexer_advance(lexer, count);
	return (token);
}

char	*to_str(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

char	*to_dstr(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(3, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = lexer->c;
	str[1] = lexer->data[lexer->index + 1];
	str[2] = '\0';
	return (str);
}
