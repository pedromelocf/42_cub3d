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
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_RIGHT))
	{
		float vector = 1.5 * M_PI / 180.0;
		s_cub3d->camera_plane.plane_x = s_cub3d->camera_plane.plane_x * cos(vector) - s_cub3d->camera_plane.plane_y * sin(vector);
		s_cub3d->camera_plane.plane_y = s_cub3d->camera_plane.plane_x * sin(vector) + s_cub3d->camera_plane.plane_y * cos(vector);
		s_cub3d->player_dir.dir_x =  s_cub3d->player_dir.dir_x * cos(vector)  - s_cub3d->player_dir.dir_y * sin(vector);
		s_cub3d->player_dir.dir_y =  s_cub3d->player_dir.dir_x * sin(vector) + s_cub3d->player_dir.dir_y * cos(vector) ;
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_LEFT))
	{
		float vector = -1.5 * M_PI / 180.0;
		s_cub3d->camera_plane.plane_x = s_cub3d->camera_plane.plane_x * cos(vector) - s_cub3d->camera_plane.plane_y * sin(vector);
		s_cub3d->camera_plane.plane_y = s_cub3d->camera_plane.plane_x * sin(vector) + s_cub3d->camera_plane.plane_y * cos(vector);
		s_cub3d->player_dir.dir_x =  s_cub3d->player_dir.dir_x * cos(vector) - s_cub3d->player_dir.dir_y * sin(vector);
		s_cub3d->player_dir.dir_y =  s_cub3d->player_dir.dir_x * sin(vector) + s_cub3d->player_dir.dir_y * cos(vector);
	}
//	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_W))
//		s_cub3d->player_pos.pos_y += 0.01;
//	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_A))
//		s_cub3d->player_pos.pos_y -= 0.01;
//	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_S))
//		s_cub3d->player_pos.pos_x += 0.01;
//	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_D))
//		s_cub3d->player_pos.pos_x -= 0.01;
	draw_background(s_cub3d);
	cast_rays(s_cub3d);
}
