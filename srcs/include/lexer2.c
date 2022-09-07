/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:09:20 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 22:41:13 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*clct_env_str(t_lexer *lexer, t_data *data, int token)
{
	char	*value;
	char	*str;

	data->saved = to_str(lexer);
	lexer_advance(lexer, 1);
	value = "";
	if (lexer->c == '?')
		data->saved = ft_strjoin2(data->saved, "?");
	if (ft_isalnum(lexer->c) || lexer->c == '?')
	{
		if (lexer->c == '?')
			lexer_advance(lexer, 1);
		str = lexer_collect_alnum(lexer);
		data->saved = ft_strjoin2(data->saved, str);
		free(str);
		str = check_env(data, data->saved + 1);
		value = ft_strjoin(value, str);
		if (str && *str)
			free(str);
	}
	else if (lexer->c != '\'' && lexer->c != '"')
		value = ft_strdup(data->saved);
	return (tkn_init(token, value));
}

char	*lexer_collect_env_value(t_lexer *lexer, t_data *data)
{
	char	*value;
	char	*str;

	data->saved = to_str(lexer);
	lexer_advance(lexer, 1);
	value = "";
	if (lexer->c == '?')
		data->saved = ft_strjoin2(data->saved, "?");
	if (ft_isalnum(lexer->c) || lexer->c == '?')
	{
		if (lexer->c == '?')
			lexer_advance(lexer, 1);
		str = lexer_collect_alnum(lexer);
		data->saved = ft_strjoin2(data->saved, str);
		free(str);
		str = check_env(data, data->saved + 1);
		value = ft_strjoin(value, str);
		if (str && *str)
			free(str);
	}
	else if (lexer->c != '\'' && lexer->c != '"')
		value = ft_strdup(data->saved);
	return (value);
}

char	*get_str(int *token, t_lexer *lexer, t_data *data, char **saved)
{
	char	*str;

	if (lexer->c == '$' && (ft_isalnum(lexer->next_c) || lexer->next_c == '?'))
	{
		*saved = ft_calloc(sizeof(char), 1);
		*token = TKN_DOLLAR;
		str = lexer_collect_env_value(lexer, data);
		*saved = ft_strjoin3(*saved, data->saved);
		free (data->saved);
	}
	else
	{
		str = to_str(lexer);
		lexer_advance(lexer, 1);
	}
	return (str);
}

t_token	*clct_dq_string(t_lexer *lexer, char c, t_data *data, int token)
{
	char	*value;
	char	*tmp;
	char	*str;
	char	*saved;

	lexer_advance(lexer, 1);
	value = "";
	while (lexer->c != c && lexer->c != '\0' && lexer->c != '\n')
	{
		str = get_str(&token, lexer, data, &saved);
		if (str != NULL)
			tmp = ft_strjoin2(value, str);
		else
			tmp = value;
		free(str);
		value = tmp;
	}
	data->saved = saved;
	lexer_advance(lexer, 1);
	return (tkn_init(token, value));
}
