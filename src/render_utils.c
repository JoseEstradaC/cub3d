/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:55 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/01 21:23:25 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_pos
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
}			t_pos;

void	clean_img(mlx_image_t *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			mlx_put_pixel(img, x, y, 0x3c75deff);
			x++;
		}
		y++;
	}
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			mlx_put_pixel(img, x, y, 0x32a852ff);
			x++;
		}
		y++;
	}
}

// Calculate x-coordinate in camera space, which box of the map,
// and length of ray from current position to next x or y-side
t_pos	calc_pos(t_vars *vars, int x)
{
	t_pos	pos;
	double	camera_x;

	camera_x = 2 * x / (double)SCREENWIDTH - 1;
	pos.ray_dir_x = vars->dir_x + vars->plane_x * camera_x;
	pos.ray_dir_y = vars->dir_y + vars->plane_y * camera_x;
	pos.map_x = (int)vars->pos_x;
	pos.map_y = (int)vars->pos_y;
	if (pos.ray_dir_x == 0)
		pos.delta_dist_x = 1e30;
	else
		pos.delta_dist_x = fabs(1 / pos.ray_dir_x);
	if (pos.ray_dir_y == 0)
		pos.delta_dist_y = 1e30;
	else
		pos.delta_dist_y = fabs(1 / pos.ray_dir_y);
	return (pos);
}
