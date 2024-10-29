/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:14:26 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/10/29 20:15:53 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_mlx(mlx_t **mlx, mlx_image_t **image)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!(*mlx))
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	*image = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (!(*image))
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(*mlx, *image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}
