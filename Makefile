NAME = minishell

SRCS =	$(wildcard srcs/*.c) \
		$(wildcard srcs/**/*.c) \
		$(wildcard srcs/**/**/*.c)
MAIN_SRCS = srcs/main.c

OBJS = ${SRCS:.c=.o}
MAIN_OBJS = ${MAIN_SRCS:.c=.o}
CC = gcc -Wall -Wextra
RM = rm -f
CFLAGS = -Iheaders -g

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS} ${MAIN_OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) ${MAIN_OBJS} ./libft/libft.a -o $(NAME)

theo: ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) -Iheaders tests/main-theo.c ./libft/libft.a -lreadline -lncurses -o minishell-theo

garance: ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) -Iheaders tests/main-garance.c ./libft/libft.a -lreadline -lncurses -o minishell-garance

clean:
	${RM} ${OBJS} ${MAIN_OBJS}
	make clean -C ./libft

fclean: clean
	${RM} ${NAME}
	${RM} minishell-theo minishell-garance
	make fclean -C ./libft

re: fclean all
