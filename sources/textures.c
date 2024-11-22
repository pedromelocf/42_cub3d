#include "../includes/cub3d.h"

static uint32_t	get_color(t_cub3d *s_cub3d);

void	draw_texturized_line(int x, int draw_start, int draw_end, t_cub3d *s_cub3d)
{
	if (s_cub3d->rays.side_hit == WEST_EAST)
		s_cub3d->textures.wall_hit_x = s_cub3d->player_pos.y + s_cub3d->rays.perp_wall_dist * s_cub3d->rays.ray_dir_y;
	else
		s_cub3d->textures.wall_hit_x = s_cub3d->player_pos.x + s_cub3d->rays.perp_wall_dist * s_cub3d->rays.ray_dir_x;
	s_cub3d->textures.wall_hit_x -= floor(s_cub3d->textures.wall_hit_x);
	s_cub3d->textures.step = 1.0 * MAP_HEIGHT / s_cub3d->rays.line_height;
	s_cub3d->textures.texture_x = (int)(s_cub3d->textures.wall_hit_x * (double)s_cub3d->textures.wall_texture->width);
	s_cub3d->textures.texture_pos = (draw_start - MAP_HEIGHT / 2 + ((int)(MAP_HEIGHT / s_cub3d->rays.perp_wall_dist) / 2)) * s_cub3d->textures.step;
	s_cub3d->textures.texture_y = (int)s_cub3d->textures.texture_pos & (s_cub3d->textures.wall_texture->height - 1);
	int i = draw_start;
	while (i < draw_end)
	{
		s_cub3d->textures.texture_y = (int)s_cub3d->textures.texture_pos & (s_cub3d->textures.wall_texture->height - 1);
		s_cub3d->textures.texture_pos += s_cub3d->textures.step;
		mlx_put_pixel(s_cub3d->image, x, i, get_color(s_cub3d));
		i++;
	}
}

static uint32_t	get_color(t_cub3d *s_cub3d)
{
	uint8_t	*pixel;
	int	texture_y;
	int	texture_x;

	texture_y = (int)s_cub3d->textures.texture_y;
	texture_x = s_cub3d->textures.texture_x;
	pixel = &s_cub3d->textures.wall_texture->pixels[(texture_y * s_cub3d->textures.wall_texture->width + texture_x) * s_cub3d->textures.wall_texture->bytes_per_pixel];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}
