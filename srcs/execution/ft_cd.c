/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:49 by azabir            #+#    #+#             */
/*   Updated: 2022/08/17 18:03:26 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

void	set_old_pwd(t_data *data)
{
	char	*old_pwd;
	char	*tmp;
	int		index;

	old_pwd = getcwd(NULL, 0);
	index = return_index(data->env, "OLDPWD");
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	//free(old_pwd);
	data->env[index] = ft_strdup(tmp);
}

void	set_new_pwd(t_data *data)
{
	char	*new_pwd;
	char	*tmp;
	int		index;

	new_pwd = getcwd(NULL, 0);
	index = return_index(data->env, "PWD");
	tmp = ft_strjoin("PWD=", new_pwd);
	//free(new_pwd);
	data->env[index] = ft_strdup(tmp);
}

char	*get_from_env(t_data *data, char *str, int size, int start)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, size) == 0)
			return (data->env[i] + start);
		i++;
	}
	return (NULL);
}

void	go_to_env(t_data *data, char *path)
{
	int		ret;
	char	*tmp;

	set_old_pwd(data);
	tmp = path;
	ret = chdir(tmp);
	if (ret == -1)
		printf("minishel: cd: no such file or directory\n");
	set_new_pwd(data);
}

void	ft_cd(t_data *data, char *path)
{
	char	*env;

	if (!path)
	{
		env = get_from_env(data, "HOME=", 5, 5);
		if (!env)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
		if (env && !env[0])
		{
			chdir(".");
			return ;
		}
		go_to_env(data, env);
	}
	else
		go_to_env(data, path);
}

// void	ft_cd(char *path)
// {
// 	char	*buffer;
// 	char	*newdir;

// 	buffer = NULL;
// 	buffer = getcwd(buffer, 1024);
// 	printf("This is the old PWD: %s\n", buffer);
// 	newdir = path;
// 	if (chdir(newdir) == -1)
// 		printf("No such file or directory\n");
// 	else
// 	{
// 		buffer = getcwd(buffer, 1024);
// 		printf("This is the new PWD: %s\n", buffer);
// 	}
// }

// int	main(int ac, char **av)
// {
// 	char	*path;
// 	t_data	*data;
// 	int		i;

// 	i = 0;
// 	if (ac == 1)
// 		ft_cd(data, "~");
// 	else
// 	{
// 		path = av[1];
// 		ft_cd(data, path);
// 	}
// 	return (0);
// 	// char	*buffer;
// 	// char	*newdir;

// 	// if (ac == 1)
// 	// {
// 	// 	buffer = getcwd(buffer, 1024);
// 	// 	printf("%s\n", buffer);
// 	// }
// 	// else if (ac == 2)
// 	// {
// 	// 	newdir = av[1];
// 	// 	if (chdir(newdir) == -1)
// 	// 		printf("Error\n");
// 	// 	else
// 	// 	{
// 	// 		buffer = getcwd(buffer, 1024);
// 	// 		printf("%s\n", buffer);
// 	// 	}
// 	// }
// 	// return (0);
// }