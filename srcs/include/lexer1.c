/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:08:10 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 22:33:37 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer_init(char *data)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->data = data;
	lexer->index = 0;
	lexer->c = data[lexer->index];
	lexer->next_c = data[lexer->index + 1];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer, int count)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->data))
	{
		lexer->index += count;
		lexer->c = lexer->data[lexer->index];
		if (lexer->data[lexer->index])
			lexer->next_c = lexer->data[lexer->index + 1];
	}
}

void	lexer_skip_white_spaces(t_lexer *lexer)
{
	if (lexer->c == ' ' || lexer->c == '\t')
	{
		while ((lexer->next_c == ' ' || lexer->next_c == '\t')
			&& lexer->c != '-')
			lexer_advance(lexer, 1);
		lexer->c = '	';
	}
}

t_token	*next_tkn(t_lexer *lexer, t_data *data)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->data))
	{
		lexer_skip_white_spaces(lexer);
		if (lexer->c == '"')
			return (clct_dq_string(lexer, lexer->c, data, TKN_DQUOTES));
		if (lexer->c == '\'')
			return (clct_str(lexer, lexer->c, TKN_SQUOTES));
		if (lexer->c == '>' && lexer->data[lexer->index + 1] == '>')
			return (nxt_tkn(lexer, tkn_init(TKN_APPEND, to_dstr(lexer)), 2));
		else if (lexer->c == '>')
			return (nxt_tkn(lexer, tkn_init(TKN_ROPERATOR, to_str(lexer)), 1));
		else if (lexer->c == '	')
			return (nxt_tkn(lexer, tkn_init(TKN_SPACE, to_str(lexer)), 1));
		else if (lexer->c == '<' && lexer->data[lexer->index + 1] == '<')
			return (nxt_tkn(lexer, tkn_init(TKN_HEREDOC, to_dstr(lexer)), 2));
		else if (lexer->c == '<')
			return (nxt_tkn(lexer, tkn_init(TKN_LOPERATOR, to_str(lexer)), 1));
		else if (lexer->c == '|')
			return (nxt_tkn(lexer, tkn_init(TKN_PIPE, to_str(lexer)), 1));
		else if (lexer->c == '$')
			return (clct_env_str(lexer, data, TKN_DOLLAR));
		return (clct_id(lexer, data));
		lexer_advance(lexer, 1);
	}
	return (NULL);
}

t_token	*clct_str(t_lexer *lexer, char c, int token)
{
	char	*value;
	char	*tmp;
	char	*str;

	lexer_advance(lexer, 1);
	value = "";
	while (lexer->c != c && lexer->c != '\0')
	{
		str = to_str(lexer);
		tmp = ft_strjoin2(value, str);
		free(str);
		value = tmp;
		lexer_advance(lexer, 1);
	}
	lexer_advance(lexer, 1);
	return (tkn_init(token, value));
}
