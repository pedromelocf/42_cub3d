/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:27:31 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 12:25:57 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_rotate(t_cub3d *s_cub3d, float multipli_factor)
{
	s_cub3d->camera_plane.x = s_cub3d->camera_plane.x * cos(multipli_factor)
		- s_cub3d->camera_plane.y * sin(multipli_factor);
	s_cub3d->camera_plane.y = s_cub3d->camera_plane.x * sin(multipli_factor)
		+ s_cub3d->camera_plane.y * cos(multipli_factor);
	s_cub3d->player_dir.x = s_cub3d->player_dir.x * cos(multipli_factor)
		- s_cub3d->player_dir.y * sin(multipli_factor);
	s_cub3d->player_dir.y = s_cub3d->player_dir.x * sin(multipli_factor)
		+ s_cub3d->player_dir.y * cos(multipli_factor);
}

void	player_move_forward(t_cub3d *s_cub3d, float move_speed,
		double colision_distance)
{
	if (s_cub3d->map[(int)(s_cub3d->player_pos.y + s_cub3d->player_dir.y
		* colision_distance)][(int)s_cub3d->player_pos.x] != '1' &&
    	s_cub3d->map[(int)s_cub3d->player_pos.y][(int)(s_cub3d->player_pos.x
		+ s_cub3d->player_dir.x * colision_distance)] != '1')
	{
       	s_cub3d->player_pos.y += s_cub3d->player_dir.y * move_speed;
		s_cub3d->player_pos.x += s_cub3d->player_dir.x * move_speed;
	}
}

void	player_move_backward(t_cub3d *s_cub3d, float move_speed, double colision_distance)
{
	if (s_cub3d->map[(int)(s_cub3d->player_pos.y - s_cub3d->player_dir.y *
		(move_speed + colision_distance))][(int)s_cub3d->player_pos.x] != '1' &&
      	s_cub3d->map[(int)s_cub3d->player_pos.y][(int)(s_cub3d->player_pos.x
		- s_cub3d->player_dir.x * (move_speed + colision_distance))] != '1')
	{
		s_cub3d->player_pos.y -= s_cub3d->player_dir.y * move_speed;
		s_cub3d->player_pos.x -= s_cub3d->player_dir.x * move_speed;
	}
}

void	player_move_left(t_cub3d *s_cub3d, float move_speed, double colision_distance)
{
	if (s_cub3d->map[(int)(s_cub3d->player_pos.y - s_cub3d->camera_plane.y *
		colision_distance)] [(int)s_cub3d->player_pos.x] != '1' &&
     	s_cub3d->map[(int)s_cub3d->player_pos.y] [(int)(s_cub3d->player_pos.x
		- s_cub3d->camera_plane.x * colision_distance)] != '1')
	{
		s_cub3d->player_pos.y -= s_cub3d->camera_plane.y * move_speed;
		s_cub3d->player_pos.x -= s_cub3d->camera_plane.x * move_speed;
	}
}

void	player_move_right(t_cub3d *s_cub3d, float move_speed, double colision_distance)
{
	if (s_cub3d->map[(int)(s_cub3d->player_pos.y + s_cub3d->camera_plane.y *
		colision_distance)] [(int)s_cub3d->player_pos.x] != '1' &&
      	s_cub3d->map[(int)s_cub3d->player_pos.y][(int)(s_cub3d->player_pos.x
		+ s_cub3d->camera_plane.x * colision_distance)] != '1')
	{
		s_cub3d->player_pos.y += s_cub3d->camera_plane.y * move_speed;
		s_cub3d->player_pos.x += s_cub3d->camera_plane.x * move_speed;
	}
}
