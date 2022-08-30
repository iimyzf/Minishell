/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:35 by azabir            #+#    #+#             */
/*   Updated: 2022/08/30 19:22:12 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	just_n(char *cmd)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	write_space(char **cmd, int i)
{
	if (cmd[i + 1])
		printf(" ");
}

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		printf("\n");
	else if (cmd[1][0] == '-' && just_n(cmd[1]))
	{
		i++;
		while (cmd[i] != NULL)
		{
			printf("%s", cmd[i]);
			write_space(cmd, i);
			i++;
		}
	}
	else
	{
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			write_space(cmd, i);
			i++;
		}
		printf("\n");
	}
	return (0);
}
