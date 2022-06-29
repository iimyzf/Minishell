/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exucve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:34:29 by azabir            #+#    #+#             */
/*   Updated: 2022/06/29 11:34:30 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char	*cmd)
{
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
	else if (!ft_strcmp(cmd, "<<"))
		return (8);
	return (0);
}

void	ft_exucve(char **cmd, char **env, char *path)
{
	if (is_builtin(cmd[0]) == 1)
		ft_echo(cmd, env);
	else if (is_builtin(cmd[0]) == 2)
		ft_cd(cmd, env);
	else if (is_builtin(cmd[0]) == 3)
		ft_pwd(cmd, env);
	else if (is_builtin(cmd[0]) == 4)
		ft_export(cmd, env);
	else if (is_builtin(cmd[0]) == 5)
		ft_unset(cmd, env);
	else if (is_builtin(cmd[0]) == 6)
		ft_env(cmd, env);
	else if (is_builtin(cmd[0]) == 7)
		ft_exit(cmd, env);
	else if (is_builtin(cmd[0]) == 8)
		ft_herd(cmd, env);
	else
		sys_exuc(cmd, path);
}
