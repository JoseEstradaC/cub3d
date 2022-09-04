/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:01:57 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 17:22:58 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define NUMSPRITES 3

t_sprite		g_sprites[NUMSPRITES] = {
	{3.5, 5.5, 5},
	{2.5, 12.5, 7},
	{7.5, 5.5, 6},
};
double			g_zbuffer[SCREENWIDTH];

mlx_texture_t	*g_textures[8];

int				g_world_map[MAPWIDTH][MAPHEIGHT] = {
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
	{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
	{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
	{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
	{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
	{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
	{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
	{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
	{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
	{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

void	load_textures(void)
{
	int	i;

	g_textures[0] = mlx_load_png("pics/face.png");
	g_textures[1] = mlx_load_png("pics/bluestone.png");
	g_textures[2] = mlx_load_png("pics/colorstone.png");
	g_textures[3] = mlx_load_png("pics/2.png");
	g_textures[4] = mlx_load_png("pics/wood.png");
	g_textures[5] = mlx_load_png("pics/barrel.png");
	g_textures[6] = mlx_load_png("pics/pillar.png");
	g_textures[7] = mlx_load_png("pics/greenlight.png");
	i = 0;
	while (i < 8)
	{
		if (g_textures[i++] == NULL)
		{
			ft_putstr_fd("Error loading textures\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

// TODO numero de textures
void	free_textures(void)
{
	int	i;

	i = 0;
	while (i < 8)
		mlx_delete_texture(g_textures[i++]);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vars		vars;
	t_file		file;

	(void)argc;
	if (parser(&file, argv[1]) == 1)
	{
		system("leaks -q cub3d");
		return (1);
	}
	free_file_struct(&file);
	system("leaks -q cub3d");
	load_textures();
	mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Raycaster", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT);
	vars.mlx = mlx;
	vars.img = img;
	vars.pos_x = 1.5;
	vars.pos_y = 1.5;
	vars.dir_x = -1;
	vars.dir_y = 0;
	vars.plane_x = 0;
	vars.plane_y = 0.66;
	render(&vars);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(mlx, &hook, &vars);
	mlx_loop(mlx);
	free_textures();
	mlx_terminate(mlx);
}
