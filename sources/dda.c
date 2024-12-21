/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:27:21 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 19:50:06 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_perp_wall_distance(t_cub3d *s_cub3d);
static void	set_side_hit(t_cub3d *s_cub3d, int side);

void	dda(t_cub3d *s_cub3d)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (s_cub3d->dda.side_dist_x < s_cub3d->dda.side_dist_y)
		{
			s_cub3d->dda.side_dist_x += s_cub3d->dda.delta_dist_x;
			s_cub3d->dda.map_x += s_cub3d->dda.step_x;
			side = 1;
		}
		else
		{
			s_cub3d->dda.side_dist_y += s_cub3d->dda.delta_dist_y;
			s_cub3d->dda.map_y += s_cub3d->dda.step_y;
			side = 2;
		}
		if (s_cub3d->map[s_cub3d->dda.map_y][s_cub3d->dda.map_x] == '1')
			hit = 1;
	}
	set_side_hit(s_cub3d, side);
	set_perp_wall_distance(s_cub3d);
}

static void	set_perp_wall_distance(t_cub3d *s_cub3d)
{
	if (s_cub3d->rays.side_hit == WEST || s_cub3d->rays.side_hit == EAST)
		s_cub3d->rays.perp_wall_dist = (s_cub3d->dda.side_dist_x
				- s_cub3d->dda.delta_dist_x);
	else
		s_cub3d->rays.perp_wall_dist = (s_cub3d->dda.side_dist_y
				- s_cub3d->dda.delta_dist_y);
}

static void	set_side_hit(t_cub3d *s_cub3d, int side)
{
	if (side == 1)
	{
		if (s_cub3d->rays.ray_dir_x > 0)
			s_cub3d->rays.side_hit = EAST;
		else if (s_cub3d->rays.ray_dir_x < 0)
			s_cub3d->rays.side_hit = WEST;
	}
	else if (side == 2)
	{
		if (s_cub3d->rays.ray_dir_y < 0)
			s_cub3d->rays.side_hit = NORTH;
		else if (s_cub3d->rays.ray_dir_y > 0)
			s_cub3d->rays.side_hit = SOUTH;
	}
}
