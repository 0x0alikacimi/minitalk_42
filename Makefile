CLIENT = client
SERVER = server
SERVER_SRC = server.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_SRC = client.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SRCS = utils.c
OBJS = $(SRCS:.c=.o)
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
CC = CC

all: $(CLIENT) $(SERVER)

$(SERVER): $(OBJS) $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(OBJS) -o $(SERVER) 
$(CLIENT): $(OBJS) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(OBJS) -o $(CLIENT)

%.o : %.c minitalk.h $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean : clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: re clean fclean all
