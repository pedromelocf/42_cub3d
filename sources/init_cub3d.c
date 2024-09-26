/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr  >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:05:05 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/25 20:05:19 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		check_args(int	argc, char	**argv);
static int		check_format(char *map);

void	init_cub(int argc, char **argv, t_cub3d	*cub3d)
{
  	(void)cub3d;
	if(!check_args(argc, argv))
          error_handler(1, MSG_INV_ARG, cub3d);
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

