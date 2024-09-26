/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:31:36 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/25 20:31:36 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_handler(int status, char *message, t_cub3d *cub3d)
{
  	(void)cub3d;
	ft_dprintf(2, "%s", message);
//	clear_cub(cub3d);
	exit(status);
}
