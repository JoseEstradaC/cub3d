/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:42:24 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 17:04:36 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(t_file *file, int *i, int x, int y)
{
	if (is_sprite(file->map[y][x]))
	{
		file->sprites.sprites[*i].x = x;
		file->sprites.sprites[*i].y = y;
		file->sprites.sprites[(*i)++].texture = (int)file->map[y][x] + 2 - '0';
	}
}

int	free_file_struct(t_file *file)
{
	free(file->no);
	free(file->so);
	free(file->we);
	free(file->ea);
	free(file->f);
	free(file->c);
	ft_split_free(file->raw_data);
	free(file->sprites.sprites);
	return (0);
}
