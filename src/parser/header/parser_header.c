/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:47:29 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 18:10:39 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**file_cub_read(char *path)
{
	int		fd;
	int		read_status;
	char	**raw_file;

	raw_file = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error\n.cub file can't be found", 2);
		return (NULL);
	}
	while (true)
	{
		read_status = join_line(get_next_line(fd), &raw_file);
		if (read_status == -1)
			break ;
		if (read_status == 1)
		{
			ft_split_free(raw_file);
			close(fd);
			return (NULL);
		}
	}
	close(fd);
	return (raw_file);
}

int	path_insert(char **path, t_file *file)
{
	if (ft_split_count(path) != 2)
		return (1);
	if (ft_strncmp(path[0], "NO", 2) == 0 && !file->no)
		file->no = path[1];
	else if (ft_strncmp(path[0], "SO", 2) == 0 && !file->so)
		file->so = path[1];
	else if (ft_strncmp(path[0], "WE", 2) == 0 && !file->we)
		file->we = path[1];
	else if (ft_strncmp(path[0], "EA", 2) == 0 && !file->ea)
		file->ea = path[1];
	else if (ft_strncmp(path[0], "F", 1) == 0 && !file->f)
		file->f = path[1];
	else if (ft_strncmp(path[0], "C", 1) == 0 && !file->c)
		file->c = path[1];
	else
		return (1);
	free(path[0]);
	free(path);
	return (0);
}

int	path_delete_new_line(t_file *file)
{
	if (delete_new_line(&file->no) == 1)
		return (1);
	if (delete_new_line(&file->so) == 1)
		return (1);
	if (delete_new_line(&file->we) == 1)
		return (1);
	if (delete_new_line(&file->ea) == 1)
		return (1);
	if (delete_new_line(&file->f) == 1)
		return (1);
	if (delete_new_line(&file->c) == 1)
		return (1);
	return (0);
}

int	fill_file_struct_scenary_1(char **raw_file, t_file *file, int index)
{
	if (ft_split_count(raw_file) < 9
		|| is_valid_char_map_line(raw_file[index]) == 0)
	{
		free_file_struct(file);
		ft_split_free(raw_file);
		ft_putendl_fd("Error\n.cub it not correct formated", 2);
		return (1);
	}
	if (path_delete_new_line(file) == 1 || parser_rgb(file, 'c') == -1
		|| parser_rgb(file, 'f') == -1)
	{
		ft_split_free(raw_file);
		free_file_struct(file);
		return (1);
	}
	return (0);
}

int	fill_file_struct_scenary(char **raw_file, t_file *file)
{
	int		index;
	char	*line;
	char	**tmp;

	index = 0;
	while (index != 6)
	{
		line = raw_file[index];
		tmp = ft_split(line, ' ');
		if (!tmp)
		{
			ft_split_free(raw_file);
			return (1);
		}
		if (path_insert(tmp, file) == 1)
		{
			ft_putendl_fd("Error\n.cub it not correct formated", 2);
			free_file_struct(file);
			ft_split_free(raw_file);
			ft_split_free(tmp);
			return (1);
		}
		index++;
	}
	return (fill_file_struct_scenary_1(raw_file, file, index));
}
