/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:13:49 by yagnaou           #+#    #+#             */
/*   Updated: 2022/09/07 22:29:26 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_mun
{
	TKN_ID,
	TKN_LOPERATOR,
	TKN_ROPERATOR,
	TKN_APPEND,
	TKN_HEREDOC,
	TKN_STRING,
	TKN_DQUOTES,
	TKN_SQUOTES,
	TKN_PIPE,
	TKN_DOLLAR,
	TKN_AND,
	TKN_OR,
	TKN_LPARAN,
	TKN_RPARAN,
	TKN_SPACE
}	t_num;

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

t_token	*tkn_init(int type, char *value);

#endif