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

# define WIDTH 1920
# define HEIGHT 1080

# define BLACK_COLOR 0x00000ff
# define RED_COLOR  0xff0000ff
# define WHITE_COLOR  0xffffffff
# define GREY_COLOR	0x00FF0000
# define YELLOW_COLLOR 0xFFFF00FF

# define FOV 66

typedef struct s_rgb_colors
{
	char	floor_color[50];
	char	ceiling_color[50];
}	t_rgb_colors;

typedef struct s_texture_paths
{
	char	no_texture_path[50];
	char	so_texture_path[50];
	char	we_texture_path[50];
	char	ea_texture_path[50];
}	t_texture_paths;

typedef struct s_player_pos
{
	double	pos_x;
	double	pos_y;
}	t_player_pos;

typedef struct s_player_dir
{
	double	dir_x;
	double	dir_y;
}	t_player_dir;

typedef struct s_camera_plane
{
	double	plane_x;
	double	plane_y;
}	t_camera_plane;

typedef struct s_cub3d
{
	t_texture_paths	texture_paths;
	t_rgb_colors	rgb_colors;
	char			map[14][25];
	t_player_pos	player_pos;
	t_player_dir 	player_dir;
	t_camera_plane 	camera_plane;
	mlx_t 			*mlx;
	mlx_image_t 	*image;
}	t_cub3d;


int	handle_mlx(mlx_t **mlx, mlx_image_t **image);
void	handle_key_hooks(t_cub3d *s_cub3d);
int	cast_rays(t_cub3d *s_cub3d);
double	dda(t_cub3d *s_cub3d, double raydir_x, double raydir_y);
void	draw_rays(int x, double perp_wall_dist, t_cub3d *s_cub3d);
void	draw_line_red(int x, int draw_start,int draw_end, t_cub3d *s_cub3d);
void	draw_line_white(int x, int draw_start,int draw_end, t_cub3d *s_cub3d);
void	draw_line_black(int x, int draw_start,int draw_end, t_cub3d *s_cub3d);
void	draw_box(mlx_image_t *image, int height, int width, int beginx, int beginy, uint32_t color);
void	draw_background (t_cub3d *s_cub3d);

#endif
