/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:45:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/03 18:38:43 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**join_split(char ***a, char *b)
{
	int		size;
	char	**ret;
	int		i;
	int		j;

	size = ft_split_count(*a) + 2;
	ret = (char **)malloc(size * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (*a && (*a)[++i])
		ret[i] = ft_strdup((*a)[i]);
	j = 0;
	if (i == -1)
		i = 0;
	ret[i++] = ft_strdup(b);
	ret[i] = NULL;
	ft_split_free((*a));
	free(b);
	*a = ret;
	return (ret);
}

void	change_space_with_x(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == ' ')
				map[y][x] = 'x';
			x++;
		}
		y++;
	}
}

/*
	OK: 1
	KO: 0
	Error: -1
*/
int	end_with_cub(const char *path)
{
	int		index;
	char	**dot_splited;
	int		last_length;

	dot_splited = ft_split(path, '.');
	if (!dot_splited)
	{
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	index = 0;
	while (dot_splited[index])
		index++;
	last_length = ft_strlen(dot_splited[index - 1]);
	if (ft_strncmp(dot_splited[index - 1], "cub", last_length))
	{
		ft_split_free(dot_splited);
		ft_putendl_fd("Map file is not end with .cub", 2);
		return (0);
	}
	ft_split_free(dot_splited);
	return (1);
}

int	isspace_str(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (!(str[index] == ' ' || str[index] == '\f' || str[index] == '\n'
				|| str[index] == '\r' || str[index] == '\t'
				|| str[index] == '\v'))
			return (0);
		index++;
	}
	return (1);
}

int	delete_new_line(char **str)
{
	char	*tmp;

	if (!(*str))
		return (0);
	if ((*str)[ft_strlen(*str) - 1] == '\n')
	{
		tmp = ft_substr(*str, 0, ft_strlen(*str) - 1);
		if (!tmp)
		{
			return (1);
			ft_putendl_fd("Error", 2);
		}
		free(*str);
		*str = tmp;
	}
	return (0);
}
