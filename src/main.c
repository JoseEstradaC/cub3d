/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:01:57 by jestrada          #+#    #+#             */
/*   Updated: 2022/08/31 20:18:08 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture[5][TEXWIDTH * TEXHEIGHT];
int worldMap[MAPWIDTH][MAPHEIGHT] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 2, 2, 1, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1}};

void	hook(void *param)
{
	t_vars				*vars;
	double				moveSpeed;
	double				rotSpeed;
	double				oldDirX;
	double				oldPlaneX;
	static int			frameCount;
	static int			oldTime;
	static mlx_image_t	*old_img_text;
	char				*strFPS;

	moveSpeed = 0.04;
	rotSpeed = 0.025;
	vars = param;
	if (mlx_get_time() != oldTime)
	{
		ft_putstr_fd("Frame: ", 1);
		ft_putnbr_fd(frameCount, 1);
		ft_putstr_fd("\n", 1);
		oldTime = mlx_get_time();
		if (old_img_text != NULL)
			mlx_delete_image(vars->mlx, old_img_text);
		strFPS = ft_itoa(frameCount);
		old_img_text = mlx_put_string(vars->mlx, strFPS, 0, 0);
		free(strFPS);
		frameCount = 0;
	}
	frameCount++;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		if (worldMap[(int)(vars->posX + vars->dirX
				* moveSpeed)][(int)vars->posY] == false)
			vars->posX += vars->dirX * moveSpeed;
		if (worldMap[(int)vars->posX][(int)(vars->posY + vars->dirY
				* moveSpeed)] == false)
			vars->posY += vars->dirY * moveSpeed;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		if (worldMap[(int)(vars->posX - vars->dirX
				* moveSpeed)][(int)vars->posY] == false)
			vars->posX -= vars->dirX * moveSpeed;
		if (worldMap[(int)vars->posX][(int)(vars->posY - vars->dirY
				* moveSpeed)] == false)
			vars->posY -= vars->dirY * moveSpeed;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		//both camera direction and camera plane must be rotated
		oldDirX = vars->dirX;
		vars->dirX = vars->dirX * cos(-rotSpeed) - vars->dirY * sin(-rotSpeed);
		vars->dirY = oldDirX * sin(-rotSpeed) + vars->dirY * cos(-rotSpeed);
		oldPlaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(-rotSpeed) - vars->planeY
			* sin(-rotSpeed);
		vars->planeY = oldPlaneX * sin(-rotSpeed) + vars->planeY
			* cos(-rotSpeed);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		//both camera direction and camera plane must be rotated
		oldDirX = vars->dirX;
		vars->dirX = vars->dirX * cos(rotSpeed) - vars->dirY * sin(rotSpeed);
		vars->dirY = oldDirX * sin(rotSpeed) + vars->dirY * cos(rotSpeed);
		oldPlaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(rotSpeed) - vars->planeY
			* sin(rotSpeed);
		vars->planeY = oldPlaneX * sin(rotSpeed) + vars->planeY * cos(rotSpeed);
	}
	render(param);
}

int	main(void)
{
	// ---- texturas de prueba
	for (int x = 0; x < TEXWIDTH; x++) {
		for (int y = 0; y < TEXHEIGHT; y++) {
			int xorcolor = (x * 256 / TEXWIDTH) ^ (y * 256 / TEXHEIGHT);
			//int xcolor = x * 256 / TEXWIDTH;
			/*int ycolor = y * 256 / TEXHEIGHT;*/
			int xycolor = y * 128 / TEXHEIGHT + x * 128 / TEXWIDTH;
			texture[0][TEXWIDTH * y + x] = 65536 * 254 * (x != y && x != TEXWIDTH - y); //flat red texture with black cross
			texture[1][TEXWIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][TEXWIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][TEXWIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][TEXWIDTH * y + x] = 256 * xorcolor; //xor green
			// Poner colores para la maravillosa MLX42
			texture[0][TEXWIDTH * y + x] = (texture[0][TEXWIDTH * y + x] << 8) + 0xFF;
			texture[1][TEXWIDTH * y + x] = (texture[1][TEXWIDTH * y + x] << 8) + 0xFF;
			texture[2][TEXWIDTH * y + x] = (texture[2][TEXWIDTH * y + x] << 8) + 0xFF;
			texture[3][TEXWIDTH * y + x] = (texture[3][TEXWIDTH * y + x] << 8) + 0xFF;
			texture[4][TEXWIDTH * y + x] = (texture[4][TEXWIDTH * y + x] << 8) + 0xFF;
		}
	}
	// ------

	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vars		vars;

	mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Raycaster", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT);
	vars.mlx = mlx;
	vars.img = img;
	vars.posX = 22;
	vars.posY = 12;
	/* Para fov a 90, para calcular estos valores
	(2 * Math.atan(1.0/1) * 180.0 / Math.PI) <-- JS*/
	vars.dirX = -1;
	vars.dirY = 0;
	vars.planeX = 0;
	vars.planeY = 1;
	render(&vars);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, &hook, &vars);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
