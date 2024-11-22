/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr  >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/25 11:35:27 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/includes/libft.h"
# include "../libraries/mlx/include/MLX42/MLX42.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define MSG_ERROR "\033[1;41mError!\033[0m\n\033[0;31m"
# define MSG_LEN_ERROR 25

# define MSG_ARG_COUNT "Arguments: Invalid number of arguments.\n"
# define MSG_INV_EXEC "Invalid .cub map file\n"
# define MSG_INV_TEXTURES "Invalid texture configurations\n"
# define MSG_INV_COLORS "Invalid RGB colors configurations\n"
# define MSG_INV_ARG "Invalid arguments\n"

# define MSG_ERROR_EXIT "\033[0m\n"
# define MSG_LEN_ERROR_EXIT 5

# define FALSE 0
# define TRUE 1

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define BLACK_COLOR 0x00000FF
# define RED_COLOR  0xFF0000FF
# define WHITE_COLOR  0xFFFFFFFF
# define GREEN_COLOR 0x00FF00FF
# define YELLOW_COLLOR 0xFFFF00FF

# define FOV 66

enum				e_side
{
	WEST_EAST,
	NORTH_SOUTH
};

typedef struct s_loaded_textures
{
	mlx_texture_t *no_loaded_texture;
	mlx_texture_t *so_loaded_texture;
	mlx_texture_t *we_loaded_texture;
	mlx_texture_t *ea_loaded_texture;
}	t_loaded_textures;

typedef struct s_texture
{
	t_loaded_textures loaded_textures;
	mlx_texture_t	*wall_texture;
	double	wall_hit_x;
	double	step;
	double	texture_pos;
	int		texture_y;
	int 	texture_x;
}	t_texture;

typedef struct s_rgb_colors
{
	char	floor_color[50];
	char	ceiling_color[50];
}	t_rgb_colors;

typedef struct s_coordinates
{
	double	x;
	double	y;
}	t_coordinates;

typedef struct s_rays
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	perp_wall_dist;
	int		side_hit;
}	t_rays;

typedef struct s_wall
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_wall;

typedef struct s_dda
{
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int step_x;
	int step_y;
	int map_x;
	int map_y;
}	t_dda;

typedef struct s_cub3d
{
	t_rgb_colors	rgb_colors;
	char			map[14][23];
	t_coordinates	player_pos;
	t_coordinates 	player_dir;
	t_coordinates 	camera_plane;
	mlx_t 			*mlx;
	mlx_image_t 	*image;
	t_texture 		textures;
	t_rays			rays;
	t_dda			dda;
	t_wall			wall;
}	t_cub3d;

int	handle_mlx(mlx_t **mlx, mlx_image_t **image);
void	handle_key_hooks(t_cub3d *s_cub3d);
int	algorithm(t_cub3d *s_cub3d);
void	ray_calculations(t_cub3d *s_cub3d, double camera_x);
void	dda(t_cub3d *s_cub3d);
void	load_texture_info(t_cub3d *s_cub3d);
void wall_calculations (t_cub3d *s_cub3d);
void	draw_line(int x, t_cub3d *s_cub3d);
void	draw_box(mlx_image_t *image, int height, int width, int beginx, int beginy, uint32_t color);
void	draw_background (t_cub3d *s_cub3d);
void	draw_texturized_line(int x, t_cub3d *s_cub3d);

#endif
