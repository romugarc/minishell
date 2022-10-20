# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 16:13:51 by rgarcia           #+#    #+#              #
#    Updated: 2022/10/20 17:26:40 by rgarcia          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	=	main.c

HEADER_FILES = minishell.h

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=thread

all:		${NAME}

%.o : %.c 	${HEADER_FILES}
		${CC} -c ${CFLAGS} $< -o ${<:.c=.o}

$(NAME):	${OBJS}
				@${CC} ${CFLAGS} ${OBJS} -o philo

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} philo

re:			fclean all

.PHONY:		all clean fclean re minishell
