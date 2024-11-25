/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:27:31 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/25 12:37:49 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_rotate(t_cub3d *s_cub3d, float multiply_factor)
{
	float	vector;

	vector = multiply_factor * M_PI / 180.0;
	s_cub3d->camera_plane.x = s_cub3d->camera_plane.x * cos(vector)
		- s_cub3d->camera_plane.y * sin(vector);
	s_cub3d->camera_plane.y = s_cub3d->camera_plane.x * sin(vector)
		+ s_cub3d->camera_plane.y * cos(vector);
	s_cub3d->player_dir.x = s_cub3d->player_dir.x * cos(vector)
		- s_cub3d->player_dir.y * sin(vector);
	s_cub3d->player_dir.y = s_cub3d->player_dir.x * sin(vector)
		+ s_cub3d->player_dir.y * cos(vector);
}

void	player_move_forward(t_cub3d *s_cub3d)
{
	if (s_cub3d->map[(int)s_cub3d->player_pos.y + (int)s_cub3d->player_dir.y]
		[(int)s_cub3d->player_pos.x] == '0')
		s_cub3d->player_pos.y += s_cub3d->player_dir.y * 0.1;
	if (s_cub3d->map[(int)s_cub3d->player_pos.y][(int)s_cub3d->player_pos.x
		+ (int)s_cub3d->player_dir.x] == '0')
		s_cub3d->player_pos.x += s_cub3d->player_dir.x * 0.1;
}

void	player_move_backward(t_cub3d *s_cub3d)
{
	if (s_cub3d->map[(int)s_cub3d->player_pos.y - (int)s_cub3d->player_dir.y]
		[(int)s_cub3d->player_pos.x] != '1')
		s_cub3d->player_pos.y -= s_cub3d->player_dir.y * 0.1;
	if (s_cub3d->map[(int)s_cub3d->player_pos.y][(int)s_cub3d->player_pos.x
		- (int)s_cub3d->player_dir.x] != '1')
		s_cub3d->player_pos.x -= s_cub3d->player_dir.x * 0.1;
}

void	player_move_left(t_cub3d *s_cub3d)
{
	if (s_cub3d->map[(int)s_cub3d->player_pos.y - (int)s_cub3d->camera_plane.y]
		[(int)s_cub3d->player_pos.x] != '1')
		s_cub3d->player_pos.y -= s_cub3d->camera_plane.y * 0.1;
	if (s_cub3d->map[(int)s_cub3d->player_pos.y - (int)s_cub3d->camera_plane.x]
		[(int)s_cub3d->player_pos.x] != '1')
		s_cub3d->player_pos.x -= s_cub3d->camera_plane.x * 0.1;
}

void	player_move_right(t_cub3d *s_cub3d)
{
	if (s_cub3d->map[(int)s_cub3d->player_pos.y + (int)s_cub3d->camera_plane.y]
		[(int)s_cub3d->player_pos.x] != '1')
		s_cub3d->player_pos.y += s_cub3d->camera_plane.y * 0.1;
	if (s_cub3d->map[(int)s_cub3d->player_pos.y + (int)s_cub3d->camera_plane.x]
		[(int)s_cub3d->player_pos.x] != '1')
		s_cub3d->player_pos.x += s_cub3d->camera_plane.x * 0.1;
}
