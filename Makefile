NAME		= cub3d
NAME_BONUS	= cub3d_bonus

CC		= gcc -O2 -g
# CFLAGS	= -Wall -Wextra -Werror

# all files location
VPATH	:= ./mandatory:./utils:./utils/map:./engine:./bonus

SRCS_M	=	cub3d.c \
			map.c parse.c valid.c cleaner.c get_next_line_utils.c get_next_line.c \
			split.c string.c string_utils.c draw.c hook.c move.c pixel.c raycast.c
SRCS_B	=	cub3d_bonus.c \
			map.c parse.c valid.c cleaner.c get_next_line_utils.c get_next_line.c \
			split.c string.c string_utils.c draw.c hook.c move.c pixel.c raycast.c objects.c objects_init.c get.c minimap.c

OBJ_DIR		= ./obj
OBJ_DIR_M	= ./obj/mandatory
OBJ_DIR_B	= ./obj/bonus

OBJS_M	= $(patsubst %,$(OBJ_DIR_M)/%,$(SRCS_M:.c=.o))
OBJS_B	= $(patsubst %,$(OBJ_DIR_B)/%,$(SRCS_B:.c=.o))

INC_DIR_M	= ./mandatory/includes
INC_DIR_B	= ./bonus/includes

INCLUDES_M	= get_next_line.h cub3d.h index.h
INCLUDES_B	= get_next_line.h cub3d_bonus.h index.h

HEADERS_M	= $(addprefix $(INC_DIR_M), $(INCLUDES_M))
HEADERS_B	= $(addprefix $(INC_DIR_B), $(INCLUDES_B))

# leaks -atexit
# -fsanitize=leak

all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJ_DIR_M)/%.o : %.c
	@mkdir -p $(OBJ_DIR_M)
	$(CC) -Imlx -I$(INC_DIR_M) -Imlx_linux -O3 -o $@ -c $<
#	$(CC) -Imlx -I$(INC_DIR_M) -o $@ -c $<

$(OBJ_DIR_B)/%.o : %.c
	@mkdir -p $(OBJ_DIR_B)
	$(CC) -Imlx -I$(INC_DIR_B) -o $@ -c $<
#	$(CC) -Imlx -I$(INC_DIR_B) -Imlx_linux -O3 -o $@ -c $<

$(NAME): $(OBJS_M)
	$(CC) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -fsanitize=leak -o $@
# 	$(CC) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@

$(NAME_BONUS): $(OBJS_B)
	$(CC) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $@
# 	$(CC) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re