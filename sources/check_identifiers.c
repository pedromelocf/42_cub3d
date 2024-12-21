/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:58 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/20 20:12:19 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_identifiers_texture(struct mlx_texture **target,
				t_cub3d *scene, char *line);
static void	check_identifiers_rgb(char **color, t_cub3d *scene, char *line);

static void	check_identifiers_texture(struct mlx_texture **target,
	t_cub3d *scene, char *line)
{
	if (*target == NULL)
		*target = get_texture(line);
	else
	{
		free(line);
		clean_scene(scene, MSG_INV_FILE_ELEMENTS);
	}
}

static void	check_identifiers_rgb(char **color, t_cub3d *scene, char *line)
{
	if (*color == NULL)
		*color = get_rgb(line);
	else
	{
		free(line);
		clean_scene(scene, MSG_INV_FILE_ELEMENTS);
	}
}

bool	check_identifiers(char *line, t_cub3d *scene, int fd)
{
	if (is_empty_line(line))
		return (false);
	if (ft_strnstr(line, "NO ", 3))
		check_identifiers_texture(&scene->textures.loaded_textures.no, scene,
			line);
	else if (ft_strnstr(line, "SO ", 3))
		check_identifiers_texture(&scene->textures.loaded_textures.so, scene,
			line);
	else if (ft_strnstr(line, "WE ", 3))
		check_identifiers_texture(&scene->textures.loaded_textures.we, scene,
			line);
	else if (ft_strnstr(line, "EA ", 3))
		check_identifiers_texture(&scene->textures.loaded_textures.ea, scene,
			line);
	else if (ft_strnstr(line, "F ", 2))
		check_identifiers_rgb(&scene->rgb_colors.floor_color, scene, line);
	else if (ft_strnstr(line, "C ", 2))
		check_identifiers_rgb(&scene->rgb_colors.ceiling_color, scene, line);
	else
	{
		get_map(line, scene, fd);
		return (true);
	}
	return (false);
}

void	fill_player_coordinates(t_cub3d *scene, int x, int y)
{
	scene->player_pos.x = y + 0.5;
	scene->player_pos.y = x + 0.5;
	if (scene->map[x][y] == 'N')
	{
		scene->player_dir.y = -1;
		scene->camera_plane.x = 0.66;
	}
	else if (scene->map[x][y] == 'S')
	{
		scene->player_dir.y = 1;
		scene->camera_plane.x = -0.66;
	}
	else if (scene->map[x][y] == 'W')
	{
		scene->player_dir.x = -1;
		scene->camera_plane.y = -0.66;
	}
	else if (scene->map[x][y] == 'E')
	{
		scene->player_dir.x = 1;
		scene->camera_plane.y = 0.66;
	}
}
