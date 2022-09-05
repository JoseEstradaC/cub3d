/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:01:57 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 14:12:54 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite		g_sprites[NUMSPRITES] = {
	{3.5, 5.5, 4},
	{2.5, 5.5, 6},
	{4.5, 5.5, 5},
};

double			g_zbuffer[SCREENWIDTH];

mlx_texture_t	*g_textures[7];

void	load_textures(t_file *file)
{
	int	i;

	g_textures[0] = mlx_load_png(file->no);
	g_textures[1] = mlx_load_png(file->so);
	g_textures[2] = mlx_load_png(file->we);
	g_textures[3] = mlx_load_png(file->ea);
	g_textures[4] = mlx_load_png("pics/barrel.png");
	g_textures[5] = mlx_load_png("pics/pillar.png");
	g_textures[6] = mlx_load_png("pics/greenlight.png");
	i = 0;
	while (i < 7)
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

void	load_vars(t_vars *vars, char direction)
{
	vars->pos_x = vars->file.player_y + 0.5;
	vars->pos_y = vars->file.player_x + 0.5;
	vars->dir_x = -1;
	vars->dir_y = 0;
	vars->plane_x = 0;
	vars->plane_y = 0.66;
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

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vars		vars;

	(void)argc;
	if (argc != 2)
	{
		ft_putendl_fd("Error, Usage ./cub3d name_of_file.cub", 2);
		return (1);
	}
	if (parser(&vars.file, argv[1]) == 1)
	{
		system("leaks -q cub3d");
		return (1);
	}
	load_vars(&vars, vars.file.map[vars.file.player_y][vars.file.player_x]);
	vars.file.map[vars.file.player_y][vars.file.player_x] = '0';
	load_textures(&vars.file);
	mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Raycaster", false);
	if (!mlx)
	{
		free_textures();
		free_file_struct(&vars.file);
		exit(EXIT_FAILURE);
	}
	img = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!img)
	{
		free_textures();
		free_file_struct(&vars.file);
		exit(EXIT_FAILURE);
	}
	vars.mlx = mlx;
	vars.img = img;
	/*vars.pos_x = 1.5;*/
	/*vars.pos_y = 1.5;*/
	/*vars.dir_x = 0;*/
	/*vars.dir_y = 0;*/
	/*vars.plane_x = 0;*/
	/*vars.plane_y = 0.66;*/
	/*vars.pause = 0;*/
	render(&vars);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(mlx, &hook, &vars);
	mlx_loop(mlx);
	free_textures();
	mlx_terminate(mlx);
	free_file_struct(&vars.file);
	system("leaks -q cub3d");
}
