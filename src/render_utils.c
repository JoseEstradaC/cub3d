/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:55 by jestrada          #+#    #+#             */
/*   Updated: 2022/08/31 16:51:19 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
