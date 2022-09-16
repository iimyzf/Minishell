/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:07 by azabir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/04 16:59:27 by yagnaou          ###   ########.fr       */
=======
/*   Updated: 2022/09/10 20:58:47 by yagnaou          ###   ########.fr       */
>>>>>>> master
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
	env_path = ft_divide(str, '=');
	while (data->env[i])
	{
		env2 = ft_divide(data->env[i], '=');
		if (!ft_strcmp(env2[0], env_path[0]))
		{
<<<<<<< HEAD
			free(env_path[i]);
			free(env2[i]);
=======
>>>>>>> master
			free(data->env[i]);
			data->env[i] = str;
			free_array(env_path);
			free_array(env2);
			return (1);
		}
<<<<<<< HEAD
		//free(env_path[i]);
		//free(env2[i]);
=======
		free_array(env2);
>>>>>>> master
		i++;
	}
	free(str);
	free_array(env_path);
<<<<<<< HEAD
	free_array(env2);
=======
>>>>>>> master
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
<<<<<<< HEAD
	return (new_env);
}

=======
	free_array(data->env);
	return (new_env);
}

int	ft_check(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

>>>>>>> master
int	check_syntax(char *str)
{
	char	**string;
	int		i;

	i = 1;
	string = ft_divide(str, '=');
	if (string[0] == NULL || !(ft_check(string[0][0]) || string[0][0] == '_'))
	{
		free_array(string);
		return (0);
	}
	while (string[0][i])
	{
<<<<<<< HEAD
		if ((!ft_isalnum(string[0][i]) && string[0][i] != '_'))
=======
		if (!(ft_isalnum(string[0][i])) && (string[0][i] != '_'))
>>>>>>> master
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
		{
			printf("error occured! check the syntax again!\n");
			g_exit_code = 1;
		}
		else
		{
			if (!check_if_exist(data, path[i]))
				data->env = add_to_list(data, path[i]);
		}
		i++;
	}
}
