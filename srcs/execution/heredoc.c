/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:24:16 by azabir            #+#    #+#             */
/*   Updated: 2022/08/26 17:33:52 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putchar(t_data *data, char *input, int exp)
{
	int	i;

	i = 0;
	(void) exp;
	while (input[i])
	{
		write(data->here_fd[1], &input[i], 1);
		i++;
	}
	write(data->here_fd[1], "\n", 1);
}

void	heredoc(char *cmd, t_data *data, int exp,int is_last_here)
{
	char	*input;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		fprintf(stderr, "cmd = [%s]\n", cmd);
		signal(SIGINT, child_sighand);
		while (1)
		{
			input = readline("heredoc> ");
			if (!input)
				exit(0);
			if (!ft_strcmp(cmd, input))
			{
				close (data->here_fd[1]);
				exit(0);
			}
			else if (is_last_here)
			{
				close (data->here_fd[0]);
				ft_putchar(data, input, exp);
			}
		}
	}
	free(cmd);
}
