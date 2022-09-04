/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:57 by azabir            #+#    #+#             */
/*   Updated: 2022/09/04 15:12:21 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		if (data->pwd != NULL)
			free (data->pwd);
		data->pwd = ft_strdup(path);
	}
	printf("%s\n", data->pwd);
	free(data->pwd);
	free(path);
	return (0);
}
