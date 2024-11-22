#include "../includes/cub3d.h"

void	draw_box(mlx_image_t *image, int height, int width, int beginx, int beginy, uint32_t color)
{
	int temp = beginx;
	int x = 0;
	int y = 0;

	while (y < height)
	{
		while (x < width)
		{
			mlx_put_pixel(image, beginx, beginy, color);
			beginx++;
			x++;
		}
		beginx = temp;
		x = 0;
		y += 1;
		beginy++;
	}
}

void	draw_background(t_cub3d *s_cub3d)
{
	draw_box(s_cub3d->image, SCREEN_HEIGHT / 2, SCREEN_WIDTH, 0, 0, RED_COLOR);
	draw_box(s_cub3d->image, SCREEN_HEIGHT / 2, SCREEN_WIDTH, 0,SCREEN_HEIGHT / 2, WHITE_COLOR);
}
