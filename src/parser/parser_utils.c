/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:42:24 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 18:10:40 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_file_struct(t_file *file)
{
	free(file->no);
	free(file->so);
	free(file->we);
	free(file->ea);
	free(file->f);
	free(file->c);
	ft_split_free(file->raw_data);
	return (0);
}
