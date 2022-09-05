/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:57 by azabir            #+#    #+#             */
/*   Updated: 2022/09/05 21:01:40 by yagnaou          ###   ########.fr       */
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
			free(data->pwd);
		data->pwd = ft_strdup(path);
		free(path);
	}
	printf("%s\n", data->pwd);
	return (0);
}
