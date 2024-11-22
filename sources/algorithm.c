#include "../includes/cub3d.h"

static void	camera_calculation(int x, double *camera_x);

int algorithm(t_cub3d *s_cub3d)
{
	double	camera_x;
	int x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_calculation(x, &camera_x);
		ray_calculations(s_cub3d, camera_x);
		dda(s_cub3d);
		wall_calculations(s_cub3d);
		load_texture_info(s_cub3d);
		draw_texturized_line(x, s_cub3d);
		x++;
	}
	return (0);
}

static void	camera_calculation(int x, double *camera_x)
{
	*camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
}
