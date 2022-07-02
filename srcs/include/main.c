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
/*
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
*/
void	ft_parce(t_data *data)
{
	t_lexer	*lexer;
	t_token	*token;
	int		i;
	t_cmd	*temp;
	char	*tmp;

	i = 0;
	tmp = "";
	lexer = lexer_init(data->input);
	(data)->cmd_list = NULL;
	while ((token = lexer_get_next_token(lexer)) != NULL)
	{
		if (!((data)->cmd_list))
			(data)->cmd_list = ft_lstnew(token->value, token->type);
		else
			lstadd_back(&(data)->cmd_list, ft_lstnew(token->value, token->type));
		free(token);
	}
	lstadd_back(&(data)->cmd_list, ft_lstnew("", -1));
	temp = (data)->cmd_list;
	while (temp && (temp->id != -1))
	{
		while (temp && (temp->id != 8))
		{
			tmp = ft_strjoin2(tmp, temp->cmd);
			temp = temp->next;
		}
		if (temp)
			temp = temp->next;
		data->full_cmd = ft_split(tmp, ' ');
		free (tmp);
		i = 0;
		while (data->full_cmd[i])
		{
			printf("[%s] ", data->full_cmd[i]);
			i++;
		}
		free_array(data->full_cmd);
		printf("\n#######################\n");
	}
}


int main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (1);
	av[0] = "minishell> ";
	data.env = env;
	free (data.full_cmd);
	while (1)
	{
		data.input = readline(av[0]);
		add_history(data.input);
		if (!ft_strcmp(data.input, "exit"))
			break;
		ft_parce(&data);
	}
	//system("leaks minishell");
	return (0);
}