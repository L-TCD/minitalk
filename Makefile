SERVER_SRC = src/server.c
CLIENT_SRC = src/client.c
CC = gcc -Wall -Werror -Wextra

%.o: %.c
	${CC} -c $< -o $@

all: server client

server: ${SERVER_SRC:.c=.o}
	${CC} ${SERVER_SRC} -o server

client: ${CLIENT_SRC:.c=.o}
	${CC} ${CLIENT_SRC} -o client

clean:
	rm -rdf ${SERVER_SRC:.c=.o} ${CLIENT_SRC:.c=.o}

fclean: clean
	rm -rdf client server

re: fclean all

.PHONY: all clean fclean re
