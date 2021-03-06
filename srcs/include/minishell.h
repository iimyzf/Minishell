/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:38:45 by azabir            #+#    #+#             */
/*   Updated: 2022/06/09 10:40:45 by azabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "../libft/libft.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>



typedef	struct s_cmd
{
	int				id;
	int				in;
	int				out;
	char			*cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int				in;
	int				out;
	int				fd[2];
	int				here_fd[2];
	char			*input;
	char			**full_cmd;
	char			**env;
	t_cmd			*cmd_list;
	int				p;
}	t_data;


typedef struct s_parser
{
	char	**infiles;
	char 	**heredoc;
	char	**outfiles;
	char	*commands;
	t_cmd	*cmd;
}	t_parser;

typedef struct s_lexer
{
	char			c;
	unsigned int	index;
	char			*data;
}	t_lexer;

t_lexer	*lexer_init(char *data);
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*lexer_collect_string(t_lexer *lexer, char c);
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
void	lstfree(t_cmd *lst);
char	*check_path(char	*cmd);
char	**ft_split(char const *s, char c);
void	ft_execve(char **cmd, char **env, char *path);
char	*ft_strjoin2(char *s1, char *s2);
void	heredoc(char	*cmd, t_data *data, int	is_last_here);
int		is_last_heredoc(t_cmd	*cmd);



#endif

