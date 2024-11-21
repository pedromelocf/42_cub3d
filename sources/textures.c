#include "../includes/cub3d.h"

static int32_t	get_color(double texture_y, int texture_x);

void	draw_texturized_line(int x, int draw_start, int draw_end, t_cub3d *s_cub3d, double perp_wall_dist)
{
	double	wall_hit_x = s_cub3d->player_pos.pos_y + perp_wall_dist * s_cub3d->player_dir.dir_y;
	wall_hit_x -= floor(wall_hit_x);
	double	step = (double)TEXTURE_HEIGHT / (int)(MAP_HEIGHT / perp_wall_dist); //set divisor to line_height variable
	int		texture_x = (int)(wall_hit_x * (double)TEXTURE_WIDTH); //fix width
	double	texture_pos = (draw_start - MAP_HEIGHT / 2 + (int)(MAP_HEIGHT / perp_wall_dist) / 2)* step;
	double	texture_y;
	int i = draw_start;

	while (i < draw_end)
	{
		texture_y = (int)texture_pos & (TEXTURE_HEIGHT - 1);
		texture_pos += step;
		mlx_put_pixel(s_cub3d->image, x, i, get_color(texture_y, texture_x));
		i++;
	}
}

static int32_t	get_color(double texture_y, int texture_x)
{
	int32_t	pixel;

	mlx_texture_t* texture = mlx_load_png("/home/pmelo/42/milestone4/42_cub3d/textures/moon.png");
	printf("width : %d\n", texture->width);
	pixel = *(texture->pixels) + (size_t)(texture_y * texture->width + texture_x);
	mlx_delete_texture(texture);
	return (pixel);
}
