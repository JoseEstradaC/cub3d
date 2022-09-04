/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:49:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 17:16:32 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	file->map = parse_map(&raw_file[6]);
	ft_split_free(raw_file);
	if (!file->map)
		return (1);
	return (0);
}
