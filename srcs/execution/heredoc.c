/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:24:16 by azabir            #+#    #+#             */
/*   Updated: 2022/08/08 16:47:48 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_putchar(t_data *data, char *input)
{
	int	i;
	int	pid;

	pid = fork();
	i = 0;
	if (pid == 0)
	{
		while (input[i])
		{
			write(data->here_fd[1], &input[i], 1);
			i++;
		}
		write(data->here_fd[1], "\n", 1);
		exit(0);
	}
}

void	heredoc(char	*cmd, t_data *data, int	is_last_here)
{
	char	*input;
	int		in;

	in = STDIN_FILENO;
	while (1)
	{
		input = readline("heredoc> ");
		if (!ft_strcmp(cmd, input))
		{
			if (is_last_here)
				close (data->here_fd[1]);
			break;
		}
		else if (is_last_here)
		{
			ft_putchar(data, input);
			waitpid(-1, NULL, 0);
		}
		if (input)
			free(input);
	}
}
