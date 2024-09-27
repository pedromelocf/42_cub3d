/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:15:10 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/26 22:15:26 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_valid_colors(char *path)
{
	char	**line_matrix;
	int		i;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	get_next_line(fd);
	while (i++ < 2)
	{
		line_matrix = ft_split(get_next_line(fd), ' ');
		if (ft_get_matrix_len(line_matrix) == 2)
		{
			remove_line_break(&line_matrix[1]);
			if (!check_color_line(i, line_matrix[0], line_matrix[1]))
				return (close(fd), FALSE);
		}
		else
			return (close(fd), FALSE);
	}
	return (close(fd), TRUE);
}

int		check_color_line(int i, char *id, char *rgbs)
{
	if (i == 1 && check_rgbs(rgbs))
		return (!ft_strncmp("F", id, 2));
	else if (i == 2 && check_rgbs(rgbs))
		return (!ft_strncmp("C", id, 2));
	return (FALSE);
}

int		check_rgbs(char *rgbs)
{
	char	**rgbs_matrix;
	int		i;

	i = 0;
	rgbs_matrix = ft_split(rgbs, ',');
	if (!rgbs_matrix)
		return (FALSE);
	if (ft_get_matrix_len(rgbs_matrix) != 3)
		return (FALSE);
	while (i < 3)
	{
		if (ft_atoi_cub(rgbs_matrix[i]) < 0 || ft_atoi_cub(rgbs_matrix[i]) > 255)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
