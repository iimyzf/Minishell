# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 11:27:39 by yagnaou           #+#    #+#              #
#    Updated: 2022/06/12 10:50:40 by yagnaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -lreadline #-fsanitize=address -g3

SRCS =	srcs/include/*.c\
		srcs/libft/*.c\
		srcs/execution/*.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRCS)
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