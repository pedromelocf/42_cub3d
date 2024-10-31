#include "../includes/cub3d.h"


static void line(mlx_image_t *image, int x1, int y1, int x2, int y2) ;

void	draw_box(mlx_image_t *image, int height, int width, int beginx, int beginy, int color)
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

void	draw_line(mlx_image_t *image ,int beginx, int beginy, int endx, int endy, float angle)
{
	double theta;
	int x3;
	int y3;

	theta = (double)(angle) * M_PI/180;
	x3 = (int)(beginx+cos(theta)*(endx-beginx) - sin(theta)*(endy - beginy));
	y3 = (int)(beginy+sin(theta)*(endx-beginx) + cos(theta)*(endy - beginy));
	(void)image;

	line(image ,beginx,beginy, x3, y3);
}

void line(mlx_image_t *image, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
		mlx_put_pixel(image, x, y, WHITE_COLOR);
        x += xIncrement;
        y += yIncrement;
			if (i == steps) {
				break;
        }
    }
}