CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = philosophers

SRC = main.c \
	  create.c \
	  routines.c \
	  philo_states.c \
	  helper.c \
	  assign_parse.c \
	  free.c
OBJ = $(SRC:.c=.o)

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

re: fclean all

clean:
	rm -rf $(OBJ)
	echo "OBJ files deleted"

fclean: clean
	rm -rf $(NAME)
	echo "Executable deleted"
