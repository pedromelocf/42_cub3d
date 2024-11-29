/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/13 23:08:10 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
//	t_scene	scene;
	(void)argv;
//	char *i = malloc(33);
//	ft_memset(i, 0, 33);
//	i[0] = '0';
//	printf("still reachable main: %c\n", *i);
//	i = malloc(33);
//	ft_memset(i, 0, 33);
//	printf("possibly lost main: %c\n", *i);
//	ssize_t f = open("Makefile", O_RDONLY);
//	pid_t pido = fork();
//	if (pido != 0)
//		execl("/bin/ls", "ls", "42", NULL);
//	else {
		if (argc != 2)
			handle_error(MSG_ARG_COUNT);
//		wait(NULL);
//	}
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
