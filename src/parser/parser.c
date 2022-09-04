/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:49:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 19:07:39 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ft_putendl_fd("Error, img is not .png file", 2);
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
	if (!file->map || parser_img_png(file) == 0)
	{
		free_file_struct(file);
		return (1);
	}
	set_player_pos(file);
	return (0);
}
