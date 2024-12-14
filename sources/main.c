/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/25 12:32:27 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main()
{
	t_cub3d s_cub3d = {
		{"220,100,0", "225,30,0"},

		// {"1111111111111111111111",
		//        "1000000000N00000000001",
		//        "1000000000000000000001",
		//        "1000000000000000000001",
		//        "1000000000000000000001",
		//        "1000000000000000000001",
		//        "1000000111111111000001",
		//        "1000000000000000000001",
		//        "1000000000000000000001",
		//        "1000000000000000000001",
		//        "1000000000000000000001",
		//        "1000000000000000000001",
		// 	   "1111111111111111111111",
		// 	   },

		{"11111",
			"100001",
			"100N01",
			"111111",
			},

		{1.5, 1.5},
		{1, 0},
		{0, 0.66},
		NULL,
		NULL,

		{{mlx_load_png("./textures/directions/N.png"),
		 		mlx_load_png("./textures/directions/S.png"),
				mlx_load_png("./textures/directions/W.png"),
				mlx_load_png("./textures/directions/E.png"),
				},
			NULL,
		0, 0, 0, 0, 0,
		},
		{0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0}
	};
	if (handle_mlx(&s_cub3d.mlx, &s_cub3d.image) == 1)
		return (EXIT_FAILURE);
	mlx_loop_hook(s_cub3d.mlx, (void *)handle_key_hooks, &s_cub3d);
	mlx_loop(s_cub3d.mlx);
	mlx_terminate(s_cub3d.mlx);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.no);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.so);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.we);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.ea);
	return (EXIT_SUCCESS);
}
