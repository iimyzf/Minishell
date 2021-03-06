/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:57 by azabir            #+#    #+#             */
/*   Updated: 2022/06/13 19:20:59 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_pwd(void)
{
	char	*path;
	char	*buf;

	buf = NULL;
	path = NULL;
	while (path == NULL) {
		path = getcwd(buf, 1);
	}
	printf("%s\n", path);
	return(0);
}
