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

void	heredoc(char	*cmd)
{
	char	*input;
	while (1)
	{
		input = readline("> ");
		if (!ft_strcmp(cmd, input))
			break;
	}
}
