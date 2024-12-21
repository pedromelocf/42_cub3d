/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:12:37 by jovicto2          #+#    #+#             */
/*   Updated: 2024/12/20 19:58:49 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	process_file(t_cub3d *scene);
static bool	is_map_playable(char **map);

void	load_scene(char *file, t_cub3d *scene)
{
	ft_bzero(scene, sizeof(t_cub3d));
	scene->file = file;
	process_file(scene);
	check_elements(scene);
}

static void	process_file(t_cub3d *scene)
{
	int		fd;
	char	*line;
	bool	not_map_line;

	fd = open(scene->file, O_RDONLY);
	if (fd < 0)
		handle_error(MSG_INV_FILE_OPEN);
	line = ft_get_next_line(fd);
	while (line && *line)
	{
		not_map_line = check_identifiers(line, scene, fd);
		if (!not_map_line)
			free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (scene->map)
		get_player_elements(scene);
}

void	check_elements(t_cub3d *scene)
{
	if (scene->player_pos.x == PLAYER_ERROR
		|| !scene->textures.loaded_textures.no
		|| !scene->textures.loaded_textures.so
		|| !scene->textures.loaded_textures.we
		|| !scene->textures.loaded_textures.ea || !scene->rgb_colors.floor_color
		|| !scene->rgb_colors.ceiling_color || !scene->map)
		clean_scene(scene, MSG_INV_FILE_MAP);
	flood_fill(scene->map, ft_arr_len(scene->map), scene->player_pos);
	if (!is_map_playable(scene->map))
		clean_scene(scene, MSG_INV_FILE_ELEMENTS);
}

void	flood_fill(char **map, int x, t_coordinates c)
{
	if (c.y < 0 || c.y >= x || c.x < 0
		|| (int)c.x >= (int)ft_strlen(map[(int)c.y])
		|| map[(int)c.y][(int)c.x] == '1' || map[(int)c.y][(int)c.x] == '#')
		return ;
	if (map[(int)c.y][(int)c.x] == '0')
		map[(int)c.y][(int)c.x] = '#';
	flood_fill(map, x, (t_coordinates){c.x - 1, c.y});
	flood_fill(map, x, (t_coordinates){c.x + 1, c.y});
	flood_fill(map, x, (t_coordinates){c.x, c.y - 1});
	flood_fill(map, x, (t_coordinates){c.x, c.y + 1});
}

static bool	is_map_playable(char **map)
{
	int	i;
	int	map_size;

	i = -1;
	map_size = (int)ft_arr_len(map);
	while (map[0][++i])
		if (map[0][i] == '#')
			return (false);
	i = -1;
	while (map[map_size - 1][++i])
		if (map[map_size - 1][i] == '#')
			return (false);
	i = 0;
	while (++i < map_size)
		if (map[i][0] == '#' || map[i][ft_strlen(map[i]) - 1] == '#')
			return (false);
	return (true);
}
