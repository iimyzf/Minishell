/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:35:58 by azabir            #+#    #+#             */
/*   Updated: 2022/06/09 10:36:00 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_path(char *path, char *cmd)
{
	char		*cmd_path;
	struct stat	buf;

	if(cmd_path = ft_strjoin(path, cmd), !stat(cmd_path, &buf))
	{
		free(cmd_path);
		return 1;
	}
	free(cmd_path);
	return(0);
}

int	check_path(char	*cmd)
{
	if(make_path("/bin/", cmd))
		return 1;
	if(make_path("/usr/bin/", cmd))
		return 1;
	if(make_path("/usr/local/bin/", cmd))
		return 1;
	if(make_path("/sbin/", cmd))
		return 1;
	if(make_path("/usr/sbin", cmd))
		return 1;
	if(make_path("/usr/local/munki/", cmd))
		return 1;
	return (0);
}