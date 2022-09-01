/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:55 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/01 18:04:19 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
