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

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	(void)argc;
	(void)argv;
	t_cub3d s_cub3d = {
		{"./path_to_the_north_texture", "./path_to_the_south_texture",
			" ./path_to_the_west_texture", "./path_to_the_east_texture"},
		{"220,100,0", "225,30,0"},
		{"11111", "10001", "10N01", "10001", "10001", "10001", "10001",
			"11111"}};
	(void)s_cub3d;
	if (handle_mlx(&mlx, &image))
		return (EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
