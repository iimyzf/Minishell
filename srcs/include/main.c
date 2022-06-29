/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/06/12 10:37:23 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstprint(t_cmd	*cmd_list)
{
	t_cmd 	*temp;
	char	*path;
	char	**cmd;
	char	*tmp;

	temp = cmd_list;
	tmp = malloc(1);
	while (temp && (temp->id != 1))
	{
		tmp = ft_strjoin(tmp, temp->cmd);
		tmp = ft_strjoin(tmp, " ");
		temp = temp->next;
	}
	//printf("tmp : [ %s ]\n", tmp );
	temp = cmd_list;
	cmd = ft_split(tmp, ' ');
	if (path = check_path(cmd[0]), path)
	{
		execve(path, cmd, NULL);
	}
	else 
	{
		printf("minishell: %s: command not found\n", cmd[0]);
	}
	exit(1);
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
	//system("leaks minishell");
	return (0);
}