/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:12:37 by jovicto2          #+#    #+#             */
/*   Updated: 2024/11/20 15:12:41 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

mlx_texture_t	*get_texture(char *line)
{
    char			*trimmed_line;
    mlx_texture_t	*texture;

	trimmed_line = ft_strtrim(line, " ");
    texture = NULL;
    if (is_valid_png(trimmed_line))
        texture = mlx_load_png(trimmed_line);
    return (texture);
}

char	*get_color(char *line)
{
	char    *trimmed_line;

    trimmed_line = ft_strtrim(line, " ");
	if (is_valid_color_tag(trimmed_line))
		return (trimmed_line);
   	free(trimmed_line);
    return (NULL);
}

void	get_map(char *line, t_cub3d *scene)
{
	(void)line;
    (void)scene;
}