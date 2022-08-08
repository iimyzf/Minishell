/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:41:26 by azabir            #+#    #+#             */
/*   Updated: 2022/08/08 00:14:00 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*make_str(t_cmd *temp, int id)
{
	char	*str;
	t_cmd	*tmp;
	

	tmp = temp;
	//tmp = tmp->next;
	//str = malloc(1);
	str = "";
	fprintf(stderr, "tmp->id = %d\n", id);
	while (tmp->id != id)
	{
		fprintf(stderr, "tmp->cmd = %s\n", tmp->cmd);
		str = ft_strjoin3(str, tmp->cmd);
		tmp = tmp->next;
		write (1, "here\n", 5);
	}
	fprintf(stderr, "str = %s\n", str);
	//tmp = tmp->next;
	temp = tmp;
	return(str);
}