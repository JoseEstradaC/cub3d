/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:52:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/08/31 10:45:54 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080
# define MAPWIDTH 24
# define MAPHEIGHT 24

typedef struct s_vars
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	double posX; // Camera pos X
	double posY; // Camera pos Y
	double dirX; // Camera dir X
	double dirY; // Camera dir Y
	double		planeX;
	double		planeY;
}				t_vars;

#endif
