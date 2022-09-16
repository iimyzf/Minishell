/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:57 by azabir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/04 15:12:21 by yagnaou          ###   ########.fr       */
=======
/*   Updated: 2022/09/05 21:01:40 by yagnaou          ###   ########.fr       */
>>>>>>> master
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
<<<<<<< HEAD
			free (data->pwd);
		data->pwd = ft_strdup(path);
	}
	printf("%s\n", data->pwd);
	free(data->pwd);
	free(path);
=======
			free(data->pwd);
		data->pwd = ft_strdup(path);
		free(path);
	}
	printf("%s\n", data->pwd);
>>>>>>> master
	return (0);
}
