/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_buildin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:57:02 by azabir            #+#    #+#             */
/*   Updated: 2022/07/30 10:58:16 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_buildin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (2);
	else if (!ft_strcmp(cmd, "pwd"))
		return (3);
	else if (!ft_strcmp(cmd, "export"))
		return (4);
	else if (!ft_strcmp(cmd, "unset"))
		return (5);
	else if (!ft_strcmp(cmd, "env"))
		return (6);
	else if (!ft_strcmp(cmd, "exit"))
		return (7);
	if (!ft_strcmp(cmd, "<<"))
		return (8);
	return (0);
}
