/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:20:49 by azabir            #+#    #+#             */
/*   Updated: 2022/09/10 21:08:04 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_old_pwd(t_data *data)
{
	char	*old_pwd;
	char	*tmp;
	int		index;
	char	**tmp2;

	old_pwd = getcwd(NULL, 0);
	index = return_index(data->env, "OLDPWD");
	if (index == -1)
	{
		tmp2 = malloc(sizeof(char *) * 2);
		tmp2[0] = "OLDPWD=";
		tmp2[1] = NULL;
		ft_export(tmp2, data);
		free(tmp2);
		index = return_index(data->env, "OLDPWD");
	}
	if (old_pwd)
		tmp = ft_strjoin("OLDPWD=", old_pwd);
	else
		tmp = ft_strjoin("OLDPWD=", data->env[index] + 7);
	free(data->env[index]);
	data->env[index] = ft_strdup(tmp);
	free(old_pwd);
	free(tmp);
}

void	set_new_pwd(t_data *data)
{
	char	*new_pwd;
	char	*tmp;
	int		index;
	char	**tmp2;

	new_pwd = getcwd(NULL, 0);
	index = return_index(data->env, "PWD");
	if (index == -1)
	{
		tmp2 = malloc(sizeof(char *) * 2);
		tmp2[0] = "PWD=";
		tmp2[1] = NULL;
		ft_export(tmp2, data);
		free(tmp2);
		index = return_index(data->env, "PWD");
	}
	if (new_pwd)
		tmp = ft_strjoin("PWD=", new_pwd);
	else
		tmp = ft_strjoin("PWD=", data->env[index] + 4);
	free(data->env[index]);
	data->env[index] = ft_strdup(tmp);
	free(new_pwd);
	free(tmp);
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

	set_old_pwd(data);
	ret = chdir(path);
	if (ret == -1)
	{
		printf("minishel: cd: no such file or directory\n");
		g_exit_code = 1;
	}
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
			g_exit_code = 1;
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
	{
		go_to_env(data, path);
	}
}
