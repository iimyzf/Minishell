/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:37:34 by azabir            #+#    #+#             */
/*   Updated: 2022/08/31 19:37:39 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data, t_cmd *temp)
{
	int	status;

	while(data->active_proc > 0)
	{
		waitpid(-1, &status, 0);
		data->active_proc --;
		WIFEXITED(status);
		g_exit_code = (WEXITSTATUS(status));
	}
	dup2(data->saved_out, STDOUT_FILENO);
	dup2(data->saved_in, STDIN_FILENO);
	close (data->saved_out);
	close (data->saved_in);
	lstfree(temp);
}

int	is_cmd(int id)
{
	if((id == 0 || id == 6 || id == 9 || id == 7))
		return (1);
	return (0);
}