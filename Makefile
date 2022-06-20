NAME		= cub3d
C_DIR		= ./
OBJ_DIR		= ./
C_F 		= main.c
INCLUDES	= ./
INCLUDES_F	= $(INCLUDES)/index.h $(INCLUDES)/cub3d.h
C_FILES 	= $(addprefix $(C_DIR), $(C_F))
T_OBJ 		= $(C_FILES:.c=.o)
OBJ			= $(T_OBJ:$(C_DIR)=$(OBJ_DIR))

all: $(NAME)

%.o: %.c 
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $(OBJ) -I $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re