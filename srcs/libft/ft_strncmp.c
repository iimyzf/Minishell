/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:18:16 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/17 17:52:05 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	if (!s1)
		return (strlen(s2));
	if (!s2)
		return (strlen(s1));
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	if (n != 0)
	{
		if (c1[0] == '\0' || c2[0] == '\0')
			return (c1[0] - c2[0]);
		while (i < n && (c1[i] || c2[i]))
		{
			if (c1[i] != c2[i])
				return (c1[i] - c2[i]);
			else
				i++;
		}
	}
	return (0);
}
