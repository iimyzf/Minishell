/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:47:21 by azabir            #+#    #+#             */
/*   Updated: 2022/09/04 14:49:52 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkif(const char *this, const char	*inthis, size_t e, size_t l)
{
	size_t	j;

	j = 0;
	while (this[j] != '\0')
	{
		if (this[j] == inthis[e] && e < l)
		{
			j++;
			e++;
		}
		else
			return (0);
	}
	return (1);
}

char	*ft_strnstr(char *h, char *n, int l)
{
	int	i;
	int	e;

	i = 0;
	if (!n[i])
		return ((char *)h);
	while (i < l && h[i])
	{
		e = i;
		if (ft_checkif(n, h, e, l) == 1)
			return ((char *)h + i);
		i++;
	}
	return (NULL);
}