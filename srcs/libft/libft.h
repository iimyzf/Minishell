/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:29:16 by yagnaou           #+#    #+#             */
/*   Updated: 2022/09/09 17:52:14 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "unistd.h"
# include "stdlib.h"

typedef struct s_lst
{
	char			*value;
	struct s_lst	*next;
}	t_lst;

size_t	ft_strlen(char *str);
char	*ft_strcat(char *str1, char *str2);
int		ft_strcmp(char *str1, char *str2);
int		ft_isalnum(char c);
char	*ft_strchr(char *s, int c);
void	*ft_calloc(int i, int s);
char	get_next_char(int pid);
char	*ft_strnstr(char *h, char *n, int l);
void	ft_lstadd_back_new(t_lst **lst, t_lst *new);
t_lst	*ft_lstnew_new(char *content);
int		ft_isdigit(int c);
int		ft_isalnum2(char c);
char	*ft_strdup(const char	*src);
char	**ft_divide(char *str, char c);

#endif