/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:48:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 16:48:34 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	join_line(char *line, char ***array)
{
	static int	limit_new_lines;

	if (!line)
		return (-1);
	if (isspace_str(line) && limit_new_lines >= 7)
	{
		if (!join_split(array, line))
		{
			ft_putendl_fd("Error", 2);
			return (1);
		}
	}
	else if (!isspace_str(line))
	{
		limit_new_lines++;
		if (!join_split(array, line))
		{
			ft_putendl_fd("Error", 2);
			return (1);
		}
	}
	else
		free(line);
	return (0);
}
