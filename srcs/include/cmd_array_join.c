/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 22:14:58 by azabir            #+#    #+#             */
/*   Updated: 2022/08/13 18:02:09 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cmd_array_join(char *cmd_part)
{
	char	*cmd;
	int		i;

	cmd = malloc(sizeof(char) * ft_strlen(cmd_part) + 1);
	i = 0;
	while(cmd_part && cmd_part[i])
	{
		cmd[i] = cmd_part[i];
		i++;
	}
	cmd[i] = 0;
	return(cmd);
}