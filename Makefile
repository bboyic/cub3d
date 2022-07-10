NAME	= cub3d

CC		= gcc
# CFLAGS	= -Wall -Wextra -Werror

# mandatory files
VPATH	:= ./mandatory:./utils:./utils/map:./engine

SRCS_M =	cub3d.c \
			map.c parse.c valid.c cleaner.c get_next_line_utils.c get_next_line.c \
			split.c string.c draw.c hook.c move.c pixel.c raycast.c

OBJ_DIR_M		= ./obj/mandatory

OBJS_M = $(patsubst %,$(OBJ_DIR_M)/%,$(SRCS_M:.c=.o))

INC_DIR	= ./mandatory/includes

INCLUDES	= get_next_line.h cub3d.h index.h
HEADERS		= $(addprefix $(INC_DIR), $(INCLUDES))

all: $(NAME)

$(OBJ_DIR_M)/%.o : %.c
	@mkdir -p $(OBJ_DIR_M)
	$(CC) -Imlx -I$(INC_DIR) -Imlx_linux -O3 -o $@ -c $< 
# $(CC) -Imlx -I$(INC_DIR) -o $@ -c $<

$(NAME): $(OBJS_M)
	$(CC) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $@
# $(CC) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@

clean:
	rm -rf $(OBJS_M)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re