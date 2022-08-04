/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:35 by azabir            #+#    #+#             */
/*   Updated: 2022/08/04 01:22:08 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		printf("\n");
	else if (ft_strcmp(cmd[1], "-n"))
	{
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (!ft_strcmp(cmd[1], "-n"))
	{
		i = 2;
		while (cmd[i])
		{
			printf(" %s", cmd[i]);
			i++;
		}
	}
	return (0);
}