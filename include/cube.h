/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:39:23 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/20 17:39:24 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <mlx.h>
# include "get_next_line.h"
# include <errno.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <math.h>

# define ERR_HEADER "Error\n"
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define TARGET_FPS 60
# define MSEC_PER_FRAME 16666
# define MSEC 1000000

# define CAMERA_PLANE_DISTANCE 0.66

# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define Q_KEY 113
# define Z_KEY 122
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

// Direction constants for last key tracking
# define DIR_NONE 0
# define DIR_LEFT 1
# define DIR_RIGHT 2
# define DIR_FORWARD 3
# define DIR_BACKWARD 4

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define COMA ','
# define CUBE_SUCCESS 0
# define CUBE_FAILURE -1
# define NOT_FOUND -2
# define FOUND_MULTIPLE -3
# define TEXTURE_COUNT 4

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_string
{
	char	*items;
	size_t	size;
	size_t	cap;
}	t_string;

typedef enum e_texture_type
{
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_WEST,
	TEXTURE_EAST
}	t_texture_type;

typedef enum e_color_type
{
	COLOR_FLOOR,
	COLOR_CEILING
}	t_color_type;

typedef enum e_token_type
{
	MAP_LINE = 0x0,
	EOL,
	EOF_,
	SEPARATOR,
	WORD,
	NUMBER,
	OVERFLOW_NUMBER,
	COUNT
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	union
	{
		t_string	string_data;
		int			number_data;
	} u_data;
}	t_token;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*window;
	int		width;
	int		height;
}	t_window;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_texture
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_direction_config
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_dir_config;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_lines
{
	char	**items;
	size_t	cap;
	size_t	size;
}	t_lines;

typedef struct s_map
{
	const char	*config_file_path;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			ceiling_color;
	int			floor_color;
	t_lines		grid;
	int			player_x;
	int			player_y;
	char		player_direction;
}	t_map;

typedef struct s_input
{
	int	move_fwd;
	int	move_back;
	int	move_left;
	int	move_right;
	int	rot_left;
	int	rot_right;
	int	last_horizontal_move;
	int	last_rotation;
	int	last_vertical_move;
}	t_input;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_game
{
	t_window		window;
	t_image			screen_buffer;
	t_texture		textures[TEXTURE_COUNT];
	t_player		player;
	t_input			input;
	int				running;
	struct timeval	last_frame_time;
	t_map			map;
}	t_game;

typedef struct s_lexer_state
{
	t_lines	*lines;
	t_token	*current;
	size_t	cursor;
	size_t	line_index;
}	t_lexer_state;

/* Window management functions */
int				init_window(t_window *window, int width,
					int height);
int				spawn_window(t_window *window, char *title);
void			cleanup_window(t_window *window);

/* Game management functions */
int				init_game(t_game *game);
int				init_screen_buffer(t_game *game);
int				init_player(t_game *game);
int				init_textures(t_game *game);
void			set_direction_vectors(t_game *game, char direction);
void			cleanup_game(t_game *game);
void			cleanup_map(t_map *map);
void			cleanup_images(t_game *game);
void			cleanup_textures(t_game *game);
int				run_game(t_game *game);
void			destroy_connection(void *mlx_ptr);

/* Event handling functions */
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);
int				handle_close(t_game *game);
void			setup_event_hooks(t_game *game);
void			handle_movement_keypress(int keycode, t_game *game);
void			handle_rotation_keypress(int keycode, t_game *game);
void			handle_movement_keyrelease(int keycode, t_game *game);
void			handle_rotation_keyrelease(int keycode, t_game *game);

/* Player movement functions */
void			update_player_state(t_game *game);
void			handle_rotation(t_game *game);
void			handle_strafe_movement(t_game *game);
void			apply_rotation(t_player *player, double rot_speed);
void			apply_movement(t_game *game, double move_x, double move_y);

/* Rendering functions */
int				render_next_frame(t_game *game);
void			put_pixel_to_image(t_image *img, int x, int y, int color);
void			clear_screen(t_game *game);
void			draw_ceiling_and_floor(t_game *game, int x, int draw_start,
					int draw_end);
void			draw_wall_line(t_game *game, int x, int draw_start,
					int draw_end);

/* Ray casting functions */
void			cast_single_ray(t_game *game);
void			cast_all_rays(t_game *game);
void			init_ray(t_ray *ray, t_player *player, int x);
void			calculate_dda_step_and_side_dist(t_ray *ray, t_player *player);
void			perform_dda(t_ray *ray, t_game *game);
void			calculate_wall_distance(t_ray *ray, t_player *player);
void			draw_vertical_line(t_game *game, t_ray *ray, int x);
int				get_texture_pixel(t_texture *texture, int x, int y);
int				get_wall_texture_index(t_ray *ray);
void			calculate_texture_coordinates(t_ray *ray, t_player *player);

/* Utility functions */
long			get_time_diff_us(struct timeval *start, struct timeval *end);

/* Map reading functions */
int				read_file_into_lines(t_lines *const lines,
					const char *file_path);
/* lexer */
char			lexer_current_char(t_lexer_state *lexer);
char			lexer_char_at(t_lexer_state *lexer, size_t index);
void			skip_whitespace(t_lexer_state *lexer);
void			lexer_clean_token(t_lexer_state *lexer);
int				lexer_eol_reached(t_lexer_state *lexer);
int				lexer_eof_reached(t_lexer_state *lexer);
void			lexer_read_word(t_lexer_state *lexer);
void			lexer_read_map_line(t_lexer_state *lexer);
void			lexer_read_number(t_lexer_state *lexer);
t_token_type	lexer_look_ahead(t_lexer_state *lexer);
int				lexer_expect_token(t_lexer_state *lexer,
					t_token_type expected_type, t_token *token);
int				ft_isdigit(int c);
int				ft_isspace(char c);
void			*ft_memset(void *b, int c, size_t len);
/* Tokenizer function */
void			get_next_token(t_lexer_state *lexer, t_token *storage);
char			*get_token_type(t_token *token);
/* String */
size_t			push_while(t_string *string, char *what,
					size_t start, int (*predicate)(int));
int				string_push(t_string *string, char item);
int				is_valid_map_character(int c);
int				lexer_exhausted(t_lexer_state *lexer);
/* Parser */
void			print_parsed_config(t_game *game);
void			init_token(t_token *token);
void			tmp_print_token(t_token *token);
void			cleanup_token(t_token *token);
int				handle_identifier(t_game *game, t_lexer_state *lexer,
					t_token *store);
int				parse_game_config(t_game *game, t_lexer_state *lexer);
int				parse_rgb_color(t_lexer_state *lexer);
int				parse_color(t_game *game, t_lexer_state *lexer,
					int *color_field);
int				parse_floor_color(t_game *game, t_lexer_state *lexer);
int				parse_ceiling_color(t_game *game, t_lexer_state *lexer);
int				get_rgb_component(t_lexer_state *lexer);
int				skip_separator(t_lexer_state *lexer);
int				get_and_validate_token(t_lexer_state *lexer,
					t_token_type expected_type, t_token *token);
char			*get_texture_path(t_lexer_state *lexer);
int				parse_texture(t_game *game, t_lexer_state *lexer,
					char **texture_field);
int				parse_texture_by_type(t_game *game, t_lexer_state *lexer,
					t_texture_type type);
int				parse_north_texture(t_game *game, t_lexer_state *lexer);
int				parse_south_texture(t_game *game, t_lexer_state *lexer);
int				parse_west_texture(t_game *game, t_lexer_state *lexer);
int				parse_east_texture(t_game *game, t_lexer_state *lexer);
int				parse_map(t_game *game, t_lexer_state *lexer, t_token *store);
int				validate_game_resources(t_map *map);
int				validate_map(t_map *map);

/* Map wall validation functions */
int				validate_map_walls(t_map *map);
int				flood_fill_validate(t_map *map, int **visited, int x, int y);
int				process_flood_fill_directions(t_map *map, int **visited,
					t_coord pos);
int				is_within_bounds(t_map *map, int x, int y);
int				is_walkable(char c);
int				is_at_boundary(t_map *map, int x, int y);
char			get_char_at(t_map *map, int x, int y);
int				**allocate_visited_matrix(t_map *map);
void			free_visited_matrix(int **visited, size_t height);
int				is_visited(int **visited, int x, int y);
void			mark_visited(int **visited, int x, int y);
t_dir_config	get_north_config(void);
t_dir_config	get_south_config(void);
t_dir_config	get_east_config(void);
t_dir_config	get_west_config(void);
int				flood_fill_validate(t_map *map, int **visited, int x, int y);
int				log_map_not_enclosed(void);

/* Loggers */
void			log_system_error(const char *resource);
int				log_missing(const char *missing_label);
int				throw_error_on_failure(const char *element,
					t_game *game,
					t_lexer_state *lexer,
					int (*proc)(t_game *, t_lexer_state *));
int				log_duplication_error(const char *duplication_label);
void			print_error_header(void);
/* Lines Methods */
void			destroy_lines(t_lines *const lines);
void			push_line(t_lines *const lines, char *line);
#endif
