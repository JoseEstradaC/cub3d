/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:55 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 13:07:33 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

void	clean_img(mlx_image_t *img, uint32_t ceiling, uint32_t floor)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
			mlx_put_pixel(img, x++, y, ceiling);
		y++;
	}
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
			mlx_put_pixel(img, x++, y, floor);
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

// Return NO, SO, WE or EA
// x_dire = pos->map_x - vars->pos_x
int	get_side(int side, int x_dire, int y_dire)
{
	if (side == 1 && y_dire >= 0)
		side += 2;
	if (side == 0 && x_dire >= 0)
		side += 2;
	return (side);
}
