/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:38:45 by azabir            #+#    #+#             */
/*   Updated: 2022/09/08 17:10:26 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include "signal.h"
# include <sys/errno.h>

typedef struct s_cmd
{
	int				id;
	int				in;
	int				out;
	char			*cmd;
	char			*saved;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmd_list;
	int				in;
	int				out;
	int				active_proc;
	int				is_last;
	int				fd[2];
	char			**complete_path;
	int				here_fd[2];
	char			*input;
	char			**full_cmd;
	char			**env;
	int				counter;
	int				dollar;
	int				status;
	char			*saved;
	char			**exp;
	int				exit_code;
	int				redirect;
	int				saved_out;
	int				saved_in;
	int				pid;
	char			*pwd;
}	t_data;

typedef struct s_parser
{
	char	**infiles;
	char	**heredoc;
	char	**outfiles;
	char	*commands;
	t_cmd	*cmd;
}	t_parser;

typedef struct s_lexer
{
	char			c;
	char			next_c;
	unsigned int	index;
	char			*data;
}	t_lexer;

int	g_exit_code;

t_lexer	*lexer_init(char *data);
int		process(char *path, t_data *data);
char	*ft_itoa(int r);
int		parce_init(t_data *data);
int		is_redirec(t_data *data);
int		write_in(t_data *data, int append);
int		proce_create(t_data *data, char *path, t_cmd *temp);
int		read_from(t_data *data);
void	ft_wait(t_data *data, t_cmd *temp);
int		is_cmd(int id);
char	*lexer_collect_env_value(t_lexer *lexer, t_data *data);
int		redirec(int id);
int		read_from_here(t_data *data);
t_token	*next_tkn(t_lexer *lexer, t_data *data);
t_token	*clct_str(t_lexer *lexer, char c, int token);
t_token	*clct_dq_string(t_lexer *lexer, char c, t_data *data, int token);
t_token	*clct_id(t_lexer *lexer, t_data *data);
t_token	*nxt_tkn(t_lexer *lexer, t_token *token, int count);
t_token	*clct_env_str(t_lexer *lexer, t_data *data, int token);
char	*to_str(t_lexer *lexer);
char	*to_dstr(t_lexer *lexer);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	lexer_advance(t_lexer *lexer, int count);
int		cmd_create(t_data *data);
void	lexer_skip_white_spaces(t_lexer *lexer);
void	ft_strswap(char **str1, char **str2);
void	free_all(t_lexer *lexer);
char	*ft_strjoin(char const *s1, char const *s2);
char	*path_checker(t_data *data, char *cmd, char **env);
char	*check_env(t_data *data, char *cmd);
t_cmd	*ft_lstnew(char *value, int id, char *saved);
void	lstadd_back(t_cmd **cmd_list, t_cmd *cmd);
void	lstfree(t_cmd *lst);
int		is_special(char c);
int		unclosed_quotes(char	*input);
void	child_sighand(int sig);
char	*check_path(char	*cmd);
char	**ft_split(char *s, char c);
void	ft_execve(t_data *data, char *path);
char	*ft_strjoin2(char *s1, char *s2);
void	heredoc(char *cmd, t_data *data, int exp, int is_last_here);
int		is_last_heredoc(t_cmd	*cmd);
char	*cmd_array_join(char *cmd_part);
void	execution(char **lst);
int		check_heredoc(t_data *data);
int		ft_pwd(t_data *data);
int		cmd_parts_count(t_cmd *cmd);
void	path_errors(t_data *data);
int		ft_echo(char **env);
void	fill_data_list(t_data *data);
int		ft_exit(t_data *data);
int		ft_env(char	**arg);
void	ft_cd(t_data *data, char *path);
void	ft_export(char **path, t_data *data);
void	ft_add_env(t_data *data, char **env);
void	ft_strswap(char **str1, char **str2);
void	ft_unset(t_data *data, char **str);
char	*lexer_collect_alnum(t_lexer *lexer);
char	**cpy_env(char **env);
void	sort_this(char **tab);
int		is_buildin(char *cmd);
void	free_array(char **arr);
int		return_index(char **env, char *str);
int		check_char(char *cmd, char c);
char	*make_str(t_cmd *temp, int id);
void	dollar(t_data *data, char **cmd, int id);
int		syntax_checker(t_cmd *cmd, int here_count);
void	ft_print_sorted_env(char **env);
void	sighandl(int sig);
void	check_last(t_data *data);
char	*ft_strjoin3(char *s1, char *s2);

#endif
