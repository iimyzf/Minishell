/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:58:32 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 18:19:51 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_digcount(int r)
{
	int				j;
	unsigned int	n;

	if (r < 0)
		n = -r;
	else
		n = r;
	j = 0;
	while (n >= 1)
	{
		n = n / 10;
		j++;
	}
	if (r <= 0)
		j++;
	return (j);
}

char	*ft_itoa(int r)
{
	char			*s;
	unsigned int	n;
	int				j;

	j = ft_digcount(r);
	if (r < 0)
		n = -r;
	else
		n = r;
	s = malloc(sizeof(char) * (j + 1));
	if (!s)
		return (NULL);
	s[j] = '\0';
	j--;
	while (j >= 0)
	{
		s[j] = n % 10 + '0';
		n = (n / 10);
		j--;
	}
	if (r < 0)
		s[0] = '-';
	return (s);
}
