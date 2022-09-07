/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 02:16:37 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 21:43:24 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char *s1, char *s2)
{
	char	*ptr;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = 0;
	}
	if (!s1 || !s2)
		return (NULL);
	j = ft_strlen(s1) + ft_strlen (s2);
	ptr = malloc (sizeof(char) * j + 2);
	if (!ptr)
		return (NULL);
	j = 0;
	while (s1[j])
	{
		ptr[j] = s1[j];
		j++;
	}
	while (*s2)
		ptr[j++] = *s2++;
	ptr[j] = '\0';
	free (s1);
	return (ptr);
}
