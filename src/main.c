/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:01:57 by jestrada          #+#    #+#             */
/*   Updated: 2022/08/31 12:51:04 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//place the example code below here:

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

void	render(t_vars *vars)
{
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	double	cameraX;

	/*memset(vars->img->pixels, 0, vars->img->width * vars->img->height
			* sizeof(uint8_t));*/
	for (int x = 0; x < SCREENWIDTH; x++)
		for (int y = 0; y < SCREENHEIGHT; y++)
			mlx_put_pixel(vars->img, x, y, 0);
	for (int x = 0; x < SCREENWIDTH; x++)
	{
		//calculate ray position and direction
		cameraX = 2 * x / (double)SCREENWIDTH - 1;
		//x-coordinate in camera space
		rayDirX = vars->dirX + vars->planeX * cameraX;
		rayDirY = vars->dirY + vars->planeY * cameraX;
		//which box of the map we're in
		mapX = (int)vars->posX;
		mapY = (int)vars->posY;
		//length of ray from current position to next x or y-side
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		//what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; //was there a wall hit?
		int side;    //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (vars->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - vars->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (vars->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - vars->posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		lineHeight = (int)(SCREENHEIGHT / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
		if (drawEnd >= SCREENHEIGHT)
			drawEnd = SCREENHEIGHT - 1;
		switch (worldMap[mapX][mapY])
		{
		case 1:
			color = 0xFF0000FF;
			break ; //red
		case 2:
			color = 0x00FF00FF;
			break ; //green
		case 3:
			color = 0x0000FFFF;
			break ; //blue
		case 4:
			color = 0xFFFFFFFF;
			break ; //white
		default:
			color = 0xFFFF00FF;
			break ; //yellow
		}
		//give x and y sides different brightness
		if (side == 1)
		{
			color = color - 88;
		}
		//draw the pixels of the stripe as a vertical line
		for (int y = drawStart; y < drawEnd; y++)
			mlx_put_pixel(vars->img, x, y, color);
	}
}

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
	/*printf("---> %f -- %f \n", vars->dirX, vars->dirY);
	printf("---> %f -- %f \n", vars->posX, vars->posY);
	printf("---> %f -- %f \n", vars->planeX, vars->planeY);*/
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
