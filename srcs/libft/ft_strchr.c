/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:23:21 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 18:23:25 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*k;
	char	m;

	i = 0;
	m = c;
	k = (char *)s;
	while (*s)
	{
		if (*s == m)
			return (k + i);
		else
			i++;
		s++;
	}
	if (*s == c)
		return (k + i);
	return (0);
}
