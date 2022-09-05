/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:49:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 17:28:54 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	sprite_count(t_file *file)
{
	int	y;
	int	x;
	int	ret;

	ret = 0;
	y = 0;
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x])
		{
			if (is_sprite(file->map[y][x]))
				ret++;
			x++;
		}
		y++;
	}
	file->sprites.num_sprites = ret;
	return (ret);
}

int	set_sprites_struct(t_file *file)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	file->sprites.sprites = ft_calloc(sprite_count(file), sizeof(t_sprite));
	if (!file->sprites.sprites)
	{
		ft_putendl_fd("Error", 2);
		return (1);
	}
	y = -1;
	while (file->map[++y])
	{
		x = -1;
		while (file->map[y][++x])
			add_sprite(file, &i, x, y);
	}
	if (i > 100)
	{
		ft_putendl_fd("Error\n Only can put 100 sprites", 2);
		return (1);
	}
	return (0);
}

void	set_player_pos(t_file *file)
{
	int	y;
	int	x;

	y = 0;
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x])
		{
			if (is_player(file->map[y][x]))
			{
				file->player_y = y;
				file->player_x = x;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	parser_img_png(t_file *file)
{
	if (ft_strlen(file->ea) <= 4 || end_with_png(file->ea) == 0
		|| ft_strlen(file->we) <= 4 || end_with_png(file->we) == 0
		|| ft_strlen(file->no) <= 4 || end_with_png(file->no) == 0
		|| ft_strlen(file->so) <= 4 || end_with_png(file->so) == 0)
	{
		ft_putendl_fd("Error\nimg is not .png file", 2);
		return (0);
	}
	return (1);
}

int	parser(t_file *file, char *path)
{
	char	**raw_file;

	if (end_with_cub(path) < 1)
		return (1);
	ft_bzero(file, sizeof(t_file));
	raw_file = file_cub_read(path);
	if (!raw_file)
		return (1);
	if (fill_file_struct_scenary(raw_file, file) == 1)
		return (1);
	file->raw_data = raw_file;
	file->map = parse_map(&raw_file[6]);
	if (!file->map || parser_img_png(file) == 0
		|| set_sprites_struct(file) == 1)
	{
		free_file_struct(file);
		return (1);
	}
	set_player_pos(file);
	return (0);
}
