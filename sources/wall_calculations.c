/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calculations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:27:37 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 19:50:17 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	line_height_calculation(t_cub3d *s_cub3d);
static void	draw_start_calculation(t_cub3d *s_cub3d);
static void	draw_end_calculation(t_cub3d *s_cub3d);
static void	set_wall_hit_x(t_cub3d *s_cub3d);

void	wall_calculations(t_cub3d *s_cub3d)
{
	line_height_calculation(s_cub3d);
	draw_start_calculation(s_cub3d);
	draw_end_calculation(s_cub3d);
	set_wall_hit_x(s_cub3d);
}

static void	line_height_calculation(t_cub3d *s_cub3d)
{
	s_cub3d->wall.line_height = (int)(SCREEN_HEIGHT
			/ s_cub3d->rays.perp_wall_dist);
}

static void	draw_start_calculation(t_cub3d *s_cub3d)
{
	s_cub3d->wall.draw_start = -s_cub3d->wall.line_height / 2 + SCREEN_HEIGHT
		/ 2;
	if (s_cub3d->wall.draw_start < 0 || s_cub3d->rays.perp_wall_dist == 0)
		s_cub3d->wall.draw_start = 0;
}

static void	draw_end_calculation(t_cub3d *s_cub3d)
{
	s_cub3d->wall.draw_end = s_cub3d->wall.line_height / 2 + SCREEN_HEIGHT / 2;
	if (s_cub3d->wall.draw_end >= SCREEN_HEIGHT
		|| s_cub3d->rays.perp_wall_dist == 0)
		s_cub3d->wall.draw_end = SCREEN_HEIGHT - 1;
}

void	set_wall_hit_x(t_cub3d *s_cub3d)
{
	if (s_cub3d->rays.side_hit == WEST || s_cub3d->rays.side_hit == EAST)
		s_cub3d->textures.wall_hit_x = s_cub3d->player_pos.y
			+ s_cub3d->rays.perp_wall_dist * s_cub3d->rays.ray_dir_y;
	else
		s_cub3d->textures.wall_hit_x = s_cub3d->player_pos.x
			+ s_cub3d->rays.perp_wall_dist * s_cub3d->rays.ray_dir_x;
	s_cub3d->textures.wall_hit_x -= floor(s_cub3d->textures.wall_hit_x);
}
