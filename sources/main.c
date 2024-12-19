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

int	main(int argc, char **argv)
{
	t_cub3d scene;

	if (argc != 2)
		handle_error(MSG_INV_ARG_COUNT);
    check_file(argv[1]);
    load_scene(argv[1], &scene);
    run_scene(&scene);
	clean_scene(&scene, NULL);
}

void run_scene(t_cub3d *scene)
{
	mlx_t *mlx;
	mlx_image_t *image;

	if (handle_mlx(&mlx, &image) == 1)
		handle_error(MSG_INV_MLX_INIT);
	scene->mlx = mlx;
	scene->image = image;
	mlx_loop_hook(mlx, (void *)handle_key_hooks, scene);
	mlx_loop(mlx);
}

void clean_scene(t_cub3d *scene, char *message)
{
	if (scene->rgb_colors.floor_color)
		free(scene->rgb_colors.floor_color);
    if (scene->rgb_colors.ceiling_color)
		free(scene->rgb_colors.ceiling_color);
	if (scene->map)
    	ft_for_each((void **)scene->map, free);
    if (scene->mlx)
		free(scene->mlx);
    if (scene->textures.loaded_textures.no)
      	free(scene->textures.loaded_textures.no);
    if (scene->textures.loaded_textures.so)
      	free(scene->textures.loaded_textures.so);
    if (scene->textures.loaded_textures.we)
      	free(scene->textures.loaded_textures.we);
    if (scene->textures.loaded_textures.ea)
      	free(scene->textures.loaded_textures.ea);
    if (scene->textures.wall_texture)
	  	free(scene->textures.wall_texture);
    if (scene->file)
		free(scene->file);
    if (message)
      	handle_error(message);
    exit(EXIT_SUCCESS);
}

void handle_error(const char* message)
{
    write(STDERR_FILENO, MSG_ERROR, MSG_LEN_ERROR);
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, MSG_ERROR_EXIT, MSG_LEN_ERROR_EXIT);
    exit(EXIT_FAILURE);
}

//	t_cub3d scene = {
//		{"220,100,0", "225,30,0"},
//
//		{"1111111111111111111111",
//		       "1000000000N00000000001",
//   		       "1000000000000000000001",
//		       "1000000000000000000001",
//		       "1000000000000000000001",
//		       "1000000000000000000001",
//		       "1000000111111111000001",
//		       "1000000000000000000001",
//		       "1000000000000000000001",
//		       "1000000000000000000001",
//		       "1000000000000000000001",
//		       "1000000000000000000001",
//			   "1111111111111111111111",
//			   },
//
//		{4, 5},
//		{1, 0},
//		{0, 0.66},
//		NULL,
//		NULL,
//		{{mlx_load_png("./textures/psycodelic.png"),
//		 		mlx_load_png("./textures/psycodelic.png"),
//				mlx_load_png("./textures/psycodelic.png"),
//				mlx_load_png("./textures/psycodelic.png"),
//				},
//			NULL,
//		0, 0, 0, 0, 0,
//		},
//		{0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0}
//	};
