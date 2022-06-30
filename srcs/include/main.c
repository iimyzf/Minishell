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

void	free_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	lstprint(t_cmd	*cmd_list)
{
	t_cmd 	*temp;
	char	*path;
	char	*tmp;
	int		id;

	temp = cmd_list;
	while (temp && (temp->id != 1))
	{
		tmp = ft_strjoin2(tmp, temp->cmd);
		temp = temp->next;
	}
	temp = cmd_list;
	cmd_list->full_cmd = ft_split(tmp, ' ');
	free (tmp);
	if (path = check_path(cmd_list->full_cmd[0]), !path)
	{
		printf("minishell: %s: command not found\n", cmd_list->full_cmd[0]);
		return;
	}
	id = fork();
	if (id == 0)
		execve(path, cmd_list->full_cmd, NULL);
	else
		waitpid(id, NULL, 0);
	free(path);
	free_array(cmd_list->full_cmd);
}


int main(int ac, char **av, char **env)
{
	t_lexer	*lexer;
	t_token	*token;
	t_cmd	*cmd_list;
	char	*input;

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
		lstprint(cmd_list);
		free(input);
		free(lexer);
		lstfree(cmd_list);
	}
	free(input);
	free(lexer);
	system("leaks minishell");
	return (0);
}