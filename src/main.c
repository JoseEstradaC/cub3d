/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:01:57 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/01 17:04:14 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				texture[5][TEXWIDTH * TEXHEIGHT];
mlx_texture_t	*textures[8];

int worldMap[MAPWIDTH][MAPHEIGHT] =
	{
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7,
			7},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,
			7},
		{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			7},
		{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			7},
		{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,
			7},
		{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7,
			7},
		{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7,
			1},
		{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0,
			8},
		{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7,
			1},
		{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0,
			8},
		{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7,
			1},
		{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7,
			1},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			6},
		{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			4},
		{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			6},
		{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3,
			3},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0,
			2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0,
			2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2,
			2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0,
			2},
		{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2,
			2},
		{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0,
			2},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0,
			2},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
			3}};

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
	int					cursor_x;
	int					cursor_y;
	int					is_w_or_s;

	moveSpeed = 0.04;
	rotSpeed = 0.025;
	is_w_or_s = 0;
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
		is_w_or_s = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		if (worldMap[(int)(vars->posX - vars->dirX
				* moveSpeed)][(int)vars->posY] == false)
			vars->posX -= vars->dirX * moveSpeed;
		if (worldMap[(int)vars->posX][(int)(vars->posY - vars->dirY
				* moveSpeed)] == false)
			vars->posY -= vars->dirY * moveSpeed;
		is_w_or_s = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		if (is_w_or_s)
			moveSpeed /= 2;
		if (worldMap[(int)(vars->posX - vars->dirY
				* moveSpeed)][(int)vars->posY] == false)
			vars->posX -= vars->dirY * moveSpeed;
		if (worldMap[(int)vars->posX][(int)(vars->posY + vars->dirX
				* moveSpeed)] == false)
			vars->posY += vars->dirX * moveSpeed;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		if (is_w_or_s)
			moveSpeed /= 2;
		if (worldMap[(int)(vars->posX + vars->dirY
				* moveSpeed)][(int)vars->posY] == false)
			vars->posX += vars->dirY * moveSpeed;
		if (worldMap[(int)vars->posX][(int)(vars->posY - vars->dirX
				* moveSpeed)] == false)
			vars->posY -= vars->dirX * moveSpeed;
	}
	mlx_get_mouse_pos(vars->mlx, &cursor_x, &cursor_y);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT) || (cursor_x > ((SCREENWIDTH
					/ 2) + 5) && cursor_x > 0 && cursor_y > 0))
	{
		if (cursor_x > ((SCREENWIDTH / 2) + 5))
			rotSpeed *= 2.5;
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
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT) || (cursor_x < ((SCREENWIDTH
					/ 2) - 5) && cursor_x > 0 && cursor_y > 0))
	{
		//both camera direction and camera plane must be rotated
		if (cursor_x < ((SCREENWIDTH / 2) - 5))
			rotSpeed *= 2.5;
		oldDirX = vars->dirX;
		vars->dirX = vars->dirX * cos(rotSpeed) - vars->dirY * sin(rotSpeed);
		vars->dirY = oldDirX * sin(rotSpeed) + vars->dirY * cos(rotSpeed);
		oldPlaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(rotSpeed) - vars->planeY
			* sin(rotSpeed);
		vars->planeY = oldPlaneX * sin(rotSpeed) + vars->planeY * cos(rotSpeed);
	}
	mlx_set_mouse_pos(vars->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	render(param);
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vars		vars;

	// ------
	textures[0] = mlx_load_png("pics/redbrick.png");
	textures[1] = mlx_load_png("pics/bluestone.png");
	textures[2] = mlx_load_png("pics/colorstone.png");
	textures[3] = mlx_load_png("pics/eagle.png");
	textures[4] = mlx_load_png("pics/wood.png");
	textures[5] = mlx_load_png("pics/greystone.png");
	textures[6] = mlx_load_png("pics/purplestone.png");
	textures[7] = mlx_load_png("pics/purplestone.png");
	// -----
	mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Raycaster", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT);
	vars.mlx = mlx;
	vars.img = img;
	vars.posX = 1.5;
	vars.posY = 1.5;
	/* Para fov a 90, para calcular estos valores
	(2 * Math.atan(1.0/1) * 180.0 / Math.PI) <-- JS*/
	vars.dirX = -1;
	vars.dirY = 0;
	vars.planeX = 0;
	vars.planeY = 0.66;
	render(&vars);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(mlx, &hook, &vars);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
