/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/20 15:12:37 by jovicto2          #+#    #+#             */
/*   Updated: 2024/11/20 15:12:41 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static void	fill_map(char ***map, t_list *lines);
static void	fill_player_coordinates(t_cub3d *scene, int x, int y);

mlx_texture_t	*get_texture(char *line)
{
	char *trimmed_line;
	mlx_texture_t *texture;

	trimmed_line = ft_strtrim(line + 3, " \n");
	texture = NULL;
	if (is_valid_png(trimmed_line))
		texture = mlx_load_png(trimmed_line);
	free(trimmed_line);
	return (texture);
}

char	*get_rgb(char *line)
{
	char *trimmed_line;

	trimmed_line = ft_strtrim(line + 2, " \n");
	if (is_valid_color_tag(trimmed_line))
		return (trimmed_line);
	free(trimmed_line);
	return (NULL);
}

void	get_map(char *line, t_cub3d *scene, int fd)
{
	t_list *lines;

	lines = NULL;
	while (line)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = ft_get_next_line(fd);
	}
	if (is_valid_map(lines))
		fill_map(&scene->map, lines);
//	ft_lstclear(&lines, free);
}

static void	fill_map(char ***map, t_list *list)
{
	t_list *lines;
	int index;
	int size;

	lines = list;
	size = ft_lstsize(lines);
	index = 0;
	*map = ft_calloc(size + 1, sizeof(char *));
	while (lines && size > index)
	{
		(*map)[index] = ft_strtrim(lines->content, "\n");
		lines = lines->next;
		index++;
	}
}

void	get_player_elements(t_cub3d *scene)
{
	int x;
	int y;
	int player_count;

	x = 0;
	player_count = 0;
	while (scene->map[x])
	{
		y = 0;
		while (scene->map[x][y])
		{
			if (ft_strchr(PLAYER_CHARS, scene->map[x][y]))
			{
				fill_player_coordinates(scene, x, y);
				player_count++;
			}
			y++;
		}
		x++;
	}
	if (player_count != 1)
		scene->player_pos.x = PLAYER_ERROR;
}

static void	fill_player_coordinates(t_cub3d *scene, int x, int y)
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
