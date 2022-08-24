/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:34:29 by azabir            #+#    #+#             */
/*   Updated: 2022/08/24 18:54:37 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*int	is_builtin(char	*cmd)
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
	if (!ft_strcmp(cmd, "<<"))
		return (8);
	return (0);
}*/

void	ft_execve(char **cmd, char **env, char *path, t_data *data)
{
	if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "PWD"))
		ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "ECHO"))
		ft_echo(cmd);
	else if ((!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "ENV")) && cmd[1] == NULL)
		ft_env(env);
	else if (!ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "EXPORT"))
		ft_export(&cmd[1], data);
	else if (!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "UNSET"))
		ft_unset(data, &cmd[1]);
	else if (!ft_strcmp(cmd[0], "exit") || !ft_strcmp(cmd[0], "EXIT"))
		ft_exit(data);
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "CD"))
		ft_cd(data, cmd[1]);
	else
		execve(path, cmd, env);
}

/*void	execution(char **lst)
{
	//t_env	*tmp;

	// tmp = *lst;
	printf("%s\n", lst[0]);
	if (!(ft_strcmp(lst[0], "pwd")))
	{
		write(2, "IM HERE\n", 9);
		ft_pwd();
	}
}*/
