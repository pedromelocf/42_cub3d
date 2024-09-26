/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr  >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/25 11:35:27 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/lib/libft.h"

# define FALSE 0
# define TRUE 1
# define MSG_INV_ARG "Invalid arguments\n"
# define MSG_INV_EXEC "Invalid .cub map file\n"
# define MSG_INV_TEXTURES "Invalid texture configurations\n"

typedef struct s_rgb_colors
{
	char	*floor_color;
	char	*ceiling_color;
}	t_rgb_colors;

typedef struct s_texture_paths
{
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
}	t_texture_paths;

typedef struct s_cub3d
{
	t_texture_paths	*texture_paths;
	t_rgb_colors	*rgb_colors;
}	t_cub3d;

void	validate_config(int argc, char **argv);
void	error_handler(int status, char *message, t_cub3d *cub3d);
int		check_valid_file(char *path);

#endif
