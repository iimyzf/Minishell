/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:35 by azabir            #+#    #+#             */
/*   Updated: 2022/07/22 21:15:52 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		printf("\n");
	if (ft_strcmp(cmd[1], "-n"))
	{
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
		}
		printf("\n");
	}
	else if (!ft_strcmp(cmd[1], "-n"))
	{
		i = 2;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
		}
	}
	return (0);
}