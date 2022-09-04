/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:14:54 by yagnaou           #+#    #+#             */
/*   Updated: 2022/09/04 16:27:44 by yagnaou          ###   ########.fr       */
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
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
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

void	add_print_qoutes(char **env, int i)
{
	int	j;

	j = 0;
	printf("declare -x ");
	while (env[i][j])
	{
		if (env[i][j] == '=')
		{
			printf("%c", env[i][j]);
			break ;
		}
		printf("%c", env[i][j]);
		j++;
	}
	printf("%c%s%c\n", '"', env[i] + j + 1, '"');
}

void	add_print_declare(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strchr(env[i], '='))
			printf("declare -x %s\n", env[i]);
		else
			add_print_qoutes(env, i);
		free(env[i]);
		i++;
	}
}

void	sort_this(char **tab)
{
	int		i;
	int		j;

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
	add_print_declare(tab);
}

void	ft_print_sorted_env(char **env)
{
	sort_this(cpy_env(env));
}
