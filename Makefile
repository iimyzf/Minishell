# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 11:27:39 by yagnaou           #+#    #+#              #
#    Updated: 2022/09/09 17:53:30 by yagnaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================================================================
# Color Variables
# =============================================================================

BLACK		=	"\033[1;30m"
GRAY		=	"\033[1;30m"
RED			=	"\033[1;31m"
GREEN		=	"\033[1;32m"
YELLOW		=	"\033[1;33m"
PURPLE		=	"\033[1;35m"
CYAN		=	"\033[1;36m"

# =============================================================================
# GCC & Flags Variables
# =============================================================================

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
READLINE	=	-lreadline -L /Users/yagnaou/goinfre/.brew/Cellar/readline/8.1.2/lib -I /Users/yagnaou/goinfre/.brew/Cellar/readline/8.1.2/include


# =============================================================================
# Name & File Names Variables
# =============================================================================

NAME		=	minishell
EXECUTION	=	srcs/execution/
INCLUDE		=	srcs/include/
LIBFT		=	srcs/libft/

SRCS		=	${EXECUTION}check_path.c		\
				${EXECUTION}ft_cd.c				\
				${EXECUTION}ft_echo.c			\
				${EXECUTION}ft_env.c			\
				${EXECUTION}ft_execve.c			\
				${EXECUTION}ft_exit.c			\
				${EXECUTION}ft_export.c			\
				${EXECUTION}ft_pwd.c			\
				${EXECUTION}ft_unset.c			\
				${EXECUTION}heredoc.c			\
				${EXECUTION}is_last_heredoc.c	\
				${EXECUTION}utils.c				\
				${INCLUDE}check_char.c			\
				${INCLUDE}check_heredoc.c		\
				${INCLUDE}check_last.c			\
				${INCLUDE}childs_sighand.c		\
				${INCLUDE}cmd_array_join.c		\
				${INCLUDE}cmd_create.c			\
				${INCLUDE}dollar.c				\
				${INCLUDE}fill_data_list.c		\
				${INCLUDE}lexer.c				\
				${INCLUDE}lexer1.c				\
				${INCLUDE}lexer2.c				\
				${INCLUDE}main.c				\
				${INCLUDE}parce_utils.c			\
				${INCLUDE}redirections_utils.c	\
				${INCLUDE}sighandl.c			\
				${INCLUDE}syntax_checker.c		\
				${INCLUDE}token.c				\
				${LIBFT}cmds_count.c			\
				${LIBFT}free_array.c			\
				${LIBFT}ft_calloc.c				\
				${LIBFT}ft_divide.c				\
				${LIBFT}ft_isalnum.c			\
				${LIBFT}ft_isdigit.c			\
				${LIBFT}ft_itoa.c				\
				${LIBFT}ft_lstadd_back_new.c	\
				${LIBFT}ft_lstadd_back.c		\
				${LIBFT}ft_lstnew_new.c			\
				${LIBFT}ft_lstnew.c				\
				${LIBFT}ft_putendl_fd.c			\
				${LIBFT}ft_splite.c				\
				${LIBFT}ft_strcat.c				\
				${LIBFT}ft_strchr.c				\
				${LIBFT}ft_strcmp.c				\
				${LIBFT}ft_strdup.c				\
				${LIBFT}ft_strjoin.c			\
				${LIBFT}ft_strjoin3.c			\
				${LIBFT}ft_strlen.c				\
				${LIBFT}ft_strncmp.c			\
				${LIBFT}ft_strnstr.c			\
				${LIBFT}get_next_char.c			\
				${LIBFT}is_buildin.c			\
				${LIBFT}is_special.c			\
				${LIBFT}lstfree.c				\
				${LIBFT}make_str.c				\
				${LIBFT}strjoin2.c				\
				${LIBFT}unclosed_quotes.c		\

OBJS		=	$(SRCS:.c=.o)

# =============================================================================
# Drawing o Dakchi Hahahahaha
# =============================================================================

define HEADER
         _                                                                      
        / \                     _                                               
        | |                    /_\                                              
        | |                   _   _                   _                         
        | |                  /_\ /_\                 /_\                _____   
 _      | |      ___      ___  ___  ___      ___     ___     ___       /     \  
/ \     |  \____/   \____/  |__| |__|  \____/   \___/   \___/   \_____/ _  O  \ 
\  \____/  \_____/ \_________________________/ \_____/ \_____/ \_______/ \____/ 
 \________/     _   _                       _   _            _   _              
               /_\ /_\                     /_\ /_\          /_\ /_\             

endef

export HEADER

# =============================================================================
# Rules
# =============================================================================

all			:	$(NAME)

$(NAME)		:	$(SRCS)
				@echo ${YELLOW}"---> Compiling \n$${HEADER}"
				@${CC} $(CFLAGS) ${READLINE} $(SRCS) -o $(NAME)
				@echo ${GREEN}"---> Compilation done."

clean		:
				@rm -rf $(OBJS)
				@echo ${PURPLE}"---> Cleaning object files..."
				@echo ${PURPLE}"---> Cleaned!"

fclean		:
				@rm -rf $(OBJS)
				@rm -rf $(NAME)
				@echo ${RED}"---> Cleaning ${NAME} with it's object files..."
				@echo ${RED}"---> All cleaned!"

re			:	fclean all