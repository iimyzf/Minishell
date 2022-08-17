/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:35:58 by azabir            #+#    #+#             */
/*   Updated: 2022/08/16 19:16:11 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

// char	*make_path(char *path, char *cmd)
// {
// 	char		*cmd_path;
// 	struct stat	buf;

// 	if(cmd_path = ft_strjoin(path, cmd), !stat(cmd_path, &buf))
// 	{
// 		return(cmd_path);
// 	}
// 	free(cmd_path);
// 	return(NULL);
// }

// char	*check_path(char	*cmd)
// {
// 	char	*path;
// 	struct stat buf;
	
// 	if (path = make_path("/bin/", cmd), path)
// 		return (path);
// 	if (path = make_path("/usr/bin/", cmd), path)
// 		return (path);
// 	if (path = make_path("/usr/local/bin/", cmd), path)
// 		return (path);
// 	if (path = make_path("/sbin/", cmd), path)
// 		return (path);
// 	if (path = make_path("/usr/sbin", cmd), path)
// 		return (path);
// 	if (path = make_path("/usr/local/munki/", cmd), path)
// 		return (path);
// 	if (!stat(cmd, &buf))
// 		return(ft_strjoin(cmd, ""));
// 	return (NULL);
// }

char	*path_checker(char *cmd, char **env)
{
	char	**complete_path;
	char	*cmd_path;
	char	*part_of_path;
	int		i;
	struct stat buf;

	i = 0;
	while (env[i] && strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	complete_path = ft_split(env[i] + 5, ':');
	i = 0;
	while (complete_path[i])
	{
		part_of_path = ft_strjoin(complete_path[i], "/");
		cmd_path = ft_strjoin(part_of_path, cmd);
		free(part_of_path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		else if (!stat(cmd, &buf))
			return(ft_strjoin(cmd, ""));
		i++;
	}
	return (0);
}
