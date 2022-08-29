/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:41:26 by azabir            #+#    #+#             */
/*   Updated: 2022/08/29 19:45:03 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*make_str(t_cmd *temp, int id)
{
	char	*str;
	t_cmd	*tmp;
	

	tmp = temp;
	str = "";
	while (tmp->id != id)
	{
		str = ft_strjoin3(str, tmp->cmd);
		tmp = tmp->next;
	}
	temp = tmp;
	return(str);
}