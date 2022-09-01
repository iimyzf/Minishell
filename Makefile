# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azabir <azabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 11:27:39 by yagnaou           #+#    #+#              #
#    Updated: 2022/08/26 23:04:17 by azabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -lreadline -L /Users/azabir/.brew/Cellar/readline/8.1.2/lib -I /Users/azabir/.brew/Cellar/readline/8.1.2/include #-fsanitize=address -g3

SRCS =	srcs/include/*.c\
		srcs/libft/*.c\
		srcs/execution/*.c

OBJS = $(SRCS:.c=.o)

define HEADER
        ___                     _                                               
        | |                    /_\                                              
        | |                   _   _                   _                         
        | |                  /_\ /_\                 /_\                 _____  
        | |      ___      ___  ___  ___      ___     ___     ___       _/     \ 
___     |  \____/   \____/  |__| |__|  \____/   \___/   \___/   \_____/ _  O  | 
\  \____/  \_____/ \_________________________/ \_____/ \_____/ \_______/ \____/ 
 \________/     _   _                       _   _            _   _              
               /_\ /_\                     /_\ /_\          /_\ /_\             

endef

export HEADER

all : $(NAME)

$(NAME) : $(SRCS)
	@echo "\033[0;32m$$HEADER\033[0m\n"
	@echo Compiling...
	@gcc $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "Done!"

clean :
	@rm -rf $(OBJS)
	@echo "Clean"

fclean :
	@rm -rf $(OBJS)
	@rm -rf $(NAME)
	@echo "Full Clean"

re : fclean all