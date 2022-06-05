/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:13:49 by yagnaou           #+#    #+#             */
/*   Updated: 2022/06/05 17:33:13 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

enum
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
	TOKEN_RPARAN
}	type;

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

t_token	*token_init(int type, char *value);

#endif