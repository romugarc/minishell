NAME	= minishell

SRCS	=	main.c parsing.c prompt.c																					\
			init_init_commands.c																						\
			utils_correct_line.c utils_count_arguments.c utils_ft_split_v2.c utils_is_in_quotes.c utils_ft_increment.c	\
			parsing_quotes_flags.c parsing_special_char_flags.c															\
			signal_sig_handler.c																						\
			free_free_command_line.c																					\
			error_error_handler.c																						\
			exec.c																										\

HEADER_FILES = minishell.h

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

all:		${NAME}

%.o : %.c 	${HEADER_FILES}
		${CC} -c ${CFLAGS} $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@$(MAKE) -C ./libft
			@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o minishell

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} minishell
			${MAKE} -C ./libft fclean

re:			fclean all

.PHONY:		all clean fclean re minishell
