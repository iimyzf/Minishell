/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:32:34 by yagnaou           #+#    #+#             */
/*   Updated: 2022/09/07 22:23:27 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tkn_init(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}
