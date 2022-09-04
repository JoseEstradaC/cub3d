/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:48:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 19:09:01 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	end_with_png(char *str)
{
	int		str_len;
	int		index;
	char	png[5];
	int		x;

	png[0] = '.';
	png[1] = 'p';
	png[2] = 'n';
	png[3] = 'g';
	png[4] = '\0';
	str_len = ft_strlen(str);
	index = str_len - 4;
	x = 0;
	while (index != str_len)
	{
		if (str[index] == png[x])
		{
			x++;
			index++;
		}
		else
			return (0);
	}
	return (1);
}

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
