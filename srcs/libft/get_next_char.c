/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:25:49 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 18:26:05 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	get_next_char(int pid)
{
	char	*c;
	int		i;

	c = malloc(sizeof(char) * 1);
	i = read(pid, c, 1);
	if (i < 0)
		return (0);
	return (*c);
}
