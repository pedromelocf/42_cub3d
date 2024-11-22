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

static void set_ray_dir(t_cub3d *s_cub3d, double camera_x);
static void set_map(t_cub3d *s_cub3d);
static void set_step_and_side_distances(t_cub3d *s_cub3d);
static void set_delta_distances(t_cub3d *s_cub3d);

void ray_calculations(t_cub3d *s_cub3d, double camera_x)
{
	set_ray_dir(s_cub3d, camera_x);
	set_map(s_cub3d);
	set_delta_distances(s_cub3d);
	set_step_and_side_distances(s_cub3d);
}

static void set_ray_dir(t_cub3d *s_cub3d, double camera_x)
{
	s_cub3d->rays.ray_dir_x = s_cub3d->player_dir.x + s_cub3d->camera_plane.x * camera_x;
	s_cub3d->rays.ray_dir_y = s_cub3d->player_dir.y + s_cub3d->camera_plane.y * camera_x;
}

static void set_map(t_cub3d *s_cub3d)
{
	s_cub3d->dda.map_x = (int)s_cub3d->player_pos.x;
	s_cub3d->dda.map_y = (int)s_cub3d->player_pos.y;
}

static void set_delta_distances(t_cub3d *s_cub3d)
{
	if (s_cub3d->rays.ray_dir_x == 0)
		s_cub3d->dda.delta_dist_x = 1e30;
	else
		s_cub3d->dda.delta_dist_x = fabs(1 / s_cub3d->rays.ray_dir_x);
	if (s_cub3d->rays.ray_dir_y == 0)
		s_cub3d->dda.delta_dist_y = 1e30;
	else
		s_cub3d->dda.delta_dist_y = fabs(1 / s_cub3d->rays.ray_dir_y);
}

static void set_step_and_side_distances(t_cub3d *s_cub3d)
{
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
}
