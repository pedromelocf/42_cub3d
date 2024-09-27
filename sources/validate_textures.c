/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:17:06 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/26 22:17:06 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int		check_valid_textures(char *path)
{
	char	**line_matrix;
	int		i;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	while (i++ < 4)
	{
		line_matrix = ft_split(get_next_line(fd), ' ');
		if (ft_get_matrix_len(line_matrix) == 2)
		{
			remove_line_break(&line_matrix[1]);
			if (!check_texture_line(i, line_matrix[0], line_matrix[1]))
				return (close(fd), FALSE);
		}
		else
			return (close(fd), FALSE);
	}
	return (close(fd), TRUE);
}

int		check_texture_line(int i, char *id, char *path)
{
	if (i == 1 && check_valid_file(path))
		return (!ft_strncmp("NO", id, 3));
	else if (i == 2 && check_valid_file(path))
		return (!ft_strncmp("SO", id, 3));
	else if (i == 3 && check_valid_file(path))
		return (!ft_strncmp("WE", id, 3));
	else if (i == 4 && check_valid_file(path))
		return (!ft_strncmp("EA", id, 3));
	return (FALSE);
}