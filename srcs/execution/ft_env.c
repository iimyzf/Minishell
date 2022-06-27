/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:55 by azabir            #+#    #+#             */
/*   Updated: 2022/06/13 19:21:56 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char	**env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return(1);
}
