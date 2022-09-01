/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:52:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/01 16:02:15 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42/MLX42.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define TEXWIDTH 64
#define TEXHEIGHT 64
#define MAPWIDTH 24
#define MAPHEIGHT 24

// place the example code below here:

extern int worldMap[MAPWIDTH][MAPHEIGHT];
extern int texture[5][TEXWIDTH * TEXHEIGHT];
extern mlx_texture_t* textures[8];

typedef struct s_vars {
    mlx_t* mlx;
    mlx_image_t* img;
    double posX; // Camera pos X
    double posY; // Camera pos Y
    double dirX; // Camera dir X
    double dirY; // Camera dir Y
    double planeX;
    double planeY;
} t_vars;

void clean_img(mlx_image_t* img);
void render(t_vars* vars);

#endif
