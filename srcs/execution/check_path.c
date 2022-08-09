/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:35:58 by azabir            #+#    #+#             */
/*   Updated: 2022/08/09 15:35:30 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*make_path(char *path, char *cmd)
{
	char		*cmd_path;
	struct stat	buf;

	if(cmd_path = ft_strjoin(path, cmd), !stat(cmd_path, &buf))
	{
		return(cmd_path);
	}
	free(cmd_path);
	return(NULL);
}

char	*check_path(char	*cmd)
{
	char	*path;
	struct stat buf;
	
	if (path = make_path("/bin/", cmd), path)
		return (path);
	if (path = make_path("/usr/bin/", cmd), path)
		return (path);
	if (path = make_path("/usr/local/bin/", cmd), path)
		return (path);
	if (path = make_path("/sbin/", cmd), path)
		return (path);
	if (path = make_path("/usr/sbin", cmd), path)
		return (path);
	if (path = make_path("/usr/local/munki/", cmd), path)
		return (path);
	if (!stat(cmd, &buf))
		return(ft_strjoin(cmd, ""));
	return (NULL);
}
