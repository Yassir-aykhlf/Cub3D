LIB_CUBE=./libcube3d.a
MAIN=./src/core/main.c

# Core application files
CORE_SRCS = ./src/core/game.c ./src/core/cleanup.c ./src/core/cleanup_helpers.c

# Game engine files  
ENGINE_SRCS = ./src/engine/player.c ./src/engine/player_movement.c ./src/engine/direction_utils.c

# Graphics subsystem
GRAPHICS_SRCS = ./src/graphics/render/renderer.c ./src/graphics/render/render_helpers.c ./src/graphics/render/draw_utils.c \
				./src/graphics/raycast/raycast.c ./src/graphics/raycast/ray_utils.c ./src/graphics/raycast/texture_utils.c \
				./src/graphics/texture_loader.c ./src/graphics/window/window.c

# Input/Output subsystem
IO_SRCS = ./src/io/parsing/read_file.c ./src/io/parsing/parse_game_config.c ./src/io/parsing/parse_rgb.c \
		  ./src/io/parsing/parse_textures.c ./src/io/parsing/parse_texture_helpers.c ./src/io/parsing/parse_utils.c \
		  ./src/io/parsing/parse_rgb_helpers.c ./src/io/parsing/parse_debug.c ./src/io/parsing/parse_map.c \
		  ./src/io/lexer/tokenizer.c ./src/io/lexer/lexer_read.c ./src/io/lexer/lexer.c ./src/io/lexer/token_utils.c \
		  ./src/io/events/events.c

# Utility functions and data structures
UTILS_SRCS = ./src/utils/containers/lines.c ./src/utils/containers/string.c ./src/utils/gnl/get_next_line.c \
			 ./src/utils/gnl/get_next_line_utils.c ./src/utils/error/error_loggers.c \
			 ./src/utils/map/map_validation.c ./src/utils/map/map_validation_helpers.c \
			 ./src/utils/map/map_utils.c ./src/utils/map/matrix_utils.c

SRCS = $(CORE_SRCS) $(ENGINE_SRCS) $(GRAPHICS_SRCS) $(IO_SRCS) $(UTILS_SRCS)
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

run: $(NAME)
	./$(NAME) ./assets/maps/test_basic.cub

test: $(NAME)
	@echo "Running basic tests..."
	./$(NAME) ./assets/maps/test_simple.cub
	./$(NAME) ./assets/maps/test_maze.cub

norm:
	norminette $(SRCS) $(MAIN) ./include/cube.h

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) ./assets/maps/test_basic.cub

print-srcs:
	@echo "Core sources: $(CORE_SRCS)"
	@echo "Engine sources: $(ENGINE_SRCS)"
	@echo "Graphics sources: $(GRAPHICS_SRCS)"
	@echo "IO sources: $(IO_SRCS)"
	@echo "Utils sources: $(UTILS_SRCS)"

.PHONY: all clean fclean re debug release run test norm valgrind print-srcs
