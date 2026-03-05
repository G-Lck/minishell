NAME = minishell

SRCS =	$(wildcard srcs/*.c) \
		$(wildcard srcs/**/*.c) \
		$(wildcard srcs/**/**/*.c)

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

theo: ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) -Iheaders tests/main-theo.c ./libft/libft.a -lreadline -lncurses -o minishell-theo

garance: ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) -Iheaders tests/main-garance.c ./libft/libft.a -lreadline -lncurses -o minishell-garance

clean:
	${RM} ${OBJS}
	make clean -C ./libft

fclean: clean
	${RM} ${NAME}
	${RM} minishell-theo minishell-garance
	make fclean -C ./libft

re: fclean all
