/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:27:21 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/25 12:28:24 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_perp_wall_distance(t_cub3d *s_cub3d);

void	dda(t_cub3d *s_cub3d)
{
	int	hit;

	hit = 0;
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
		if (s_cub3d->map[s_cub3d->dda.map_y][s_cub3d->dda.map_x] == '1')
			hit = 1;
	}
	set_perp_wall_distance(s_cub3d);
}

static void	set_perp_wall_distance(t_cub3d *s_cub3d)
{
	if (s_cub3d->rays.side_hit == WEST_EAST)
		s_cub3d->rays.perp_wall_dist = (s_cub3d->dda.side_dist_x
				- s_cub3d->dda.delta_dist_x);
	else
		s_cub3d->rays.perp_wall_dist = (s_cub3d->dda.side_dist_y
				- s_cub3d->dda.delta_dist_y);
}
