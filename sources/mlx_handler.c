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
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(s_cub3d->mlx);
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_RIGHT))
	{
		float vector = 1.5 * M_PI / 180.0;
		s_cub3d->camera_plane.x = s_cub3d->camera_plane.x * cos(vector) - s_cub3d->camera_plane.y * sin(vector);
		s_cub3d->camera_plane.y = s_cub3d->camera_plane.x * sin(vector) + s_cub3d->camera_plane.y * cos(vector);
		s_cub3d->player_dir.x =  s_cub3d->player_dir.x * cos(vector)  - s_cub3d->player_dir.y * sin(vector);
		s_cub3d->player_dir.y =  s_cub3d->player_dir.x * sin(vector) + s_cub3d->player_dir.y * cos(vector) ;
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_LEFT))
	{
		float vector = -1.5 * M_PI / 180.0;
		s_cub3d->camera_plane.x = s_cub3d->camera_plane.x * cos(vector) - s_cub3d->camera_plane.y * sin(vector);
		s_cub3d->camera_plane.y = s_cub3d->camera_plane.x * sin(vector) + s_cub3d->camera_plane.y * cos(vector);
		s_cub3d->player_dir.x =  s_cub3d->player_dir.x * cos(vector) - s_cub3d->player_dir.y * sin(vector);
		s_cub3d->player_dir.y =  s_cub3d->player_dir.x * sin(vector) + s_cub3d->player_dir.y * cos(vector);
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_W))
	{
		if (s_cub3d->map[(int)s_cub3d->player_pos.y + (int)s_cub3d->player_dir.y][(int)s_cub3d->player_pos.x] == '0')
			s_cub3d->player_pos.y += s_cub3d->player_dir.y * 0.1;
		if (s_cub3d->map[(int)s_cub3d->player_pos.y][(int)s_cub3d->player_pos.x + (int)s_cub3d->player_dir.x] == '0')
			s_cub3d->player_pos.x += s_cub3d->player_dir.x * 0.1;
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_S))
	{
		if (s_cub3d->map[(int)s_cub3d->player_pos.y - (int)s_cub3d->player_dir.y][(int)s_cub3d->player_pos.x] != '1')
			s_cub3d->player_pos.y -= s_cub3d->player_dir.y  * 0.1;
		if (s_cub3d->map[(int)s_cub3d->player_pos.y][(int)s_cub3d->player_pos.x - (int)s_cub3d->player_dir.x] != '1')
			s_cub3d->player_pos.x -= s_cub3d->player_dir.x  * 0.1;
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_A))
	{
		if (s_cub3d->map[(int)s_cub3d->player_pos.y - (int)s_cub3d->camera_plane.y][(int)s_cub3d->player_pos.x] != '1')
			s_cub3d->player_pos.y -= s_cub3d->camera_plane.y * 0.1;
		if (s_cub3d->map[(int)s_cub3d->player_pos.y - (int)s_cub3d->camera_plane.x][(int)s_cub3d->player_pos.x] != '1')
			s_cub3d->player_pos.x -= s_cub3d->camera_plane.x * 0.1;
	}
	if (mlx_is_key_down(s_cub3d->mlx, MLX_KEY_D))
	{
		if (s_cub3d->map[(int)s_cub3d->player_pos.y + (int)s_cub3d->camera_plane.y][(int)s_cub3d->player_pos.x] != '1')
			s_cub3d->player_pos.y += s_cub3d->camera_plane.y * 0.1;
		if (s_cub3d->map[(int)s_cub3d->player_pos.y + (int)s_cub3d->camera_plane.x][(int)s_cub3d->player_pos.x] != '1')
			s_cub3d->player_pos.x += s_cub3d->camera_plane.x * 0.1;
	}
	draw_background(s_cub3d);
	cast_rays(s_cub3d);
}
