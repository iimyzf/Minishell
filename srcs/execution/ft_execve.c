/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:34:29 by azabir            #+#    #+#             */
/*   Updated: 2022/08/25 21:59:36 by azabir           ###   ########.fr       */
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

void	ft_execve(t_data *data, char *path)
{
	if (!ft_strcmp(data->full_cmd[0], "pwd") || !ft_strcmp(data->full_cmd[0], "PWD"))
		ft_pwd();
	else if (!ft_strcmp(data->full_cmd[0], "echo") || !ft_strcmp(data->full_cmd[0], "ECHO"))
		ft_echo(data->full_cmd);
	else if ((!ft_strcmp(data->full_cmd[0], "env") || !ft_strcmp(data->full_cmd[0], "ENV")) && data->full_cmd[1] == NULL)
		ft_env(data->env);
	else if (!ft_strcmp(data->full_cmd[0], "export") || !ft_strcmp(data->full_cmd[0], "EXPORT"))
		ft_export(&data->full_cmd[1], data);
	else if (!ft_strcmp(data->full_cmd[0], "unset") || !ft_strcmp(data->full_cmd[0], "UNSET"))
		ft_unset(data, &data->full_cmd[1]);
	else if (!ft_strcmp(data->full_cmd[0], "exit") || !ft_strcmp(data->full_cmd[0], "EXIT"))
		ft_exit(data);
	else if (!ft_strcmp(data->full_cmd[0], "cd") || !ft_strcmp(data->full_cmd[0], "CD"))
		ft_cd(data, data->full_cmd[1]);
	else
		execve(path, data->full_cmd, data->env);
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
