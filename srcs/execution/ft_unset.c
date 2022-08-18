/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:25 by azabir            #+#    #+#             */
/*   Updated: 2022/08/17 17:45:59 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_syntax_unset(char *str)
{
	int		i;

	i = 1;
	if (ft_isdigit(str[0]) && str[0] != '_')
	{
		//free(str);
		return (0);
	}
	while (str[i])
	{
		if ((!ft_isalnum2(str[i]) && str[i] != '_'))
		{
			//free(string);
			return (0);
		}
		i++;
	}
	return (1);
}

int	return_index(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (i);
		i++;
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
	printf("---------------------------> INDEX: %d\n", index);
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
				printf("error occured! check the syntax again!\n");
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