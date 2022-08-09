/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:11:22 by azabir            #+#    #+#             */
/*   Updated: 2022/08/09 17:16:50 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_in_string();

char	*check_env(t_data *data, char *cmd)
{
	int		i;
	char	**env2;

	i = 0;
	while (data->env[i])
	{
		env2 = ft_split(data->env[i], '=');
		if (!ft_strcmp(env2[0], cmd))
			return (env2[1]);
		free_array(env2);
		i++;
	}
	return (NULL);
}


void	dollar(t_data *data, char **cmd, int id)
{
	(void) id;
	*cmd = check_env(data, *cmd);
	// fprintf(stderr, "cmd final = %s\n", *cmd);
}