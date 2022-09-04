/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:49:11 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 19:50:19 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_paused(t_vars *vars)
{
	static int	old_time;

	if (mlx_is_key_down(vars->mlx, MLX_KEY_P))
	{
		if (mlx_get_time() != old_time)
		{
			vars->pause = !vars->pause;
			mlx_set_mouse_pos(vars->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
			if (vars->pause == 1)
				mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_NORMAL);
			if (vars->pause == 0)
				mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_DISABLED);
			old_time = mlx_get_time();
		}
	}
}
