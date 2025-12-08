NAME = minishell

SRCS = 	$(wildcard srcs/*.c) \
		$(wildcard srcs/utils/*.c) \
		$(wildcard srcs/parser/tokenizer/*.c)


OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Iheaders

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
	${RM} ${OBJS}
	make clean -C ./libft

fclean: clean
	${RM} ${NAME}
	make fclean -C ./libft

re: fclean all
