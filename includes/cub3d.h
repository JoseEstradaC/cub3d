/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:52:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 14:36:51 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# define NUMSPRITES 3

typedef struct s_vars {
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_vars;

typedef struct s_sprite {
	double	x;
	double	y;
	int		texture;
}			t_sprite;

extern int				g_world_map[MAPWIDTH][MAPHEIGHT];
extern mlx_texture_t	*g_textures[8];
extern t_sprite			g_sprites[NUMSPRITES];
extern double			g_zbuffer[SCREENWIDTH];

void					clean_img(mlx_image_t *img);
void					render(t_vars *vars);
void					hook(void *param);

void					ft_qsort(void *array, unsigned int nitems,
							unsigned int size, int (*cmp)(void*, void*));
void					ft_qsort_dbl(double *array, unsigned int nitems);

#endif
