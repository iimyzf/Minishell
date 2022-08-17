/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:07 by azabir            #+#    #+#             */
/*   Updated: 2022/08/15 14:35:51 by yagnaou          ###   ########.fr       */
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
			//free(env_path);
			//free(env2);
			//free(data->env[i]);
			data->env[i] = str;
			return (1);
		}
		i++;
	}
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
		//free(data->env[i]);
		i++;
	}
	new_env[i] = string;
	new_env[i + 1] = NULL;
	//free(data->env);f
	return (new_env);
}

int check_syntax(char *str)
{
	char	**string;
	int		i;

	i = 1;
	string = ft_split(str, '=');
	if (string[0] == NULL || (ft_isdigit(string[0][0]) && string[0][0] != '_'))
	{
		//free(string);
		return (0);
	}
	while (string[0][i])
	{
		if ((!ft_isalnum2(string[0][i]) && string[0][i] != '_'))
		{
			//free(string);
			return (0);
		}
		i++;
	}
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
			{
				printf("-------------------------------------->\n");
				data->env = add_to_list(data, path[i]);
			}
		}
		i++;
}
	// i = 0;
	// while (data->env[i])
	// {
	// 	printf("%s\n", data->env[i]);
	// 	i++;
	// }
}

// int main(int ac, char **av, char **env)
// {
// 	t_data	*data;
// 	(void)ac;
// 	(void)av;

// 	data = malloc(sizeof(t_data));
// 	data->env = cpy_env(env);
// 	av++;
// 	ft_export(av, data);
// 	ft_export(av, data);
// 	return (0);
// }