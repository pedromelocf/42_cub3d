/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/05 16:19:25 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main()
{
	t_cub3d s_cub3d = {
		{"./path_to_the_north_texture", "./path_to_the_south_texture",
		 " ./path_to_the_west_texture", "./path_to_the_east_texture"},
		{"220,100,0", "225,30,0"},

		{"1111111111111111111111",
		       "1000000000N00000000001",
   		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000111111111000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
			   "1111111111111111111111",
			   },

		{4, 5},
		{1, 0},
		{0, 0.66},
		NULL,
		NULL
	};
	if (handle_mlx(&s_cub3d.mlx, &s_cub3d.image) == 1)
		return (EXIT_FAILURE);
	draw_background(&s_cub3d);
	cast_rays(&s_cub3d);
	mlx_loop_hook(s_cub3d.mlx, (void *)handle_key_hooks, &s_cub3d);
	mlx_loop(s_cub3d.mlx);
	mlx_terminate(s_cub3d.mlx);
	return (EXIT_SUCCESS);
}
