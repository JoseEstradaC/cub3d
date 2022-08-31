#include "cub3d.h"

void	clean_img(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREENWIDTH)
	{
		y = 0;
		while (y < SCREENHEIGHT)
		{
			mlx_put_pixel(img, x, y, 0);
			y++;
		}
		x++;
	}
}

