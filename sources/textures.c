/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:27:34 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 19:50:16 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_texture_info(t_cub3d *s_cub3d);
static void	set_wall_texture(t_cub3d *s_cub3d);
static void	set_texture_north_east(t_cub3d *s_cub3d);
static void	set_texture_south_west(t_cub3d *s_cub3d);

void	load_texture_info(t_cub3d *s_cub3d)
{
	set_wall_texture(s_cub3d);
	set_texture_info(s_cub3d);
}

static void	set_wall_texture(t_cub3d *s_cub3d)
{
	if (s_cub3d->rays.side_hit == NORTH)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.no;
	else if (s_cub3d->rays.side_hit == SOUTH)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.so;
	else if (s_cub3d->rays.side_hit == EAST)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.ea;
	else if (s_cub3d->rays.side_hit == WEST)
		s_cub3d->textures.wall_texture = s_cub3d->textures.loaded_textures.we;
}

static void	set_texture_info(t_cub3d *s_cub3d)
{
	if (s_cub3d->rays.side_hit == NORTH || s_cub3d->rays.side_hit == EAST)
		set_texture_north_east(s_cub3d);
	else if (s_cub3d->rays.side_hit == SOUTH || s_cub3d->rays.side_hit == WEST)
		set_texture_south_west(s_cub3d);
}

static void	set_texture_north_east(t_cub3d *s_cub3d)
{
	s_cub3d->textures.step = 1.0 * s_cub3d->textures.wall_texture->height
		/ s_cub3d->wall.line_height;
	s_cub3d->textures.texture_x = ((int)(s_cub3d->textures.wall_hit_x
				* (double)s_cub3d->textures.wall_texture->width));
	s_cub3d->textures.texture_pos = (s_cub3d->wall.draw_start - SCREEN_HEIGHT
			/ 2 + s_cub3d->wall.line_height / 2) * s_cub3d->textures.step;
	s_cub3d->textures.texture_y = ((int)s_cub3d->textures.texture_pos);
}

static void	set_texture_south_west(t_cub3d *s_cub3d)
{
	s_cub3d->textures.step = 1.0 * s_cub3d->textures.wall_texture->height
		/ s_cub3d->wall.line_height;
	s_cub3d->textures.texture_x = s_cub3d->textures.wall_texture->width - 1
		- ((int)(s_cub3d->textures.wall_hit_x
				* (double)s_cub3d->textures.wall_texture->width));
	s_cub3d->textures.texture_pos = (s_cub3d->wall.draw_start - SCREEN_HEIGHT
			/ 2 + s_cub3d->wall.line_height / 2) * s_cub3d->textures.step;
	s_cub3d->textures.texture_y = ((int)s_cub3d->textures.texture_pos);
}
