NAME = minishell

SRCS =	./srcs/main.c \
		./srcs/0_initalisation/init_minishell.c \
		./srcs/0_initalisation/read_and_process.c \
		./srcs/1_tokenizer/heredoc_utils.c \
		./srcs/1_tokenizer/heredoc.c \
		./srcs/1_tokenizer/syntax_checker_2.c \
		./srcs/1_tokenizer/syntax_checker.c \
		./srcs/1_tokenizer/token_manager.c \
		./srcs/1_tokenizer/tokenizer_utils.c \
		./srcs/1_tokenizer/tokenizer.c \
		./srcs/2_create_ast/ast.c \
		./srcs/2_create_ast/utils_ast_2.c \
		./srcs/2_create_ast/utils_ast.c \
		./srcs/3_expansion_and_wildcards/command_preparation.c \
		./srcs/3_expansion_and_wildcards/create_redirs.c \
		./srcs/3_expansion_and_wildcards/expand_variables.c \
		./srcs/3_expansion_and_wildcards/expansions_utils.c \
		./srcs/3_expansion_and_wildcards/variable_parser.c \
		./srcs/3_expansion_and_wildcards/wildcards_parser.c \
		./srcs/4_execute_ast/exec_ast.c \
		./srcs/5_execute_pipeline/exec_pipeline.c \
		./srcs/5_execute_pipeline/pipeline_cleanup.c \
		./srcs/5_execute_pipeline/pipeline_init.c \
		./srcs/5_execute_pipeline/pipeline_pipe_redir.c \
		./srcs/5_execute_pipeline/pipeline_redir.c \
		./srcs/6_execute_cmd/built_ins/env_helpers_2.c \
		./srcs/6_execute_cmd/built_ins/env_helpers.c \
		./srcs/6_execute_cmd/built_ins/export_helpers.c \
		./srcs/6_execute_cmd/built_ins/ft_cd.c \
		./srcs/6_execute_cmd/built_ins/ft_echo.c \
		./srcs/6_execute_cmd/built_ins/ft_env.c \
		./srcs/6_execute_cmd/built_ins/ft_exit.c \
		./srcs/6_execute_cmd/built_ins/ft_export.c \
		./srcs/6_execute_cmd/built_ins/ft_pwd.c \
		./srcs/6_execute_cmd/built_ins/ft_unset.c \
		./srcs/6_execute_cmd/built_ins/is_builtin.c \
		./srcs/6_execute_cmd/exec_node.c \
		./srcs/7_clean/cleanup_minishell.c \
		./srcs/utils/command_finder.c \
		./srcs/utils/signals.c \
		./srcs/utils/token_utils.c





OBJS = ${SRCS:.c=.o}
CC = gcc -Wall -Wextra -Werror
RM = rm -f
CFLAGS = -Iheaders -g

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) ./libft/libft.a -lreadline -lncurses -o $(NAME)

clean:
	${RM} ${OBJS}
	make clean -C ./libft

fclean: clean
	${RM} ${NAME}
	${RM} minishell-theo minishell-garance
	make fclean -C ./libft

re: fclean all
