/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:35:58 by azabir            #+#    #+#             */
/*   Updated: 2022/09/16 11:41:28 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*make_path(char *path, char *cmd)
{
	char		*cmd_path;
	struct stat	buf;

	cmd_path = ft_strjoin(path, cmd);
	if (!stat(cmd_path, &buf))
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

int	is_dir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*creat_path(t_data *data, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	*part_of_path;

	i = 0;
	while (data->complete_path[i])
	{
		part_of_path = ft_strjoin(data->complete_path[i], "/");
		cmd_path = ft_strjoin(part_of_path, cmd);
		free(part_of_path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_array(data->complete_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(data->complete_path);
	return (NULL);
}
