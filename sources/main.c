/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:54:02 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/25 12:32:27 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d scene = {
		{"220,100,0", "225,30,0"},

		{"1111111111111111111111",
		       "1000000000N00000000001",
   		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000111111111000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
		       "1000000000000000000001",
			   "1111111111111111111111",
			   },

		{4, 5},
		{1, 0},
		{0, 0.66},
		NULL,
		NULL,
		{{mlx_load_png("./textures/psycodelic.png"),
		 		mlx_load_png("./textures/psycodelic.png"),
				mlx_load_png("./textures/psycodelic.png"),
				mlx_load_png("./textures/psycodelic.png"),
				},
			NULL,
		0, 0, 0, 0, 0,
		},
		{0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0}
	};
     if (argc != 2)
         handle_error(MSG_INV_ARG_COUNT);
    check_file(argv[1]);
    load_scene(argv[1], &scene);
    run_scene(&scene);
	if (handle_mlx(&s_cub3d.mlx, &s_cub3d.image) == 1)
		return (EXIT_FAILURE);
	mlx_loop_hook(s_cub3d.mlx, (void *)handle_key_hooks, &s_cub3d);
	mlx_loop(s_cub3d.mlx);
	clean_scene(&scene);
	mlx_terminate(s_cub3d.mlx);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.no);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.so);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.we);
	mlx_delete_texture(s_cub3d.textures.loaded_textures.ea);

//     //	char *i = malloc(33);
//     //	ft_memset(i, 0, 33);
//     //	i[0] = '0';
//     //	printf("still reachable main: %c\n", *i);
//     //	i = malloc(33);
//     //	ft_memset(i, 0, 33);
//     //	printf("possibly lost main: %c\n", *i);
//     //	ssize_t f = open("Makefile", O_RDONLY);
//     //	pid_t pido = fork();
//     //	if (pido != 0)
//     //		execl("/bin/ls", "ls", "42", NULL);
//     //	else {
//     if (argc != 2)
//         handle_error(MSG_INV_ARG_COUNT);
//     //		wait(NULL);
//     //	}
//     //	load_scene(&scene, ++argv);
// 	return (EXIT_SUCCESS);
// }
//
    exit(EXIT_FAILURE);
}

void handle_error(const char* message)
{
    write(STDERR_FILENO, MSG_ERROR, MSG_LEN_ERROR);
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, MSG_ERROR_EXIT, MSG_LEN_ERROR_EXIT);
    exit(EXIT_FAILURE);
}