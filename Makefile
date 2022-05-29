NAME		= cub3d
C_DIR		= mandatory/main/
OBJ_DIR		= obj/
C_F 		= cub3d.c
INCLUDES	=
C_FILES 	= $(addprefix $(C_DIR), $(C_F))
T_OBJ 		= $(C_FILES:.c=.o)
OBJ			= $(T_OBJ:$(C_DIR)=$(OBJ_DIR))

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $($@:mandatory/main=obj)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re