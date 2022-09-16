/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:34:29 by azabir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/04 16:00:58 by yagnaou          ###   ########.fr       */
=======
/*   Updated: 2022/09/08 13:58:19 by yagnaou          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execve(t_data *data, char *path)
{
<<<<<<< HEAD
	if (!ft_strcmp(data->full_cmd[0], "pwd") || !ft_strcmp(data->full_cmd[0], "PWD"))
		ft_pwd(data);
	else if (!ft_strcmp(data->full_cmd[0], "echo") || !ft_strcmp(data->full_cmd[0], "ECHO"))
		ft_echo(data->full_cmd + 1);
	else if ((!ft_strcmp(data->full_cmd[0], "env") || !ft_strcmp(data->full_cmd[0], "ENV")) && data->full_cmd[1] == NULL)
=======
	if (!ft_strcmp(data->full_cmd[0], "pwd")
		|| !ft_strcmp(data->full_cmd[0], "PWD"))
		ft_pwd(data);
	else if (!ft_strcmp(data->full_cmd[0], "echo")
		|| !ft_strcmp(data->full_cmd[0], "ECHO"))
		ft_echo(data->full_cmd + 1);
	else if ((!ft_strcmp(data->full_cmd[0], "env")
			|| !ft_strcmp(data->full_cmd[0], "ENV"))
		&& data->full_cmd[1] == NULL)
>>>>>>> master
		ft_env(data->env);
	else if (!ft_strcmp(data->full_cmd[0], "export")
		|| !ft_strcmp(data->full_cmd[0], "EXPORT"))
		ft_export(&data->full_cmd[1], data);
	else if (!ft_strcmp(data->full_cmd[0], "unset")
		|| !ft_strcmp(data->full_cmd[0], "UNSET"))
		ft_unset(data, &data->full_cmd[1]);
	else if (!ft_strcmp(data->full_cmd[0], "exit")
		|| !ft_strcmp(data->full_cmd[0], "EXIT"))
		ft_exit(data);
	else if (!ft_strcmp(data->full_cmd[0], "cd")
		|| !ft_strcmp(data->full_cmd[0], "CD"))
		ft_cd(data, data->full_cmd[1]);
	else
		execve(path, data->full_cmd, data->env);
}
