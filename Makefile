NAME	= minishell

SRCS	=	main.c prompt.c							\
			signal_sig_handler.c					\
			free_free_command_line.c				\
			error_error_handler.c					\
													\
			commands_path.c							\
													\
			envcpy/envcpy.c							\
			envcpy/tmp_env.c						\
													\
			init_init_commands.c					\
			init_init_inc.c							\
													\
			utils/utils_correct_line.c				\
			utils/utils_count_arguments.c			\
			utils/utils_ft_split_v2.c				\
			utils/utils_is_in_quotes.c				\
			utils/utils_ft_increment.c				\
			utils/utils_find_special_char.c			\
			utils/utils_ft_splitv2old.c				\
													\
			exec/exec.c								\
			exec/exec_init.c						\
			exec/close_fd.c							\
			exec/child_process.c					\
			exec/free_all_exec.c					\
			exec/dup_fd.c							\
													\
			builtins/is_builtins.c					\
			builtins/ft_echo.c						\
			builtins/ft_pwd.c						\
			builtins/ft_cd.c						\
			builtins/ft_unset.c						\
			builtins/ft_export.c					\
			builtins/ft_env.c						\
			builtins/ft_exit.c						\
													\
			parsing/parsing.c						\
			parsing/parsing_quotes_flags.c			\
			parsing/parsing_special_char_flags.c	\
			parsing/parsing_find_end_redirection.c	\

HEADER_FILES = minishell.h

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -f

CFLAGS	=	-Wall -Wextra #-fsanitize=address #-Werror  #-g

all:		${NAME}

%.o : %.c 	${HEADER_FILES}
		${CC} -c ${CFLAGS} $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@$(MAKE) -C ./libft
			@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o minishell

c:
			${RM} ${OBJS}

fclean:		c
			${RM} minishell
			${MAKE} -C ./libft fclean

re:			fclean all

.PHONY:		all c fclean re minishell
