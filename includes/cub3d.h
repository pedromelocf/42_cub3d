/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 12:26:33 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/includes/libft.h"
# include "../libraries/mlx/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <sys/stat.h>

# define MSG_ERROR "\033[1;41mError!\033[0m\n\033[0;31m"
# define MSG_LEN_ERROR 25

# define MSG_INV_ARG_COUNT "Arguments: Invalid number of arguments.\n"
# define MSG_INV_FILE_DIR "File: Specified file is actually a directory.\n"
# define MSG_INV_FILE_OPEN "File: Could not open specified file.\n"
# define MSG_INV_FILE_EXT_CUB "File: Invalid file extension. Must be '.cub'.\n"
# define MSG_INV_FILE_ELEMENTS "File: Invalid elements or players in file.\n"
# define MSG_INV_FILE_MAP "Map: Map is not playable.\n"
# define MSG_INV_MLX_INIT "MLX: Could not initialize MLX.\n"
# define MSG_INV_TEXTURES "Invalid texture configurations.\n"
# define MSG_INV_COLORS "Invalid RGB colors configurations.\n"
# define MSG_INV_ARG "Invalid arguments.\n"

# define MSG_ERROR_EXIT "\033[0m"
# define MSG_LEN_ERROR_EXIT 5

# define BLANK_CHARS " \t\v"
# define PLAYER_CHARS "NSWE"

# define PLAYER_ERROR -2

# define FALSE 0
# define TRUE 1

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define ESC MLX_KEY_ESCAPE
# define W MLX_KEY_W
# define A MLX_KEY_A
# define S MLX_KEY_S
# define D MLX_KEY_D
# define RIGHT MLX_KEY_RIGHT
# define LEFT MLX_KEY_LEFT
# define MOVE_SPEED_MULTI 4.0
# define ROTATE_SPEED_MULTI 1.5
# define COLISION_DISTANCE_MULTI 10.0

enum					e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_loaded_textures
{
	mlx_texture_t		*no;
	mlx_texture_t		*so;
	mlx_texture_t		*we;
	mlx_texture_t		*ea;
}						t_loaded_textures;

typedef struct s_texture
{
	t_loaded_textures	loaded_textures;
	mlx_texture_t		*wall_texture;
	double				wall_hit_x;
	double				step;
	double				texture_pos;
	int					texture_y;
	int					texture_x;
}						t_texture;

typedef struct s_rgb_colors
{
	char				*floor_color;
	char				*ceiling_color;
}						t_rgb_colors;

typedef struct s_coordinates
{
	double				x;
	double				y;
}						t_coordinates;

typedef struct s_rays
{
	double				ray_dir_x;
	double				ray_dir_y;
	double				perp_wall_dist;
	int					side_hit;
}						t_rays;

typedef struct s_wall
{
	int					line_height;
	int					draw_start;
	int					draw_end;
}						t_wall;

typedef struct s_dda
{
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	int					step_x;
	int					step_y;
	int					map_x;
	int					map_y;
}						t_dda;

typedef struct s_cub3d
{
	t_rgb_colors		rgb_colors;
	char				**map;
	t_coordinates		player_pos;
	t_coordinates		player_dir;
	t_coordinates		camera_plane;
	mlx_t				*mlx;
	mlx_image_t			*image;
	t_texture			textures;
	t_rays				rays;
	t_dda				dda;
	t_wall				wall;
	char				*file;
}						t_cub3d;

void					print_map(char **map);
void					handle_error(const char *message);
void					check_file(char *file);
void					load_scene(char *file, t_cub3d *scene);
mlx_texture_t			*get_texture(char *line);
char					*get_rgb(char *line);
void					get_map(char *line, t_cub3d *scene, int fd);
void					get_player_elements(t_cub3d *scene);
void					check_elements(t_cub3d *scene);
void					flood_fill(char **map, int rows, t_coordinates c);
bool					is_valid_png(char *file);
bool					is_valid_color_tag(char *line);
bool					is_valid_map(t_list *lines);
bool					is_empty_line(char *line);
void					run_scene(t_cub3d *scene);
void					clean_scene(t_cub3d *scene, char *message);
int						handle_mlx(mlx_t **mlx, mlx_image_t **image);
void					handle_key_hooks(t_cub3d *s_cub3d);
int						algorithm(t_cub3d *s_cub3d);
void					ray_calculations(t_cub3d *s_cub3d, double camera_x);
void					dda(t_cub3d *s_cub3d);
void					load_texture_info(t_cub3d *s_cub3d);
void					wall_calculations(t_cub3d *s_cub3d);
void					draw_line(int x, t_cub3d *s_cub3d);
void					draw_box(mlx_image_t *image, int height, int width,
							int beginx, int beginy, uint32_t color);
void					draw_background(t_cub3d *s_cub3d);
void					draw_texturized_line(int x, t_cub3d *s_cub3d);
void					player_rotate(t_cub3d *s_cub3d, float multiply_factor);
void					player_move_forward(t_cub3d *s_cub3d, float move_speed,
							double colision_distance);
void					player_move_backward(t_cub3d *s_cub3d, float move_speed,
							double colision_distance);
void					player_move_left(t_cub3d *s_cub3d, float move_speed,
							double colision_distance);
void					player_move_right(t_cub3d *s_cub3d, float move_speed,
							double colision_distance);

#endif
