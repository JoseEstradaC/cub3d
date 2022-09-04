/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:55:02 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 17:02:16 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_max_width(char **map)
{
	int		index;
	size_t	max_width;

	index = 0;
	max_width = 0;
	while (map[index] != NULL)
	{
		if (ft_strlen(map[index]) > max_width)
			max_width = ft_strlen(map[index]);
		index++;
	}
	return (max_width);
}

int	normalize_map(char **map, size_t max_width)
{
	int		index;
	char	*tmp_line;
	int		x;

	index = 0;
	while (map[index])
	{
		tmp_line = (char *)ft_calloc(sizeof(char), max_width);
		if (!tmp_line)
		{
			ft_putendl_fd("Error", 2);
			return (-1);
		}
		ft_memset(tmp_line, 'x', max_width - 1);
		x = -1;
		while (map[index][++x] != '\n' && map[index][x] != '\0')
			tmp_line[x] = map[index][x];
		free(map[index]);
		map[index] = tmp_line;
		index++;
	}
	change_space_with_x(map);
	return (1);
}

char	**parse_map(char **map)
{
	if (!map)
		return (NULL);
	if (border_check(map) == 0 || normalize_map(map, get_max_width(map)) == -1
		|| is_valid_map_content(map) == 0 || surround_check(map) == 0)
		return (NULL);
	return (map);
}
