/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:14:54 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/15 14:56:41 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_strswap(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

char	**cpy_env(char **env)
{
	char	**str;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(str = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	sort_this(char **tab)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				ft_strswap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (tab[i])
	{
		tmp = ft_split(tab[i], '=');
		printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
		i++;
	}
}

void	ft_print_sorted_env(char **env)
{
	sort_this(cpy_env(env));
}