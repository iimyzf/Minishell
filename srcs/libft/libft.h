/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:29:16 by yagnaou           #+#    #+#             */
/*   Updated: 2022/06/04 18:15:17 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "unistd.h"
# include "stdlib.h"

size_t	ft_strlen(char *str);
char	*ft_strcat(char *str1, char *str2);
int		ft_strcmp(char *str1, char *str2);
int		ft_isalnum(char c);
char	get_next_char(int pid);

#endif