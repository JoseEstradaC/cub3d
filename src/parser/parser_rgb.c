/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:40:52 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 15:06:35 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	str_to_rgb(char **split, t_rgb *rgb)
{
	int	index;

	index = 0;
	while (split[index])
	{
		if ((ft_strlen(split[index]) >= 1 && ft_strlen(split[index]) <= 3)
			&& (ft_atoi(split[index]) >= 0 && ft_atoi(split[index]) <= 255))
		{
			if (index == 0)
				rgb->r = ft_atoi(split[index]);
			if (index == 1)
				rgb->g = ft_atoi(split[index]);
			if (index == 2)
				rgb->b = ft_atoi(split[index]);
		}
		else
			return (1);
		index++;
	}
	return (0);
}

void	rgb_to_hex_in_t_file(t_file *file, char type, t_rgb *rgb)
{
	if (type == 'c')
	{
		free(file->c);
		file->c = NULL;
		file->c_int = ((rgb->r & 0xff) << 24) + ((rgb->g & 0xff) << 16)
			+ ((rgb->b & 0xff) << 8) + 0xff;
	}
	else
	{
		free(file->f);
		file->f = NULL;
		file->f_int = ((rgb->r & 0xff) << 24) + ((rgb->g & 0xff) << 16)
			+ ((rgb->b & 0xff) << 8) + 0xff;
	}
}

int	parser_rgb(t_file *file, char type)
{
	t_rgb	rgb;
	char	**split;

	rgb.r = -1;
	rgb.g = -1;
	rgb.b = -1;
	if (type == 'c')
		split = ft_split(file->c, ',');
	else
		split = ft_split(file->f, ',');
	if (!split)
	{
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	if (ft_split_count(split) != 3 || str_to_rgb(split, &rgb) == 1)
	{
		ft_split_free(split);
		ft_putendl_fd("Error\nInvalid color formart", 2);
		return (-1);
	}
	rgb_to_hex_in_t_file(file, type, &rgb);
	ft_split_free(split);
	return (1);
}
