/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:14:26 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/25 12:28:33 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_mlx(mlx_t **mlx, mlx_image_t **image)
{
	*mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D", true);
	if (!(*mlx))
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	*image = mlx_new_image(*mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!(*image))
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}

	if (mlx_image_to_window(*mlx, *image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

void	handle_key_hooks(t_cub3d *s_cub3d)
{
	double	rotation_speed;
	double	move_speed;
	double	colision_distance;

	rotation_speed = s_cub3d->mlx->delta_time * ROTATE_SPEED_MULTI;
	move_speed = s_cub3d->mlx->delta_time * MOVE_SPEED_MULTI;
	colision_distance = move_speed * COLISION_DISTANCE_MULTI;

	if (mlx_is_key_down(s_cub3d->mlx, ESC))
		mlx_close_window(s_cub3d->mlx);
	if (mlx_is_key_down(s_cub3d->mlx, RIGHT))
		player_rotate(s_cub3d, rotation_speed);
	if (mlx_is_key_down(s_cub3d->mlx, LEFT))
		player_rotate(s_cub3d, -rotation_speed);
	if (mlx_is_key_down(s_cub3d->mlx, W))
		player_move_forward(s_cub3d, move_speed, colision_distance);
	if (mlx_is_key_down(s_cub3d->mlx, S))
		player_move_backward(s_cub3d, move_speed, colision_distance);
	if (mlx_is_key_down(s_cub3d->mlx, A))
		player_move_left(s_cub3d, move_speed, colision_distance);
	if (mlx_is_key_down(s_cub3d->mlx, D))
		player_move_right(s_cub3d, move_speed, colision_distance);
	draw_background(s_cub3d);
	algorithm(s_cub3d);
}
