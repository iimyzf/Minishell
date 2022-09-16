/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:25 by azabir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/04 15:58:58 by yagnaou          ###   ########.fr       */
=======
/*   Updated: 2022/09/10 21:06:19 by yagnaou          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_syntax_unset(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[0]) && str[0] != '_')
<<<<<<< HEAD
	{
		free(str);
=======
>>>>>>> master
		return (0);
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
<<<<<<< HEAD
		{
			free(str);
=======
>>>>>>> master
			return (0);
		i++;
	}
	return (1);
}

int	return_index(char **env, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_divide(env[i], '=');
		if (ft_strcmp(tmp[0], str) == 0)
		{
			free_array(tmp);
			return (i);
		}
		i++;
		free_array(tmp);
	}
	return (-1);
}

char	**delete_it(t_data *data, int index)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (data->env[i])
		i++;
	new = malloc(sizeof(char *) * i);
	if (!new)
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup(data->env[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free_array(data->env);
	return (new);
}

void	ft_unset(t_data *data, char **str)
{
	int		i;
	int		j;

	i = 0;
	if (!str)
		return ;
	else
	{
		while (str[i])
		{
			if (!check_syntax_unset(str[i]))
			{
				printf("error occured! check the syntax again!\n");
				g_exit_code = 1;
			}
			else
			{
				j = return_index(data->env, str[i]);
				if (j != -1)
					data->env = delete_it(data, j);
			}
			i++;
		}
	}
}
