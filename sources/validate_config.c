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

void		validate_config(int argc, char **argv)
{
	if (!check_args(argc, argv))
    	error_handler(1, MSG_INV_ARG, NULL);
    if (!check_valid_file(argv[1]))
    	error_handler(2, MSG_INV_EXEC, NULL);
    if (!check_valid_textures(argv[1]))
    	error_handler(3, MSG_INV_TEXTURES, NULL);
    if (!check_valid_colors(argv[1]))
    	error_handler(4, MSG_INV_COLORS, NULL);
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
