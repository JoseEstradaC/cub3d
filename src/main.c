/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:01:57 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 17:35:39 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double			g_zbuffer[SCREENWIDTH];

mlx_texture_t	*g_textures[NTEXTURES];

void	load_textures(t_file *file)
{
	int	i;

	g_textures[0] = mlx_load_png(file->no);
	g_textures[1] = mlx_load_png(file->so);
	g_textures[2] = mlx_load_png(file->we);
	g_textures[3] = mlx_load_png(file->ea);
	g_textures[4] = mlx_load_png("pics/barrel.png");
	g_textures[5] = mlx_load_png("pics/pillar.png");
	g_textures[6] = mlx_load_png("pics/maggie.png");
	g_textures[7] = mlx_load_png("pics/maggie2.png");
	i = 0;
	while (i < NTEXTURES)
	{
		if (g_textures[i++] == NULL)
		{
			ft_putendl_fd("Error\nloading textures", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	load_vars(t_vars *vars, char direction)
{
	vars->pos_x = vars->file.player_y + 0.5;
	vars->pos_y = vars->file.player_x + 0.5;
	vars->dir_x = -1;
	vars->dir_y = 0;
	vars->plane_x = 0;
	vars->plane_y = 0.66;
	vars->pause = 0;
	if (direction == 'S')
	{
		vars->dir_x = 1;
		vars->plane_y = -0.66;
	}
	if (direction == 'E' || direction == 'W')
	{
		vars->dir_x = 0;
		vars->dir_y = 1;
		vars->plane_x = 0.66;
		vars->plane_y = 0;
	}
	if (direction == 'W')
	{
		vars->dir_y = -1;
		vars->plane_x = -0.66;
	}
}

void	mlx_load(t_vars *vars)
{
	render(vars);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
	mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(vars->mlx, &hook, vars);
	mlx_loop(vars->mlx);
	free_textures();
	mlx_terminate(vars->mlx);
	free_file_struct(&vars->file);
	system("leaks -q cub3d");
}

void	mlx_init_vars(t_vars *vars)
{
	vars->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Raycaster", false);
	if (!vars->mlx)
	{
		free_textures();
		free_file_struct(&vars->file);
		exit(EXIT_FAILURE);
	}
	vars->img = mlx_new_image(vars->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!vars->img)
	{
		free_textures();
		free_file_struct(&vars->file);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	(void)argc;
	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage ./cub3d name_of_file.cub", 2);
		return (1);
	}
	if (parser(&vars.file, argv[1]) == 1)
	{
		system("leaks -q cub3d");
		return (1);
	}
	mlx_init_vars(&vars);
	load_vars(&vars, vars.file.map[vars.file.player_y][vars.file.player_x]);
	vars.file.map[vars.file.player_y][vars.file.player_x] = '0';
	load_textures(&vars.file);
	mlx_load(&vars);
	return (0);
}
