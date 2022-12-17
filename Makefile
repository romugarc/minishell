NAME	= minishell

SRCS	=	main.c									\
			utils/signal_sig_handler.c				\
			free/free_free_command_line.c			\
			free/free_ft_free_tab.c					\
			free/free_free_expand.c					\
			free/free_envc.c						\
			free/free_free_flag_string.c			\
													\
			commands/commands_path.c				\
			commandscommands_path_next.c			\
													\
			envcpy/envcpy.c							\
			envcpy/tmp_env.c						\
			envcpy/shlvl.c							\
			envcpy/get_env_str.c					\
													\
			init/init_init_commands.c				\
			init/init_init_inc.c					\
			init/init_init_tab_fd.c					\
			init/init_init_command_tab.c			\
													\
			utils/utils_correct_line.c				\
			utils/utils_count_arguments.c			\
			utils/utils_ft_split_v2.c				\
			utils/utils_is_in_quotes.c				\
			utils/utils_ft_increment.c				\
			utils/utils_find_special_char.c			\
			utils/utils_ft_splitv2old.c				\
			utils/utils_ft_del_str_from_i.c			\
			utils/utils_close_tab_fd.c				\
			utils/utils_ft_strrcmp.c				\
			utils/utils_ft_isenvarc.c				\
			utils/utils_ft_strdup_s_to_e.c			\
			utils/utils_is_sp_char.c				\
			utils/utils_ft_isspace.c				\
			utils/puterror.c						\
			utils/exec_utils.c						\
			utils/other_strlen.c					\
													\
			exec/exec.c								\
			exec/exec_init.c						\
			exec/close_fd.c							\
			exec/child_process.c					\
			exec/free_all_exec.c					\
			exec/dup_fd.c							\
			exec/check_access.c						\
			exec/is_command_path.c					\
													\
			builtins/is_builtins.c					\
			builtins/ft_echo.c						\
			builtins/ft_pwd.c						\
			builtins/ft_cd.c						\
			builtins/ft_unset.c						\
			builtins/ft_export.c					\
			builtins/get_next_val.c					\
			builtins/get_new_val.c					\
			builtins/valid_id_exp.c					\
			builtins/export_var_val.c				\
			builtins/print_export.c					\
			builtins/add_export.c					\
			builtins/ft_env.c						\
			builtins/ft_exit.c						\
			builtins/ft_refresh_pwd.c				\
			builtins/rm_var.c						\
													\
			parsing/parsing.c						\
			parsing/parsing_quotes_flags.c			\
			parsing/parsing_special_char_flags.c	\
			parsing/parsing_find_end_redirection.c	\
			parsing/parsing_count_redirections.c	\
			parsing/parsing_malloc_tab_files.c		\
			parsing/parsing_form_tab.c				\
			parsing/parsing_manage_infile.c			\
			parsing/parsing_manage_outfile.c		\
			parsing/parsing_reform_tab.c			\
			parsing/parsing_correct_tab.c			\
			parsing/parsing_create_fd.c				\
			parsing/parsing_create_fd_in.c			\
			parsing/parsing_expand_variable.c		\
			parsing/parsing_copy_var.c				\
			parsing/parsing_expand_heredoc.c		\
			parsing/parsing_check_fd.c				\
			parsing/parsing_remove_quotes.c			\
			parsing/parsing_parse_error.c			\
			parsing/parsing_cat_ex_var.c			\
			parsing/parsing_create_fdnorm.c			\
			parsing/parsing_hd_routine.c			\
			parsing/parsing_search_expand.c			\
			parsing/parsing_removing_quotes.c		\

RL_LIB = -L$(shell brew --prefix readline)/lib
RL_INC = -I$(shell brew --prefix readline)/include

HEADER_FILES = minishell.h

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

all:		${NAME}

%.o : %.c 	${HEADER_FILES}
		${CC} ${CFLAGS} ${RL_INC} -c $< -o ${<:.c=.o} 

$(NAME):	${OBJS}
			@$(MAKE) -C ./libft
			@${CC} ${CFLAGS} ${OBJS} ${RL_LIB} ${RL_INC} -lreadline ./libft/libft.a -o minishell 

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} minishell
			${MAKE} -C ./libft fclean

re:			fclean all

.PHONY:		all clean fclean re minishell
