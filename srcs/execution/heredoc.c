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


void ft_putchar(t_data *data, char *input)
{
	int	i;
	int	pid;

	pid = fork();
	i = 0;
	if (pid == 0)
	{
		close(data->here_fd[0]);
		dup2(data->here_fd[1], STDOUT_FILENO);
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

	printf("last = %d\n", is_last_here);
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
		free(input);
	}
}
