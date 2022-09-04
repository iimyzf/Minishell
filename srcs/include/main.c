/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/30 21:40:19 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exuce_built(t_data *data,t_cmd *temp)
{
	if (data->redirect)
		dup2(data->out, STDOUT_FILENO);
	ft_execve(data, NULL);
	close(data->in);
	close(data->out);
	lstfree(temp);
	free_array(data->full_cmd);
	ft_wait(data);
}

int	process(char *path, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		g_exit_code = 1;
		return (0);
	}
	if (pid == 0)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->in);
		ft_execve(data, path);
		exit(0);
	}
	close(data->out);
	dup2(data->in, STDIN_FILENO);
	close (data->in);
	return (1);
}

void	ft_parce(t_data *data)
{
	t_cmd	*temp;
	char	*path;
	int		status;

	status = -1;
	fill_data_list(data);
	temp = (data)->cmd_list;
	/*while (temp->id != -1)
	{
		fprintf(stderr, "check [%s] of id[%d]\n", temp->cmd, temp->id);
		temp = temp->next;
	}*/
	if (!syntax_checker((data)->cmd_list) || !check_heredoc(data))
	{
		lstfree(temp);
		return ;
	}
	//(data)->cmd_list = temp;
	data->saved_out = dup(STDOUT_FILENO);
	data->saved_in = dup(STDIN_FILENO);
	data->active_proc = 0;
	while (data->cmd_list && (data->cmd_list->id != -1))
	{
		pipe(data->fd);
		data->out = data->fd[1];
		data->in = data->fd[0];
		if (cmd_create(data))
		{
			if (is_buildin(data->full_cmd[0]) && data->cmd_list->id != 8 && status == -1)
				return (exuce_built(data, temp));
			status = 0;
			path = path_checker(data, data->full_cmd[0], data->env);
			if (!path)
			{
				g_exit_code = 127;
				if (check_char(data->full_cmd[0], '/'))
					printf("minishell: %s: No such file or directory\n", data->full_cmd[0]);
				else
					printf("minishell: %s: command not found\n", data->full_cmd[0]);
			}
			if (data->cmd_list->id != -1)
				data->cmd_list = data->cmd_list->next;
			if (data->cmd_list && data->cmd_list->id == -1 && !data->redirect)
			{
				data->out = 1;
				close (data->fd[1]);
			}
			if (data->full_cmd[0] != NULL)
			{
				if (process(path, data))
					data->active_proc += 1;
				else
				{
					free(path);
					free_array(data->full_cmd);
					dup2(data->saved_out, STDOUT_FILENO);
					dup2(data->saved_in, STDIN_FILENO);
					close (data->saved_out);
					close (data->saved_in);
					break;
				}
			}
			free(path);
		}
		else if (data->cmd_list->id != -1)
			data->cmd_list = data->cmd_list->next;
		free_array(data->full_cmd);
	}
	free (data->saved);
	ft_wait(data);
	lstfree(temp);
}

int main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (1);
	av[0] = "minishell-1.0$ ";
	data.env = env;
	signal(SIGINT, sighandl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data.input = readline(av[0]);
		if (!data.input)
			exit(0);
		if (data.input[0] && !unclosed_quotes(data.input))
		{
			add_history(data.input);
			ft_parce(&data);
		}
		free (data.input);
	}
	return (0);
}



/*  TO DO */

/*
	# removing Leaks from prcing --> doing
	# removing Leaks from exuc
	# permissions
	# echo -n  bbb hello>>g (hhh)
	# exit status
	# test memory protections
	# errors handle
	# $PWD then $?
	# remove forbiden funcs like calloc and fprintf
	# readline + CTRL-C -- > done
	# echo dd > "ff"ff (collect file name) --> done
	# pwd | ls | ls -la | cat > $PWD | chokran ela had | echo "Hello| World" (ikhan) --> done
	# protect open --> done
	# '   gbghggh | ghgh ' (seg) --> done
	# '' or "" should print cmd not found! --> done
	# echo ">>" ''| ls >> l (hhhhhhhhh) --> HAHAHA DONE
	# cat<<$USER"" (expand in heredoc) --> done
	#  echo $USER$USER$USER --> done
	# unclosed qoutes protect --> done
	# remove unused TOKENS --> done
	# empty cmd handle --> done
	# complete isalnum --> done
	# handel dollar sign in lexer --> done
	# fix path checking (check from env) --> done
	# $cmd --> done
	# path protect  --> done
	# echo "hello">"gg" --> done
	# remove split --> done
	# << << error  --> done
	# signal should close heredoc --> done
	# $ sign protect --> done
	# grep not woking --> done
	# handel last pipewith no cmd --> done
	# handel error syntax (special carrachters with no options) --> done
	# exuce minishell in  minishell --> done 
	# (ls | top) hang --> done
*/
