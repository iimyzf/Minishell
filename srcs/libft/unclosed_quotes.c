/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:28:24 by azabir            #+#    #+#             */
/*   Updated: 2022/09/07 18:28:51 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unclosed_quotes(char	*input)
{
	int		i;
	char	c;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			c = input[i];
			i++;
			while (input[i] != c)
			{
				if (input[i] == '\n' || input[i] == 0)
				{
					write (2, "minishell: unclosed Quotes\n", 27);
					return (1);
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}
