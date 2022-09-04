/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:48:00 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 17:12:57 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_zero_or_player(char c)
{
	if (c == '0' || is_player(c))
		return (1);
	return (0);
}

int	is_zero_or_one_or_player(char c)
{
	if (is_zero_or_player(c) || c == '1')
		return (1);
	return (0);
}

int	is_terrain(char c)
{
	if (c == '0' || c == '1' || c == 'x')
		return (1);
	return (0);
}

int	is_valid_map_content(char **map)
{
	int	x;
	int	y;
	int	player_count;
	int	error;

	player_count = 0;
	error = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] != '\0')
		{
			if (is_player(map[y][x]))
				player_count++;
			else if (!is_terrain(map[y][x]))
				error++;
		}
	}
	if (player_count != 1 || error != 0)
	{
		ft_putendl_fd("Error, map content is invalid\n", 2);
		return (0);
	}
	return (1);
}
