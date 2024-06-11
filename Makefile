NAME = client
SRV = server

SRC_CLIENT = client.c utils.c
SRC_SERVER = server.c utils.c
OBJ_CLIENT = ${SRC_CLIENT:.c=.o}
OBJ_SERVER = ${SRC_SERVER:.c=.o}

CC = cc
FLAGS = -Wall -Wextra -Werror

%.o : %.c minitalk.h
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME) $(SRV)

$(NAME) : $(OBJ_CLIENT)
	$(CC) $(FLAGS) $(OBJ_CLIENT) -o $(NAME)

$(SRV) : $(OBJ_SERVER)
	$(CC) $(FLAGS) $(OBJ_SERVER) -o $(SRV)

clean : 
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean : clean
	rm -f $(NAME) $(SRV)

re : fclean all
