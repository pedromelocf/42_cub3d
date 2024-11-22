/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:14:26 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/10/29 20:15:53 by pmelo-ca         ###   ########.fr       */
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
	if (mlx_is_key_down(s_cub3d->mlx, ESC))
		mlx_close_window(s_cub3d->mlx);
	if (mlx_is_key_down(s_cub3d->mlx, RIGHT))
		player_rotate(s_cub3d, (float)1.5);
	if (mlx_is_key_down(s_cub3d->mlx, LEFT))
		player_rotate(s_cub3d, (float)-1.5);
	if (mlx_is_key_down(s_cub3d->mlx, W))
		player_move_forward(s_cub3d);
	if (mlx_is_key_down(s_cub3d->mlx, S))
		player_move_backward(s_cub3d);
	if (mlx_is_key_down(s_cub3d->mlx, A))
		player_move_left(s_cub3d);
	if (mlx_is_key_down(s_cub3d->mlx, D))
		player_move_right(s_cub3d);
	draw_background(s_cub3d);
	algorithm(s_cub3d);
}

