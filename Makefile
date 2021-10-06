# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 14:12:38 by nlaurids          #+#    #+#              #
#    Updated: 2021/10/05 17:46:17 by nlaurids         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	philo.c \
				utils.c

INC			= 	philo.h

OBJS		= 	$(SRCS:.c=.o)

all :		$(NAME)

$(NAME)	: $(OBJS) $(INC)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY = all clean fclean re