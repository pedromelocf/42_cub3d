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

int cast_rays(t_cub3d *s_cub3d)
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double  perp_wall_dist;

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		camera_x = 2 * x / (double)MAP_WIDTH - 1;
		raydir_x = s_cub3d->player_dir.dir_x + s_cub3d->camera_plane.plane_x * camera_x;
		raydir_y = s_cub3d->player_dir.dir_y + s_cub3d->camera_plane.plane_y * camera_x;
		perp_wall_dist = dda(s_cub3d, raydir_x, raydir_y);
		draw_rays(x, perp_wall_dist, s_cub3d);
	}
	return (0);
}

double	dda(t_cub3d *s_cub3d, double raydir_x, double raydir_y)
{
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x =  (raydir_x == 0) ? 1e30 : fabs(1 / raydir_x);
	double	delta_dist_y = (raydir_y == 0) ? 1e30 : fabs(1 / raydir_y);
	int step_x;
	int step_y;
	int map_x = (int)s_cub3d->player_pos.pos_x;
	int map_y = (int)s_cub3d->player_pos.pos_y;
	int hit = 0;
	int side = 0;
	double perp_wall_dist;

	if (raydir_x < 0)
	{
		step_x = -1;
		side_dist_x = ((int)s_cub3d->player_pos.pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - (int)s_cub3d->player_pos.pos_x) * delta_dist_x;
	}
	if (raydir_y < 0)
	{
		step_y = -1;
		side_dist_y = ((int)s_cub3d->player_pos.pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - (int)s_cub3d->player_pos.pos_y) * delta_dist_y;
	}

	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (s_cub3d->map[map_y][map_x] == '1') hit = 1;
 	}
	if (side == 0)
		perp_wall_dist = (side_dist_x - delta_dist_x);
	else
		perp_wall_dist = (side_dist_y  - delta_dist_y);
	return (perp_wall_dist);
}

void	draw_rays(int x, double perp_wall_dist, t_cub3d *s_cub3d)
{
	int lineHeight = (int)(MAP_HEIGHT / perp_wall_dist);
	int draw_start = -lineHeight / 2 + MAP_HEIGHT / 2;
	if (draw_start < 0 || perp_wall_dist == 0)
		draw_start = 0;
    int draw_end = lineHeight / 2 + MAP_HEIGHT / 2;
	if (draw_end >= MAP_HEIGHT || perp_wall_dist == 0)
		draw_end = MAP_HEIGHT - 1;
	draw_line_black(x, draw_start, draw_end, s_cub3d);
}

void	draw_line_red(int x, int draw_start,int draw_end, t_cub3d *s_cub3d)
{
	while (draw_start < draw_end)
	{
		mlx_put_pixel(s_cub3d->image, x, draw_start, RED_COLOR);
		draw_start++;
	}
}

void	draw_line_white(int x, int draw_start,int draw_end, t_cub3d *s_cub3d)
{
	while (draw_start < draw_end)
	{
		mlx_put_pixel(s_cub3d->image, x, draw_start, WHITE_COLOR);
		draw_start++;
	}
}

void	draw_line_black(int x, int draw_start,int draw_end, t_cub3d *s_cub3d)
{
	while (draw_start < draw_end)
	{
		mlx_put_pixel(s_cub3d->image, x, draw_start, BLACK_COLOR);
		draw_start++;
	}
}
void	draw_box(mlx_image_t *image, int height, int width, int beginx, int beginy, uint32_t color)
{
	int temp = beginx;
	int x = 0;
	int y = 0;

	while (y < height)
	{
		while (x < width)
		{
			mlx_put_pixel(image, beginx, beginy, color);
			beginx++;
			x++;
		}
		beginx = temp;
		x = 0;
		y += 1;
		beginy++;
	}
}

void	draw_background(t_cub3d *s_cub3d)
{
	draw_box(s_cub3d->image, MAP_HEIGHT / 2, MAP_WIDTH, 0, 0, GREY_COLOR);
	draw_box(s_cub3d->image, MAP_HEIGHT / 2, MAP_WIDTH, 0,MAP_HEIGHT / 2, WHITE_COLOR);
}