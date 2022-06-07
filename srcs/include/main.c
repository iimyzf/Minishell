/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/06/05 18:28:49 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int main(int ac, char **av, char **env)
{
	t_lexer	*lexer;
	t_token	*token;
	char	*cmd;

	if (ac != 1)
		return (1);
	//just to mute the unsed parametrs warning 
	env = NULL;
	av[0] = "minishell> ";
	while (1)
	{
		// cmd is your input
		cmd = readline(av[0]);
		lexer = lexer_init(cmd);
		add_history(cmd);
		if (!ft_strcmp(cmd, "exit"))
			break;
		while ((token = lexer_get_next_token(lexer)) != NULL)
		{
			printf("TOKEN ---> [id: %d,    value: %s]\n", token->type, token->value);
			free(token->value);
			free(token);
		}
	}
	//system("leaks minishell");
	return (0);
}