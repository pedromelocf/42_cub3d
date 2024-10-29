/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/10/28 20:44:08 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
//	t_scene	scene;
	(void)argv;
	if (argc != 2)
		handle_error(MSG_ARG_COUNT);
//	load_scene(&scene, ++argv);
	return (EXIT_SUCCESS);
}

void	handle_error(const char *message)
{
	write(STDERR_FILENO, MSG_ERROR, MSG_LEN_ERROR);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, MSG_ERROR_EXIT, MSG_LEN_ERROR_EXIT);
	exit(EXIT_FAILURE);
}
