/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:02:24 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/26 19:07:09 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		check_args(int argc, char **argv);
static int		check_format(char *map);
static int		check_valid_textures(char *path);
static int		check_texture_line(int i, char *id, char *path);

void		validate_config(int argc, char **argv)
{
	if (!check_args(argc, argv))
    	error_handler(1, MSG_INV_ARG, NULL);
    if (!check_valid_file(argv[1]))
    	error_handler(2, MSG_INV_EXEC, NULL);
    if (!check_valid_textures(argv[1]))
    	error_handler(3, MSG_INV_TEXTURES, NULL);
}

static int		check_args(int	argc, char	**argv)
{
	if (argc == 2)
		return (check_format(argv[1]));
	return (FALSE);
}

static int		check_format(char *map)
{
	const char	*format;
    int			map_len;

    format = ".cub";
    map_len = ft_strlen(map);
    if (map_len == 4)
    	return(FALSE);
    while(map_len-- > 4)
     	map++;
    return(!ft_strncmp(map, format, 5));
}

static int		check_valid_textures(char *path)
{
    char	**line_matrix;
	int		i;
	int		fd;

    i = 0;
	fd = open(path, O_RDONLY);
    while (i++ < 4)
    {
    	line_matrix = ft_split(get_next_line(fd), ' ');
        if (ft_get_matrix_len(line_matrix) == 2)
        {
			if (!check_texture_line(i, line_matrix[0], line_matrix[1]))
				return (FALSE);
        }
		else
			return (FALSE);
    }
    return (TRUE);
}

static int		check_texture_line(int i, char *id, char *path)
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
