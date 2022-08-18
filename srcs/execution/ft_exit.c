/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:35 by azabir            #+#    #+#             */
/*   Updated: 2022/08/17 17:44:29 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "string.h"

int	ft_is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	error_print(t_data *data, char *str, int code)
{
	write(2, str, strlen(str));
	data->exit_code = code;
	return (code);
}

void	just_exit(t_data *data)
{
	write(2, "exit\n", 5);
	if (atoi(data->full_cmd[1]) >= 0 && (long) atoi(data->full_cmd[1]) < __LONG_MAX__)
	{
		data->exit_code = (unsigned int)atoi(data->full_cmd[1]) % 255;
		exit(data->exit_code);
	}
	else
	{
		data->exit_code = (unsigned int)atoi(data->full_cmd[1]) % 255;
		exit(data->exit_code);
	}
}

int	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	if (!data->full_cmd[1])
	{
		printf("exit\n");
		exit(data->exit_code);
	}
	if (!ft_is_all_num(data->full_cmd[1]))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", data->full_cmd[1]);
		exit(255);
	}
	while (data->full_cmd[i])
		i++;
	if (i != 2)
		return (error_print(data, "minishell: exit: too many arguments\n", 1));
	else
	{
		just_exit(data);
		printf("exit code : %d\n", data->exit_code);
	}
	return (1);
}

// int	main(int ac, char **av)
// {
// 	t_data	*data;
// 	int		i;

// 	i = 0;
// 	data = (t_data*)malloc(sizeof(t_data));
// 	data->full_cmd = av;
// 	data->exit_code = 0;
// 	ft_exit(data);
// 	return (0);
// }