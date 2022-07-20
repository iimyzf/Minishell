/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:24:16 by azabir            #+#    #+#             */
/*   Updated: 2022/07/17 15:24:18 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_putchar(int *fd, char *input)
{
	int	i;
	int	pid;

	pid = fork();
	i = 0;
	if (pid == 0)
	{ 
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		while (input[i])
		{
			write(fd[1], &input[i], 1);
			i++;
		}
		exit(1);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	}

}

void	heredoc(char	*cmd, t_data *data)
{
	char	*input;

	pipe(data->fd);
	while (1)
	{
		input = readline("heredoc> ");
		if (!ft_strcmp(cmd, input))
			break;
		else
		{
			ft_putchar(data->fd, input);
		}
	}
}
