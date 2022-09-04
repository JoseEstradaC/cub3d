/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:52:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 19:50:26 by jestrada         ###   ########.fr       */
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

# define NUMSPRITES 3

typedef struct s_file
{
	char				**map;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*f;
	char				*c;
	char				**raw_data;
	int					f_int;
	int					c_int;
	int					player_x;
	int					player_y;

}						t_file;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;

}						t_rgb;

typedef struct s_vars
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	int					pause;
	t_file				file;
}						t_vars;

typedef struct s_sprite
{
	double				x;
	double				y;
	int					texture;
}						t_sprite;

extern mlx_texture_t	*g_textures[8];
extern t_sprite			g_sprites[NUMSPRITES];
extern double			g_zbuffer[SCREENWIDTH];

void					clean_img(mlx_image_t *img);
void					render(t_vars *vars);
void					hook(void *param);

void					ft_qsort(void *array, unsigned int nitems,
							unsigned int size, int (*cmp)(void *, void *));
void					ft_qsort_dbl(double *array, unsigned int nitems);

char					**join_split(char ***a, char *b);
void					change_space_with_x(char **map);
int						is_player(char c);
int						is_zero_or_player(char c);
int						is_zero_or_one_or_player(char c);
int						is_terrain(char c);
int						end_with_cub(const char *path);
int						parser(t_file *file, char *path);
char					**parse_map(char **map);
int						is_valid_map_content(char **map);
int						border_check(char **map);
int						surround_check(char **map);
int						isspace_str(char *str);
int						delete_new_line(char **str);
int						is_valid_char_map_line(char *line);
int						parser_rgb(t_file *file, char type);
int						free_file_struct(t_file *file);
int						join_line(char *line, char ***array);
char					**file_cub_read(char *path);
int						fill_file_struct_scenary(char **raw_file, t_file *file);
int						end_with_png(char *str);
void					check_paused(t_vars *vars);

#endif
