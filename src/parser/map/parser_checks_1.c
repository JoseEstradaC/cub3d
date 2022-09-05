/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:48:00 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 16:00:26 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	surrounding_by_zero_or_1(char **map, int x, int y)
{
	if (!is_zero_or_one_or_player(map[y - 1][x - 1]))
		return (0);
	if (!is_zero_or_one_or_player(map[y - 1][x]))
		return (0);
	if (!is_zero_or_one_or_player(map[y - 1][x + 1]))
		return (0);
	if (!is_zero_or_one_or_player(map[y][x - 1]))
		return (0);
	if (!is_zero_or_one_or_player(map[y][x + 1]))
		return (0);
	if (!is_zero_or_one_or_player(map[y + 1][x - 1]))
		return (0);
	if (!is_zero_or_one_or_player(map[y + 1][x]))
		return (0);
	if (!is_zero_or_one_or_player(map[y + 1][x + 1]))
		return (0);
	return (1);
}

int	surround_check(char **map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if ((map[y][x] == '0' || is_sprite(map[y][x]))
				&& !surrounding_by_zero_or_1(map, x, y))
			{
				ft_putendl_fd("Map is not surround by walls\n", 2);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	border_check(char **map)
{
	int	x;
	int	y;
	int	error;

	error = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] != '\0')
		{
			if ((y == 0 || y == ft_split_count(map) - 1)
				&& is_zero_or_player(map[y][x]))
				error = 1;
			if (((x == 0 || x == ((int)ft_strlen(map[y]) - 2))
					&& is_zero_or_player(map[y][x])))
				error = 1;
		}
	}
	if (error)
		ft_putendl_fd("Map is not surround by walls\n", 2);
	return (!error);
}

int	is_valid_char_map_line(char *line)
{
	int	index;

	index = 0;
	while (line[index] != '\n' && line[index] != '\0')
	{
		if (is_zero_or_one_or_player(line[index]) == 0 && line[index] != ' ')
			return (0);
		index++;
	}
	return (1);
}

int	is_sprite(char c)
{
	if (c == '2' || c == '3' || c == '4')
		return (1);
	return (0);
}
