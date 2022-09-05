/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:11:22 by azabir            #+#    #+#             */
/*   Updated: 2022/08/30 22:21:45 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(t_data *data, char *cmd)
{
	int		i;
	char	**env2;
	char	*value;

	i = 0;
	value = NULL;
	if (*cmd == '?')
	{
		value = ft_itoa(g_exit_code);
		return (ft_strjoin2(value, cmd + 1));
	}
	while (data->env[i])
	{
		env2 = ft_split(data->env[i], '=');
		if (!ft_strcmp(env2[0], cmd))
		{
			value = ft_strdup(env2[1]);
			free_array(env2);
			return (value);
		}
		free_array(env2);
		i++;
	}
	return (value);
}

void	dollar(t_data *data, char **cmd, int id)
{
	(void) id;
	*cmd = check_env(data, *cmd);
}
