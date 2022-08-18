/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_sighand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <azabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:57:52 by azabir            #+#    #+#             */
/*   Updated: 2022/08/18 17:27:20 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_sighand(int sig)
{
	if (sig == SIGINT)
	{
		fprintf(stderr, "from child %d\n", getpid());
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		(void) sig;
	}	
}
