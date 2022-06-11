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
#include "parser.h"



void	lstprint(t_cmd	*cmd_list)
{
	t_cmd 	*temp;
	char	*path;

	temp = cmd_list;
	while (temp)
	{
		printf("id = %d | cmd = %s", temp->id, temp->cmd);
		if (temp->id == 0 && (path = check_path(temp->cmd), path))
		{
			printf(" | Valid cmd\n");
			execve(path, &(temp->cmd), NULL);
		}
		else if(temp->id == 0)
			printf(" | Invalid cmd\n");
		else
			printf (" | id != 0\n");
		temp = temp->next;
	}
}


int main(int ac, char **av, char **env)
{
	t_lexer	*lexer;
	t_token	*token;
	t_cmd	*cmd_list;
	char	*input;
	int		id;

	if (ac != 1)
		return (1);
	//just to mute the unsed parametrs warning 
	env = NULL;
	av[0] = "minishell> ";
	while (1)
	{
		// input is your input
		cmd_list = NULL;
		input = readline(av[0]);
		lexer = lexer_init(input);
		add_history(input);
		if (!ft_strcmp(input, "exit"))
			break;
		while ((token = lexer_get_next_token(lexer)) != NULL)
		{
			//printf("TOKEN ---> [id: %d,    value: %s]\n", token->type, token->value);
			if (!(cmd_list))
				cmd_list = ft_lstnew(token->value, token->type);
			else
				lstadd_back(&cmd_list, ft_lstnew(token->value, token->type));
			free(token);
		}
		free(input);
		id = fork();
		if(id == 0)
			lstprint(cmd_list);
		lstfree(&cmd_list);
		free(lexer);
		waitpid(id, NULL, 0);
	}
	free(input);
	free(lexer);
	system("leaks minishell");
	return (0);
}