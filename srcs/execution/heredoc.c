/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:24:16 by azabir            #+#    #+#             */
/*   Updated: 2022/08/26 23:03:12 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*make_alnume(char *str, int	*i)
{
	char	*cmd;
	int		j;
	
	j = *i;
	while (str[j] && ft_isalnum(str[j]))
		j++;
	cmd = malloc(sizeof(char) * (j - (*i) + 1));
	j = 0;
	while (str[*i] && ft_isalnum(str[*i]))
	{
		cmd[j] = str[*i];
		*i += 1;
		j++;
	}
	cmd[j] = 0;
	//*i -= 1;
	return (cmd);
}

void	ft_putchar(t_data *data, char *input, int exp)
{
	int		i;
	char	*cmd;
	char	*str;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && ft_isalnum(input[i + 1]) && exp)
		{
			i++;
			str = make_alnume(input, &i);
			cmd = check_env(data, str);
			free(str);
			while(cmd && *cmd)
			{
				write(data->here_fd[1], &(*cmd), 1);
				cmd++;
			}
		}
		write(data->here_fd[1], &input[i], 1);
		if (input[i])
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
