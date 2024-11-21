#include "../includes/cub3d.h"

static uint32_t	get_color(double texture_y, int texture_x, t_cub3d *s_cub3d);

void	draw_texturized_line(int x, int draw_start, int draw_end, t_cub3d *s_cub3d, double perp_wall_dist)
{
	double	wall_hit_x = s_cub3d->player_pos.pos_y + perp_wall_dist * s_cub3d->player_dir.dir_y;
	wall_hit_x -= floor(wall_hit_x);
	double	step = 1.0 * MAP_HEIGHT / (int)(MAP_HEIGHT / perp_wall_dist); //set divisor to line_height variable
	int		texture_x = (int)(wall_hit_x * (double)s_cub3d->texture->width);
	double	texture_pos = (draw_start - MAP_HEIGHT / 2 + ((int)(MAP_HEIGHT / perp_wall_dist) / 2)) * step;
	double	texture_y;

	int i = draw_start;

	while (i < draw_end)
	{
		texture_y = (int)texture_pos & (s_cub3d->texture->height - 1);
		texture_pos += step;
		mlx_put_pixel(s_cub3d->image, x, i, get_color(texture_y, texture_x, s_cub3d));
		i++;
	}
}

static uint32_t	get_color(double texture_y, int texture_x, t_cub3d *s_cub3d)
{
	uint8_t	*pixel;

	pixel = &s_cub3d->texture->pixels[((int)texture_y * s_cub3d->texture->width + texture_x) * s_cub3d->texture->bytes_per_pixel];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}
