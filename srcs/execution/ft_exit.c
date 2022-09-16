/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:21:35 by azabir            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/04 14:59:11 by yagnaou          ###   ########.fr       */
=======
/*   Updated: 2022/09/08 13:53:13 by yagnaou          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9' && str[i] != '-'
<<<<<<< HEAD
			&& str[i] != '+' && str[i] != '#'))
=======
				&& str[i] != '+' && str[i] != '#'))
>>>>>>> master
			return (0);
		i++;
	}
	return (1);
}

int	error_print(char *str, int code)
{
	write(2, str, ft_strlen(str));
	g_exit_code = code;
	return (code);
}

void	just_exit(t_data *data)
{
	write(2, "exit\n", 5);
	if (atoi(data->full_cmd[1]) >= 0
		&& (long) atoi(data->full_cmd[1]) < __LONG_MAX__)
	{
		g_exit_code = (unsigned int)atoi(data->full_cmd[1]) % 256;
		exit(g_exit_code);
	}
	else
	{
		g_exit_code = (unsigned int)atoi(data->full_cmd[1]) % 256;
		exit(g_exit_code);
	}
}

int	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	if (!data->full_cmd[1])
	{
		printf("exit\n");
		exit(g_exit_code);
	}
	if (!ft_is_all_num(data->full_cmd[1]) && (data->full_cmd[1][1] == '\0'
		|| data->full_cmd[1][1] == '-' || data->full_cmd[1][1] == '+'
		|| !(data->full_cmd[1][1] >= '0' && data->full_cmd[1][1] <= '9')))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n",
			data->full_cmd[1]);
		exit(255);
	}
	while (data->full_cmd[i])
		i++;
	if (i != 2)
		return (error_print("minishell: exit: too many arguments\n", 1));
	else
		just_exit(data);
	return (1);
}
