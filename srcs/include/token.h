/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:13:49 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/15 07:15:45 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_mun
{
	TOKEN_ID,
	TOKEN_LOPERATOR,
	TOKEN_ROPERATOR,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_STRING,
	TOKEN_DQUOTES,
	TOKEN_SQUOTES,
	TOKEN_PIPE,
	TOKEN_DOLLAR,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPARAN,
	TOKEN_RPARAN,
	TOKEN_SPACE
}	t_num;

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

t_token	*token_init(int type, char *value);

#endif