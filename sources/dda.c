#include "../includes/cub3d.h"

static int	calculate_step(t_cub3d *s_cub3d, char c);

void	perform_dda(t_cub3d	*s_cub3d)
{
	int	mapX = (int)s_cub3d->player_pos.x;
	int mapY = (int)s_cub3d->player_pos.y;
	int stepX = calculate_step(s_cub3d, 'x');
	int stepY = calculate_step(s_cub3d, 'y');

	double sideDistX, sideDistY, deltaDistX, deltaDistY;

	if (s_cub3d->player_pos.angle_orientation == 90 || s_cub3d->player_pos.angle_orientation == 270)
		deltaDistX = 1;
	else
		deltaDistX = fabs(1 / cos(s_cub3d->player_pos.angle_orientation * M_PI / 180));

	if (s_cub3d->player_pos.angle_orientation == 0 || s_cub3d->player_pos.angle_orientation == 180)
		deltaDistY = 1;
	else
		deltaDistY = fabs(1 / sin(s_cub3d->player_pos.angle_orientation * M_PI / 180));

	if (s_cub3d->player_pos.angle_orientation > 180)
    	sideDistX = (s_cub3d->player_pos.x - mapX) * deltaDistX;
	else
    	sideDistX = (mapX + 1.0 - s_cub3d->player_pos.x) * deltaDistX;

	if (s_cub3d->player_pos.angle_orientation > 90 && s_cub3d->player_pos.angle_orientation < 270) // Ray is going up (negative Y)
    	sideDistY = (s_cub3d->player_pos.y - mapY) * deltaDistY;
	else
    	sideDistY = (mapY + 1.0 - s_cub3d->player_pos.y) * deltaDistY;

	while (s_cub3d->map[mapY][mapX] != '1')
	{
		if (sideDistX > sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
		}

		if (s_cub3d->map[mapY][mapX] == '1')
		{
			float rayzise = sqrt((sideDistY * sideDistY) + (sideDistX * sideDistX));
			printf("Ray size = %f\n", rayzise);
		}
	}
}

static int	calculate_step(t_cub3d *s_cub3d, char c)
{
	int	step;

	step = 0;
	if (c == 'x')
	{
		if (s_cub3d->player_pos.angle_orientation > 90 && s_cub3d->player_pos.angle_orientation < 270)
			step = 1;
		else
			step = -1;
	}
	else
	{
		if (s_cub3d->player_pos.angle_orientation > 180)
			step = 1;
		else
			step = -1;
	}
	return (step);
}
