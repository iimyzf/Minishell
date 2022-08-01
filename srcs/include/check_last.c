/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:16:09 by azabir            #+#    #+#             */
/*   Updated: 2022/08/01 15:26:59 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_last(t_data *data)
{
	int		i;
	char	*str;
	
	i = 1;
	if (ft_isalnum(data->input[0]))
	{
		while(data->input[i + 1])
			i++;
		if (data->input[i] == '|')
		{
			str = readline("> ");
			data->input = ft_strjoin3(data->input, str);
			free(str);
		}
	}
}