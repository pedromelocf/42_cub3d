/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 12:25:37 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(char **map);
void	print_scene(t_cub3d *cub);

int	main(int argc, char **argv)
{
	t_cub3d	scene;

	if (argc != 2)
		handle_error(MSG_INV_ARG_COUNT);
	check_file(argv[1]);
	load_scene(argv[1], &scene);
	// print_scene(&scene);
	run_scene(&scene);
	clean_scene(&scene, NULL);
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			write(STDOUT_FILENO, &map[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	print_scene(t_cub3d *cub)
{
	// Print RGB colors
	printf("RGB Colors:\n");
	printf("  Floor color:   %s\n",
			cub->rgb_colors.floor_color ? cub->rgb_colors.floor_color : "(null)");
	printf("  Ceiling color: %s\n",
			cub->rgb_colors.ceiling_color ? cub->rgb_colors.ceiling_color : "(null)");
	// Print Map using the provided print_map function
	print_map(cub->map);
	// Print Player position and direction
	printf("Player:\n");
	printf("  Position: (x: %f, y: %f)\n", cub->player_pos.x,
			cub->player_pos.y);
	printf("  Direction: (x: %f, y: %f)\n", cub->player_dir.x,
			cub->player_dir.y);
	printf("  Camera plane: (x: %f, y: %f)\n", cub->camera_plane.x,
			cub->camera_plane.y);
	// Print MLX references
	printf("MLX:\n");
	printf("  mlx pointer:   %p\n", (void *)cub->mlx);
	printf("  image pointer: %p\n", (void *)cub->image);
	// Print textures
	printf("Textures:\n");
	printf("  NO texture: %p\n", (void *)cub->textures.loaded_textures.no);
	printf("  SO texture: %p\n", (void *)cub->textures.loaded_textures.so);
	printf("  WE texture: %p\n", (void *)cub->textures.loaded_textures.we);
	printf("  EA texture: %p\n", (void *)cub->textures.loaded_textures.ea);
	printf("  Wall texture: %p\n", (void *)cub->textures.wall_texture);
	printf("  Wall hit x:   %f\n", cub->textures.wall_hit_x);
	printf("  Step:         %f\n", cub->textures.step);
	printf("  Texture pos:  %f\n", cub->textures.texture_pos);
	printf("  Texture y:    %d\n", cub->textures.texture_y);
	printf("  Texture x:    %d\n", cub->textures.texture_x);
	// Print rays
	printf("Rays:\n");
	printf("  Ray dir x:       %f\n", cub->rays.ray_dir_x);
	printf("  Ray dir y:       %f\n", cub->rays.ray_dir_y);
	printf("  Perp wall dist:  %f\n", cub->rays.perp_wall_dist);
	printf("  Side hit:        %d\n", cub->rays.side_hit);
	// Print DDA
	printf("DDA:\n");
	printf("  Side dist x:   %f\n", cub->dda.side_dist_x);
	printf("  Side dist y:   %f\n", cub->dda.side_dist_y);
	printf("  Delta dist x:  %f\n", cub->dda.delta_dist_x);
	printf("  Delta dist y:  %f\n", cub->dda.delta_dist_y);
	printf("  Step x:        %d\n", cub->dda.step_x);
	printf("  Step y:        %d\n", cub->dda.step_y);
	printf("  Map x:         %d\n", cub->dda.map_x);
	printf("  Map y:         %d\n", cub->dda.map_y);
	// Print Wall
	printf("Wall:\n");
	printf("  Line height: %d\n", cub->wall.line_height);
	printf("  Draw start:  %d\n", cub->wall.draw_start);
	printf("  Draw end:    %d\n", cub->wall.draw_end);
	// Print file name
	printf("File: %s\n", cub->file ? cub->file : "(null)");
}

void	run_scene(t_cub3d *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	if (handle_mlx(&mlx, &image) == 1)
		handle_error(MSG_INV_MLX_INIT);
	scene->mlx = mlx;
	scene->image = image;
	mlx_loop_hook(mlx, (void *)handle_key_hooks, scene);
	mlx_loop(mlx);
}

void	clean_scene(t_cub3d *scene, char *message)
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
	if (message)
		handle_error(message);
	exit(EXIT_SUCCESS);
}

void	handle_error(const char *message)
{
	write(STDERR_FILENO, MSG_ERROR, MSG_LEN_ERROR);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, MSG_ERROR_EXIT, MSG_LEN_ERROR_EXIT);
	exit(EXIT_FAILURE);
}
