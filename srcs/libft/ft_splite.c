/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:45:38 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 18:22:24 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_strcount(char *l, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (c)
	{
		while (l[i])
		{
			if (l[i] != c)
				j++;
			while (l[i] != c && l[i] != '\0')
				i++;
			while (l[i] == c)
				i++;
		}
	}
	else
		j = 1;
	return (j);
}

static char	**ft_mkstr(char **h, char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			k++;
			i++;
		}
		while (s[i] == c && c)
			i++;
		h[j] = malloc(sizeof(char) * (k + 1));
		if (!h[j])
			return (NULL);
		j++;
		k = 0;
	}
	return (h);
}

char	**ft_copy(char **h, char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			h[k][j] = s[i];
			j++;
			i++;
		}
		h[k][j] = '\0';
		while (s[i] == c && c)
			i++;
		k++;
		j = 0;
	}
	h[k] = NULL;
	return (h);
}

char	**ft_split(char *s, char c)
{
	char	**h;
	int		i;
	int		j;

	if (!s || !*s)
	{
		h = malloc(sizeof(char *) * 1);
		if (!h)
			return (NULL);
		*h = NULL;
		return (h);
	}
	i = 0;
	while (s[i] == c)
		i++;
	j = ft_strcount(s, c);
	h = malloc(sizeof(char *) * (j + 1));
	if (!h)
		return (NULL);
	ft_mkstr(h, s + i, c);
	ft_copy(h, s + i, c);
	return (h);
}
