/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:07 by azabir            #+#    #+#             */
/*   Updated: 2022/09/04 20:47:31 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_exist(t_data *data, char *path)
{
	char	**env_path;
	char	**env2;
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup(path);
	env_path = ft_split(str, '=');
	while (data->env[i])
	{
		env2 = ft_split(data->env[i], '=');
		if (!ft_strcmp(env2[0], env_path[0]))
		{
			free(data->env[i]);
			data->env[i] = str;
			free_array(env_path);
			free_array(env2);
			return (1);
		}
		free_array(env2);
		i++;
	}
	free(str);
	free_array(env_path);
	return (0);
}

char	**add_to_list(t_data *data, char *str)
{
	char	**new_env;
	char	*string;
	int		i;

	i = 0;
	string = ft_strdup(str);
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[i] = string;
	new_env[i + 1] = NULL;
	free_array(data->env);
	return (new_env);
}

int	check_syntax(char *str)
{
	char	**string;
	int		i;

	i = 1;
	string = ft_split(str, '=');
	if (string[0] == NULL || (ft_isdigit(string[0][0]) && string[0][0] != '_'))
	{
		free_array(string);
		return (0);
	}
	while (string[0][i])
	{
		if ((!ft_isalnum(string[0][i]) && string[0][i] != '_'))
		{
			free_array(string);
			return (0);
		}
		i++;
	}
	free_array(string);
	return (1);
}

void	ft_export(char **path, t_data *data)
{
	int		i;

	i = 0;
	if (path[0] == NULL)
	{
		ft_print_sorted_env(data->env);
		return ;
	}
	while (path[i])
	{
		if (!check_syntax(path[i]))
			printf("error occured! check the syntax again!\n");
		else
		{
			if (!check_if_exist(data, path[i]))
				data->env = add_to_list(data, path[i]);
		}
		i++;
	}
}
