/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/10/29 20:16:17 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main()
{
	t_cub3d s_cub3d = {
		{"./path_to_the_north_texture", "./path_to_the_south_texture",
		 " ./path_to_the_west_texture", "./path_to_the_east_texture"},
		{"220,100,0", "225,30,0"},
		{"11111\0", "10001\0", "10001\0", "10N01\0", "10001\0", "10001\0", "10001\0","11111\0"},
		{3, 2, 270},
		NULL,
		NULL
	};

	if (handle_mlx(&s_cub3d.mlx, &s_cub3d.image))
		return (EXIT_FAILURE);

	draw_box(s_cub3d.image, HEIGHT, WIDTH, 0, 0, BLACK_COLOR);
	draw_player_minimap(s_cub3d.image, &s_cub3d);
	mlx_loop_hook(s_cub3d.mlx, (void *)handle_key_hooks, &s_cub3d);
	mlx_loop(s_cub3d.mlx);
	mlx_terminate(s_cub3d.mlx);
	return (EXIT_SUCCESS);
}

void draw_player_minimap (mlx_image_t *image, t_cub3d *s_cub3d)
{
	int x = 0;
	int y = 0;

	while (y < 8) // change 8 to map height
	{
		x = 0;
		while (x < 6) // change 6 to map width
		{
			if (s_cub3d->map[y][x] == '1')
				draw_box(s_cub3d->image, 30, 30, x * 32 + 50, y * 32 + 420, GREY_COLOR);
			else
			{
				draw_box(image, 5, 5, WIDTH * s_cub3d->player_pos.x / 6 - 2,HEIGHT * s_cub3d->player_pos.y / 8 - 2 ,RED_COLOR);// change 6 to map width and 8 to map height
				if (s_cub3d->map[y][x] != '\0' && s_cub3d->map[y][x] != ' ')
				{
					draw_box(s_cub3d->image, 31, 31, x * 29 + 56, y * 31 + 423, WHITE_COLOR);
					draw_line(image, WIDTH * s_cub3d->player_pos.x / 6,
							  HEIGHT * s_cub3d->player_pos.y / 8,
							  WIDTH * s_cub3d->player_pos.x / 6 - 1 + 100,
							  HEIGHT * s_cub3d->player_pos.y / 8 - 5 + 2,
							  s_cub3d->player_pos.angle_orientation);
				}
			}
			x++;
		}
		y++;
	}
}