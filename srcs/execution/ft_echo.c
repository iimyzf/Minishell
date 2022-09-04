/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:35 by azabir            #+#    #+#             */
/*   Updated: 2022/09/04 14:57:09 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_str(char **str, int n)
{
	int	i;

	i = n;
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (str[i])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
}

void	check_for_n(char **str, int i, int j)
{
	while (str[i])
	{
		if (str[i][0] != '-')
		{
			print_str(str, i);
			return ;
		}
		j = 1;
		while (str[i][j])
		{
			if (str[i][j] != 'n')
			{
				print_str(str, i);
				return ;
			}
			j++;
		}
		if (str[i][j - 1] == '-')
		{
			print_str(str, i);
			return ;
		}
		i++;
	}
}

int	ft_echo(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str[0])
	{
		printf("\n");
		return (1);
	}
	if (str[0][0] == '-')
		check_for_n(str, i, j);
	else
		print_str(str, 0);
	return (0);
}
