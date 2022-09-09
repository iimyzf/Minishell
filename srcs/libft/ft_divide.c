/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 22:22:17 by azabir            #+#    #+#             */
/*   Updated: 2022/09/09 18:50:03 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_buff(char *str, int start, int stop)
{
	char	*buff;
	int		i;

	i = 0;
	buff = malloc(sizeof(char) * (stop - start + 1));
	while (str[start] && start < stop)
	{
		buff[i] = str[start];
		i++;
		start++;
	}
	buff[i] = 0;
	return (buff);
}

char	**ft_divide(char *str, char c)
{
	char	**devise;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	devise = malloc(sizeof(char *) * 3);
	while (str[i] && str[i] != c)
		i++;
	devise [0] = get_buff(str, 0, i);
	devise [1] = get_buff(str, i + 1, ft_strlen(str));
	devise [2] = NULL;
	return (devise);
}
