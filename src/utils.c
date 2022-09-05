/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:12:58 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 17:35:23 by jestrada         ###   ########.fr       */
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
