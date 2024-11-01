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
	*mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!(*mlx))
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	*image = mlx_new_image(*mlx, WIDTH, HEIGHT);
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
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(s_cub3d->mlx);
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_W) && s_cub3d->player_pos.y > 0.1 ) {
		s_cub3d->player_pos.y -= 0.05;
		printf("POSY: %f\n", s_cub3d->player_pos.y);
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_S) && s_cub3d->player_pos.y < 7.9 ) {
		s_cub3d->player_pos.y += 0.05;
		printf("POSY: %f\n", s_cub3d->player_pos.y);
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_A) && s_cub3d->player_pos.x > 0.1 ) {
		s_cub3d->player_pos.x -= 0.05;
		printf("POSX: %f\n", s_cub3d->player_pos.x);
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_D) && s_cub3d->player_pos.x < 5.9 ) {
		s_cub3d->player_pos.x += 0.05;
		printf("POSX: %f\n", s_cub3d->player_pos.x);
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_LEFT)) {
		if (s_cub3d->player_pos.angle_orientation >= 0 && s_cub3d->player_pos.angle_orientation <= 360)
			s_cub3d->player_pos.angle_orientation -= 1;
		if (s_cub3d->player_pos.angle_orientation < 0)
			s_cub3d->player_pos.angle_orientation = 360;
		printf("ANG: %f\n", s_cub3d->player_pos.angle_orientation);
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_RIGHT)) {
		if (s_cub3d->player_pos.angle_orientation >= 0 && s_cub3d->player_pos.angle_orientation < 360)
			s_cub3d->player_pos.angle_orientation += 1;
		if (s_cub3d->player_pos.angle_orientation >= 360)
			s_cub3d->player_pos.angle_orientation = 0;
		printf("ANG: %f\n", s_cub3d->player_pos.angle_orientation);
	}
	draw_box(s_cub3d->image, HEIGHT, WIDTH, 0, 0, BLACK_COLOR);
	draw_player_minimap(s_cub3d->image, s_cub3d);
}
