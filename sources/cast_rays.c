/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:29:03 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/19 18:14:28 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int cast_rays(t_cub3d *s_cub3d)
{
	double	camera_x;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		s_cub3d->rays.ray_dir_x = s_cub3d->player_dir.x + s_cub3d->camera_plane.x * camera_x;
		s_cub3d->rays.ray_dir_y = s_cub3d->player_dir.y + s_cub3d->camera_plane.y * camera_x;
		dda(s_cub3d);
		draw_line(x, s_cub3d);
	}
	return (0);
}

void	dda(t_cub3d *s_cub3d)
{
	s_cub3d->dda.delta_dist_x =  (s_cub3d->rays.ray_dir_x == 0) ? 1e30 : fabs(1 / s_cub3d->rays.ray_dir_x);
	s_cub3d->dda.delta_dist_y = (s_cub3d->rays.ray_dir_y == 0) ? 1e30 : fabs(1 / s_cub3d->rays.ray_dir_y);
	s_cub3d->dda.map_x = (int)s_cub3d->player_pos.x;
	s_cub3d->dda.map_y = (int)s_cub3d->player_pos.y;
	int hit = 0;

	if (s_cub3d->rays.ray_dir_x < 0)
	{
		s_cub3d->dda.step_x = -1;
		s_cub3d->dda.side_dist_x = ((int)s_cub3d->player_pos.x - s_cub3d->dda.map_x) * s_cub3d->dda.delta_dist_x;
	}
	else
	{
		s_cub3d->dda.step_x = 1;
		s_cub3d->dda.side_dist_x = (s_cub3d->dda.map_x + 1.0 - (int)s_cub3d->player_pos.x) * s_cub3d->dda.delta_dist_x;
	}
	if (s_cub3d->rays.ray_dir_y < 0)
	{
		s_cub3d->dda.step_y = -1;
		s_cub3d->dda.side_dist_y = ((int)s_cub3d->player_pos.y - s_cub3d->dda.map_y) * s_cub3d->dda.delta_dist_y;
	}
	else
	{
		s_cub3d->dda.step_y = 1;
		s_cub3d->dda.side_dist_y = (s_cub3d->dda.map_y + 1.0 - (int)s_cub3d->player_pos.y) * s_cub3d->dda.delta_dist_y;
	}

	while (hit == 0)
	{
		if (s_cub3d->dda.side_dist_x < s_cub3d->dda.side_dist_y)
		{
			s_cub3d->dda.side_dist_x += s_cub3d->dda.delta_dist_x;
			s_cub3d->dda.map_x += s_cub3d->dda.step_x;
			s_cub3d->rays.side_hit = WEST_EAST;
		}
		else
		{
			s_cub3d->dda.side_dist_y += s_cub3d->dda.delta_dist_y;
			s_cub3d->dda.map_y += s_cub3d->dda.step_y;
			s_cub3d->rays.side_hit = NORTH_SOUTH;
		}
		if (s_cub3d->map[s_cub3d->dda.map_y][s_cub3d->dda.map_x] == '1') hit = 1;
 	}
	if (s_cub3d->rays.side_hit == WEST_EAST)
		s_cub3d->rays.perp_wall_dist = (s_cub3d->dda.side_dist_x - s_cub3d->dda.delta_dist_x);
	else
		s_cub3d->rays.perp_wall_dist = (s_cub3d->dda.side_dist_y  - s_cub3d->dda.delta_dist_y);
}

void	draw_line(int x, t_cub3d *s_cub3d)
{
	s_cub3d->rays.line_height = (int)(SCREEN_HEIGHT / s_cub3d->rays.perp_wall_dist);
	s_cub3d->rays.draw_start = -s_cub3d->rays.line_height / 2 + SCREEN_HEIGHT / 2;
	if (s_cub3d->rays.draw_start < 0 || s_cub3d->rays.perp_wall_dist == 0)
		s_cub3d->rays.draw_start = 0;
    s_cub3d->rays.draw_end = s_cub3d->rays.line_height / 2 + SCREEN_HEIGHT / 2;
	if (s_cub3d->rays.draw_end >= SCREEN_HEIGHT || s_cub3d->rays.perp_wall_dist == 0)
		s_cub3d->rays.draw_end = SCREEN_HEIGHT - 1;
	if (s_cub3d->rays.side_hit == NORTH_SOUTH && s_cub3d->rays.ray_dir_y < 0)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.no_loaded_texture;
	else if (s_cub3d->rays.side_hit == NORTH_SOUTH && s_cub3d->rays.ray_dir_y > 0)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.so_loaded_texture;
	else if (s_cub3d->rays.side_hit == WEST_EAST && s_cub3d->rays.ray_dir_x > 0)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.ea_loaded_texture;
	else if (s_cub3d->rays.side_hit == WEST_EAST && s_cub3d->rays.ray_dir_x < 0)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.we_loaded_texture;
	draw_texturized_line(x, s_cub3d);
}

void	draw_box(mlx_image_t *image, int height, int width, int beginx, int beginy, uint32_t color)
{
	int temp = beginx;
	int x = 0;
	int y = 0;

	while (y < height)
	{
		while (x < width)
		{
			mlx_put_pixel(image, beginx, beginy, color);
			beginx++;
			x++;
		}
		beginx = temp;
		x = 0;
		y += 1;
		beginy++;
	}
}

void	draw_background(t_cub3d *s_cub3d)
{
	draw_box(s_cub3d->image, SCREEN_HEIGHT / 2, SCREEN_WIDTH, 0, 0, RED_COLOR);
	draw_box(s_cub3d->image, SCREEN_HEIGHT / 2, SCREEN_WIDTH, 0,SCREEN_HEIGHT / 2, WHITE_COLOR);
}