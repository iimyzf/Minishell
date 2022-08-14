/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:34:25 by azabir            #+#    #+#             */
/*   Updated: 2022/08/14 09:50:50 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int	cmd_parts_count(t_cmd *cmd)
{
	int	count;

	count = 0;	
	while(cmd && cmd->id != 8 && cmd->id != -1)
	{
		if (cmd->id == 1 || cmd->id == 2 || cmd->id == 3 || cmd->id == 4)
			count -= 2;
		if (cmd->id != 14)
		{
			// if (cmd->id ==)
			count++;
		}
		cmd = cmd->next;
	}
	return(count);
}