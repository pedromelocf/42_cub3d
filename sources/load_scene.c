/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:12:37 by jovicto2          #+#    #+#             */
/*   Updated: 2024/11/20 15:12:41 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	process_file(t_cub3d *scene);
static void	check_identifiers(char *line, t_cub3d *scene);
static void	set_aditionals(t_cub3d *scene);

void	load_scene(char *file, t_cub3d *scene)
{
    ft_bzero(scene, sizeof(t_cub3d));
    scene->file = file;
	process_file(scene);
    check_elements(scene);
    set_aditionals(scene);
}

static void	process_file(t_cub3d *scene)
{
    int		fd;
    char	*line;

    fd = open(scene->file, O_RDONLY);
    if (fd < 0)
        handle_error(MSG_INV_FILE_OPEN);
    line = ft_get_next_line(fd);
    while (*line && !ft_strchr(line, '1'))
    {
		check_identifiers(line, scene);
        free(line);
        line = ft_get_next_line(fd);
    }
    get_map(line, scene, fd);
    free(line);
    close(fd);
}

static void	check_identifiers(char *line, t_cub3d *scene)
{
	if (ft_strnstr(line, "NO ", 3))
		scene->textures.loaded_textures.no = get_texture(line);
    else if (ft_strnstr(line, "SO ", 3))
		scene->textures.loaded_textures.so = get_texture(line);
    else if (ft_strnstr(line, "WE ", 3))
        scene->textures.loaded_textures.we = get_texture(line);
    else if (ft_strnstr(line, "EA ", 3))
		scene->textures.loaded_textures.ea = get_texture(line);
	else if (ft_strnstr(line, "F ", 2))
		scene->rgb_colors.floor_color = get_color(line);
	else if (ft_strnstr(line, "C ", 2))
		scene->rgb_colors.ceiling_color = get_color(line);
}

static void	set_aditionals(t_cub3d *scene)
{
	(void)scene;
}