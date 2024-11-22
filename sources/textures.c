#include "../includes/cub3d.h"

static uint32_t	get_color(double texture_y, int texture_x, t_cub3d *s_cub3d);

void	draw_texturized_line(int x, int draw_start, int draw_end, t_cub3d *s_cub3d, double perp_wall_dist)
{
	s_cub3d->textures.wall_hit_x = s_cub3d->player_pos.pos_y + perp_wall_dist * s_cub3d->player_dir.dir_y;
	s_cub3d->textures.wall_hit_x -= floor(s_cub3d->textures.wall_hit_x);
	s_cub3d->textures.step = 1.0 * MAP_HEIGHT / (int)(MAP_HEIGHT / perp_wall_dist); //set divisor to line_height variable
	s_cub3d->textures.texture_x = (int)(s_cub3d->textures.wall_hit_x * (double)s_cub3d->textures.loaded_textures.ea_loaded_texture->width);
	s_cub3d->textures.texture_pos = (draw_start - MAP_HEIGHT / 2 + ((int)(MAP_HEIGHT / perp_wall_dist) / 2)) * s_cub3d->textures.step;

	int i = draw_start;

	while (i < draw_end)
	{
		s_cub3d->textures.texture_y = (int)s_cub3d->textures.texture_pos & (s_cub3d->textures.loaded_textures.ea_loaded_texture->height - 1);
		s_cub3d->textures.texture_pos += s_cub3d->textures.step;
		mlx_put_pixel(s_cub3d->image, x, i, get_color(s_cub3d->textures.texture_y, s_cub3d->textures.texture_x, s_cub3d));
		i++;
	}
}

static uint32_t	get_color(double texture_y, int texture_x, t_cub3d *s_cub3d)
{
	uint8_t	*pixel;

	pixel = &s_cub3d->textures.loaded_textures.ea_loaded_texture->pixels[((int)texture_y * s_cub3d->textures.loaded_textures.ea_loaded_texture->width + texture_x) * s_cub3d->textures.loaded_textures.ea_loaded_texture->bytes_per_pixel];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}
