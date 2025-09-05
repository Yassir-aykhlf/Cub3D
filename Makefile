LIB_CUBE=./libcube3d.a
MAIN=./src/main.c
SRCS=./src/cube.c ./src/player.c ./src/player_movement.c ./src/lexer/tokenizer.c ./src/lexer/lexer_read.c ./src/lexer/lexer.c ./src/gnl/get_next_line.c ./src/gnl/get_next_line_utils.c ./src/read_file.c ./src/window.c ./src/events.c ./src/renderer.c ./src/renderer_utils.c ./src/raycast.c ./src/ray_utils.c ./src/render_helpers.c ./src/texture_utils.c ./src/texture_loader.c ./src/draw_utils.c ./src/containers/lines.c ./src/containers/string.c ./src/parsing/parse_game_config.c ./src/parsing/parse_rgb.c ./src/parsing/parse_textures.c ./src/parsing/parse_texture_helpers.c ./src/parsing/parse_utils.c ./src/parsing/parse_rgb_helpers.c ./src/parsing/parse_debug.c ./src/cleanup.c ./src/cleanup_helpers.c ./src/parsing/parse_map.c ./src/error_loggers.c ./src/parsing/map_validation.c ./src/parsing/map_validation_helpers.c ./src/lexer/token_utils.c ./src/parsing/map_utils.c ./src/matrix_utils.c ./src/direction_utils.c
OBJS=$(SRCS:%.c=%.o)
NAME=cub3D
CC=cc
LIBS=-L. -lcube3d -L./minilibx-linux -lmlx_Linux -lX11 -lXext -lm
INCLUDE=-I./include -I./minilibx-linux
CFLAGS=-Wall -Wextra -Werror $(INCLUDE) -ggdb -Wno-incompatible-pointer-types
AR=ar rsc
RM=rm -f

all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(LIB_CUBE): $(OBJS)
	$(AR) $@ $?
$(NAME): $(LIB_CUBE) $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $@ $(LIBS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(LIB_CUBE)
	$(RM) $(NAME)
re: fclean all

run: re
	norminette $(SRCS) $(MAIN) ./include/cube.h
	valgrind --leak-check=full ./$(NAME) ./maps/test_basic.cub

.PHONY: re fclean clean bonus
