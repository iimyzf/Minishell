/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:33 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/14 15:12:51 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer_init(char *data)
{
	t_lexer	*lexer;

	lexer = calloc(1, sizeof(t_lexer));
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
	while ((lexer->next_c == ' ' || lexer->next_c == '\t') && lexer->c != '-')
		lexer_advance(lexer, 1);
}

t_token	*lexer_get_next_token(t_lexer *lexer, t_data *data)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->data))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_white_spaces(lexer);

		if (lexer->c == '"')
			return (lexer_collect_dq_string(lexer, lexer->c, data));
		if (lexer->c == '\'')
			return (lexer_collect_string(lexer, lexer->c, TOKEN_SQUOTES));

		else if (ft_isalnum(lexer->c))
			return (lexer_collect_id(lexer, data));

		if (lexer->c == '>' && lexer->data[lexer->index + 1] == '>')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_APPEND, lexer_get_current_char_as_two_strings(lexer)), 2));

		else if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_ROPERATOR, lexer_get_current_char_as_string(lexer)), 1));
			
		else if (lexer->c == ' ')
		{
			lexer->c = '	';
			return (lexer_advance_with_token(lexer, token_init(TOKEN_SPACE, lexer_get_current_char_as_string(lexer)), 1));
		}
		else if (lexer->c == '<' && lexer->data[lexer->index + 1] == '<')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_HEREDOC, lexer_get_current_char_as_two_strings(lexer)), 2));

		else if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_LOPERATOR, lexer_get_current_char_as_string(lexer)), 1));

		else if (lexer->c == '"')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_DQUOTES, lexer_get_current_char_as_string(lexer)), 1));

		else if (lexer->c == '\'')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_SQUOTES, lexer_get_current_char_as_string(lexer)), 1));

		if (lexer->c == '|' && lexer->data[lexer->index + 1] == '|')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_OR, lexer_get_current_char_as_two_strings(lexer)), 2));

		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_PIPE, lexer_get_current_char_as_string(lexer)), 1));

		else if (lexer->c == '$')
			return (lexer_collect_env_string(lexer, data, TOKEN_DOLLAR));

		if (lexer->c == '&' && lexer->data[lexer->index + 1] == '&')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_AND, lexer_get_current_char_as_two_strings(lexer)), 2));

		else if (lexer->c == '(')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_LPARAN, lexer_get_current_char_as_string(lexer)), 1));

		else if (lexer->c == ')')
			return (lexer_advance_with_token(lexer, token_init(TOKEN_RPARAN, lexer_get_current_char_as_string(lexer)), 1));

		lexer_advance(lexer, 1);
	}
	return (NULL);
}

t_token	*lexer_collect_string(t_lexer *lexer, char c, int token)
{
	char	*value;
	char	*tmp;
	char	*str;

	lexer_advance(lexer, 1);
	value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != c && lexer->c != '\0')
	{
		str = lexer_get_current_char_as_string(lexer);
		tmp = ft_strjoin(value, str);
		free (value);
		free(str);
		value = tmp;
		lexer_advance(lexer, 1);
	}
	lexer_advance(lexer, 1);
	return token_init(token, value);
}

t_token	*lexer_collect_env_string(t_lexer *lexer,t_data *data, int token)
{
	char	*value;
	char	*str;

	data->saved = lexer_get_current_char_as_string(lexer);
	lexer_advance(lexer, 1);
	value = calloc(1, sizeof(char));
	value[0] = '\0';
	if (ft_isalnum2(lexer->c))
	{
		data->saved = ft_strjoin(data->saved, lexer_collect_id(lexer, data)->value);
		
		str = check_env(data, data->saved + 1);
		value = ft_strjoin2(value, str);
	}
	else
		value = data->saved;
	fprintf(stderr, "value = [%s]\n", value);
	return token_init(token, value);
}

t_token	*lexer_collect_dq_string(t_lexer *lexer, char c, t_data *data)
{
	char	*value;
	char	*tmp;
	char	*str;

	lexer_advance(lexer, 1);
	value = calloc(1, sizeof(char));
	value[0] = '\0';
	data->saved = value;
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == '$' && ft_isalnum2(lexer->next_c))
			str = lexer_collect_env_string(lexer, data, TOKEN_DOLLAR)->value;
		else
		{
			str = lexer_get_current_char_as_string(lexer);
			lexer_advance(lexer, 1);
		}
		if (str != NULL)
			tmp = ft_strjoin(value, str);
		else
			tmp = value;
		if (str != NULL)
			free (value);
		free(str);
		value = tmp;
	}
lexer_advance(lexer, 1);
	return token_init(TOKEN_DQUOTES, value);
}

t_token	*lexer_collect_id(t_lexer *lexer, t_data *data)
{
	char	*value;
	char	*tmp;
	char	*str;

	value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (ft_isalnum(lexer->c) || lexer->c == '\'' || lexer->c == '"')
	{
		if (lexer->c == '\'')
			str = lexer_collect_string(lexer, lexer->c, TOKEN_SQUOTES)->value;
		else if (lexer->c == '"')
			str = lexer_collect_dq_string(lexer, lexer->c, data)->value;
		else
			str = lexer_get_current_char_as_string(lexer);
		tmp = ft_strjoin(value, str);
		free(value);
		free(str);
		value = tmp;
		lexer_advance(lexer, 1);
	}
	return token_init(TOKEN_ID, value);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token, int count)
{
	lexer_advance(lexer, count);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

char	*lexer_get_current_char_as_two_strings(t_lexer *lexer)
{
	char	*str;

	str = calloc(3, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = lexer->c;
	str[1] = lexer->data[lexer->index + 1];
	str[2] = '\0';
	return (str);
}
