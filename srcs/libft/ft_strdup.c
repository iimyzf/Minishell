/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:46:51 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/23 18:36:26 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*src)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
		i++;
	dst = (char *) malloc (sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	while (j < i)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}