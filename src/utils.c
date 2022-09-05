/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:12:58 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 18:59:08 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(void)
{
	int	i;

	i = 0;
	while (i < NTEXTURES)
		mlx_delete_texture(g_textures[i++]);
}

int	intro(t_vars *vars)
{
	static int	first;

	if (mlx_get_time() < 2)
	{
		if (!first)
		{
			first = 1;
			mlx_draw_texture(vars->img, g_textures[8], 0, 0);
			mlx_image_to_window(vars->mlx, vars->img, 0, 0);
		}
		return (1);
	}
	return (0);
}
