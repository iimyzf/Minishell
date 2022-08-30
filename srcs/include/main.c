/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:02 by yagnaou           #+#    #+#             */
/*   Updated: 2022/08/30 21:32:42 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process(char **cmd, char *path, t_data *data)
{
	pid_t	pid;

	pid = fork();

	if (pid == 0)
	{
		dup2(data->out, STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->saved_out);
		close(data->saved_in);
		ft_execve(cmd, data->env, path, data);
		exit(0);
	}
	else
	{
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		close(data->out);
	}
}

void	ft_parce(t_data *data)
{

	t_cmd	*temp;
	char	*path;
	int		status;
	int		status1;
	int		open_proce;

	fill_data_list(data);
	temp = (data)->cmd_list;
	if (!syntax_checker(temp))
		return ;
	if (!check_heredoc(data))
		return ;
	temp = (data)->cmd_list;
	data->in = 0;
	data->out = 1;
	open_proce = 0;
	status1 = 0;
	data->saved_out = dup(STDOUT_FILENO);
	data->saved_in = dup(STDIN_FILENO);
	while (data->cmd_list && (data->cmd_list->id != -1))
	{
		cmd_create(data);
		//temp = data->cmd_list;

		if (data->cmd_list->id == 8)
		{
			pipe(data->fd);
			if (status == 0)
				data->out = data->fd[1];
			data->in = data->fd[0];
			//temp = temp->next;
			status1 = 2;
 		}
		else if (data->full_cmd[0] && is_buildin(data->full_cmd[0]) && temp->id == -1 && status1 != 2)
		{
			dup2(data->out, STDOUT_FILENO);
			if (!ft_strcmp(data->full_cmd[0], "pwd"))
				ft_pwd();
			else if (!ft_strcmp(data->full_cmd[0], "echo"))
				ft_echo(data->full_cmd);
			else if (!ft_strcmp(data->full_cmd[0], "env") && data->full_cmd[1] == NULL)
				ft_env(data->env);
			else if (!ft_strcmp(data->full_cmd[0], "export"))
				ft_export(&data->full_cmd[1], data);
			else if (!ft_strcmp(data->full_cmd[0], "unset"))
					ft_unset(data, data->full_cmd);
			else if (!ft_strcmp(data->full_cmd[0], "exit"))
					ft_exit(data);
			else if (!ft_strcmp(data->full_cmd[0], "cd"))
					ft_cd(data, data->full_cmd[1]);
			status1 = 1;
		}
		data->cmd_list = data->cmd_list->next;
		path = path_checker(data->full_cmd[0], data->env);
		if (data->full_cmd[0] && (!path && !is_buildin(data->full_cmd[0])))
		{
			printf("minishell: %s: command not found\n", data->full_cmd[0]);
			data->exit_code = 127;
		}
			if (temp && temp->id == -1)
			{
				pipe(data->fd);
				if (status == 0)
					data->out = 1;
				data->in = data->fd[0];
			}
			if (data->full_cmd[0] != NULL && status1 != 1)
			{
				process(data->full_cmd, path, data);
				open_proce ++;
			}
		free(path);
		free_array(data->full_cmd);
	}
	while(open_proce > 0)
	{
		waitpid(-1, &status, 0);
		open_proce --;
		WIFEXITED(status);
		data->exit_code = (WEXITSTATUS(status));
	}
	dup2(data->saved_out, STDOUT_FILENO);
	dup2(data->saved_in, STDIN_FILENO);
	close (data->saved_out);
	close (data->saved_in);
}

int main(int ac, char **av, char **env)
{

	t_data	data;
	if (ac != 1)
		return (1);
	av[0] = "minishell-1.0$ ";
	data.env = env;
	data.in = 1;
	signal(SIGINT, sighandl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data.input = readline(av[0]);
		if (!data.input)
		{
			//system("leaks minishell");
			exit(0);
		}
		if (data.input[0] && !unclosed_quotes(data.input))
		{
			//check_last(&g_data);
			add_history(data.input);
			ft_parce(&data);
		}
		free (data.input);
	}
	system("leaks minishell");
	return (0);
}



/*  TO DO */

/*
	# << ok <<
	# leaks handle
	# permissions
	# pwd | ls | ls -la | cat > $PWD | chokran ela had | echo "Hello| World" (ikhan)
	# protect open
	# '   gbghggh | ghgh ' (seg) --> done
	# '' or "" should print cmd not found!
	# echo ">>" ''| ls >> l (hhhhhhhhh) --> HAHAHA DONE
	# echo -n  bbb hello>>g (hhh)
	# exit status
	# memory protections
	# errors handle
	# echo dd > "ff"ff (collect file name)
	# readline + CTRL-C
	# remove forbiden funcs like calloc and fprintf
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
