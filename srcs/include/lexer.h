/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:07:54 by yagnaou           #+#    #+#             */
/*   Updated: 2022/06/05 18:23:28 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

typedef	struct s_cmd
{
	int				id;
	char			*cmd;
	struct s_cmd	*next;
}	t_cmd;


typedef struct s_lexer
{
	char			c;
	unsigned int	index;
	char			*data;
}	t_lexer;

t_lexer	*lexer_init(char *data);
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*lexer_collect_string(t_lexer *lexer);
t_token	*lexer_collect_id(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token, int count);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
char	*lexer_get_current_char_as_two_strings(t_lexer *lexer);
void	lexer_advance(t_lexer *lexer, int count);
void	lexer_skip_white_spaces(t_lexer *lexer);
void	free_all(t_lexer *lexer);
char	*ft_strjoin(char const *s1, char const *s2);
t_cmd	*ft_lstnew(char *value, int id);
void	lstadd_back(t_cmd **cmd_list, t_cmd *cmd);
void	lstfree(t_cmd **lst);
char	*check_path(char	*cmd);

#endif