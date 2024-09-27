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
# define MSG_INV_COLORS "Invalid RGB colors configurations\n"

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

void			validate_config(int argc, char **argv);
int				check_valid_textures(char *path);
int				check_texture_line(int i, char *id, char *path);
int				check_valid_file(char *path);
int				check_valid_colors(char *path);
int				check_color_line(int i, char *id, char *rgbs);
int				check_rgbs(char *rgbs);
int				ft_atoi_cub(const char *nptr);
void			remove_line_break(char **old_string);
void			error_handler(int status, char *message, t_cub3d *cub3d);

#endif
