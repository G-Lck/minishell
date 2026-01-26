NAME = minishell

SRCS =	$(wildcard srcs/utils/*.c) \
		$(wildcard srcs/parser/**/*.c) \
		$(wildcard srcs/parser/*.c) \
		$(wildcard srcs/execution/*.c) \
		$(wildcard srcs/execution/**/*.c) \
		$(wildcard srcs/execution/**/**/*.c)
MAIN_SRCS = srcs/main.c

OBJS = ${SRCS:.c=.o}
MAIN_OBJS = ${MAIN_SRCS:.c=.o}
CC = gcc
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
