# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkord <gkord@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 14:47:26 by iwhana21          #+#    #+#              #
#    Updated: 2022/06/14 17:35:31 by gkord            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c philosophers.c philo_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CLANG	= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -lpthread

HEADER	= philosophers.h


all:	$(NAME)

.PHONY:	clean fclean re

$(NAME): $(OBJS)
	$(CLANG) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)
