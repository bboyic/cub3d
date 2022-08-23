NAME		= cub3D
NAME_BONUS	= cub3D_bonus

CC		= gcc -O2 -g
CFLAGS	= 
# -Wall -Wextra -Werror

# all files location
VPATH	:= ./mandatory:./utils:./utils/map:./engine:./bonus

SRCS_M	=	cub3d.c ifs_for_move.c raycast_utils.c\
			map.c parse.c valid.c cleaner.c get_next_line_utils.c get_next_line.c \
			split.c string.c string_utils.c draw.c hook.c move.c pixel.c raycast.c init.c
SRCS_B	=	cub3d_bonus.c ifs_for_move.c raycast_utils.c\
			map.c parse.c valid.c cleaner.c get_next_line_utils.c get_next_line.c \
			split.c string.c string_utils.c draw.c hook.c move.c pixel.c raycast.c objects.c objects_init.c get.c minimap.c init_bonus.c

OBJ_DIR		= ./obj
OBJ_DIR_M	= ./obj/mandatory
OBJ_DIR_B	= ./obj/bonus

OBJS_M	= $(patsubst %,$(OBJ_DIR_M)/%,$(SRCS_M:.c=.o))
OBJS_B	= $(patsubst %,$(OBJ_DIR_B)/%,$(SRCS_B:.c=.o))

INC_DIR_M	= ./mandatory/includes
INC_DIR_B	= ./bonus/includes

INCLUDES_M	= cub3d.h index.h
INCLUDES_B	= cub3d_bonus.h index.h

HEADERS_M	= $(addprefix $(INC_DIR_M), $(INCLUDES_M))
HEADERS_B	= $(addprefix $(INC_DIR_B), $(INCLUDES_B))

all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJ_DIR_M)/%.o : %.c
	@mkdir -p $(OBJ_DIR_M)
	$(CC) $(CFLAGS) -Imlx -I$(INC_DIR_M) -o $@ -c $<
#	$(CC) $(CFLAGS) -Imlx -I$(INC_DIR_M) -Imlx_linux -O3 -o $@ -c $<

$(OBJ_DIR_B)/%.o : %.c
	@mkdir -p $(OBJ_DIR_B)
	$(CC) $(CFLAGS) -Imlx -I$(INC_DIR_B) -o $@ -c $<
#	$(CC) $(CFLAGS) -Imlx -I$(INC_DIR_B) -Imlx_linux -O3 -o $@ -c $<

$(NAME): $(OBJS_M)
	$(CC) $(CFLAGS) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@
#	$(CC) $(CFLAGS) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $@

$(NAME_BONUS): $(OBJS_B)
	$(CC) $(CFLAGS) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@
#	$(CC) $(CFLAGS) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re