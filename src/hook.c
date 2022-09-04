/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:44:27 by jarredon          #+#    #+#             */
/*   Updated: 2022/09/04 18:28:20 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_mov
{
	double	move_speed;
	double	rot_speed;
	int		cursor_x;
	int		cursor_y;
	int		is_w_or_s;
}			t_mov;

static void	print_frames(t_vars *vars)
{
	static int			frame_count;
	static int			old_time;
	static mlx_image_t	*old_img_text;
	char				*str_fps;

	if (mlx_get_time() != old_time)
	{
		ft_putstr_fd("Frame: ", 1);
		ft_putnbr_fd(frame_count, 1);
		ft_putstr_fd("\n", 1);
		old_time = mlx_get_time();
		if (old_img_text != NULL)
			mlx_delete_image(vars->mlx, old_img_text);
		str_fps = ft_itoa(frame_count);
		old_img_text = mlx_put_string(vars->mlx, str_fps, 0, 0);
		free(str_fps);
		frame_count = 0;
	}
	frame_count++;
}

static void	check_w_s(t_vars *vars, t_mov *mov)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		if (vars->file.map[(int)(vars->pos_x + vars->dir_x
				* mov->move_speed)][(int)vars->pos_y] == '0')
			vars->pos_x += vars->dir_x * mov->move_speed;
		if (vars->file.map[(int)vars->pos_x][(int)(vars->pos_y + vars->dir_y
			* mov->move_speed)] == '0')
			vars->pos_y += vars->dir_y * mov->move_speed;
		mov->is_w_or_s = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		if (vars->file.map[(int)(vars->pos_x - vars->dir_x
				* mov->move_speed)][(int)vars->pos_y] == '0')
			vars->pos_x -= vars->dir_x * mov->move_speed;
		if (vars->file.map[(int)vars->pos_x][(int)(vars->pos_y - vars->dir_y
			* mov->move_speed)] == '0')
			vars->pos_y -= vars->dir_y * mov->move_speed;
		mov->is_w_or_s = 1;
	}
}

static void	check_a_d(t_vars *vars, t_mov *mov)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		if (mov->is_w_or_s)
			mov->move_speed /= 2;
		if (vars->file.map[(int)(vars->pos_x - vars->dir_y
				* mov->move_speed)][(int)vars->pos_y] == '0')
			vars->pos_x -= vars->dir_y * mov->move_speed;
		if (vars->file.map[(int)vars->pos_x][(int)(vars->pos_y + vars->dir_x
			* mov->move_speed)] == '0')
			vars->pos_y += vars->dir_x * mov->move_speed;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		if (mov->is_w_or_s)
			mov->move_speed /= 2;
		if (vars->file.map[(int)(vars->pos_x + vars->dir_y
				* mov->move_speed)][(int)vars->pos_y] == '0')
			vars->pos_x += vars->dir_y * mov->move_speed;
		if (vars->file.map[(int)vars->pos_x][(int)(vars->pos_y - vars->dir_x
			* mov->move_speed)] == '0')
			vars->pos_y -= vars->dir_x * mov->move_speed;
	}
}

// if 'right', rotate the camera to the right, else left
static void	rotate(t_vars *vars, t_mov *mov, int right)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	if (right)
		rot_speed = -mov->rot_speed;
	else
		rot_speed = mov->rot_speed;
	if (mov->cursor_x > ((SCREENWIDTH / 2) + 5) || mov->cursor_x < ((SCREENWIDTH
				/ 2) + 5))
		rot_speed *= 2;
	old_dir_x = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(rot_speed) - vars->dir_y * sin(rot_speed);
	vars->dir_y = old_dir_x * sin(rot_speed) + vars->dir_y * cos(rot_speed);
	old_plane_x = vars->plane_x;
	vars->plane_x = vars->plane_x * cos(rot_speed) - vars->plane_y
		* sin(rot_speed);
	vars->plane_y = old_plane_x * sin(rot_speed) + vars->plane_y
		* cos(rot_speed);
}

void	hook(void *param)
{
	t_vars	*vars;
	t_mov	mov;

	mov.move_speed = 0.04;
	mov.rot_speed = 0.025;
	mov.is_w_or_s = 0;
	vars = param;
	print_frames(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	check_w_s(vars, &mov);
	check_a_d(vars, &mov);
	mlx_get_mouse_pos(vars->mlx, &mov.cursor_x, &mov.cursor_y);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT)
		|| (mov.cursor_x > ((SCREENWIDTH / 2) + 5) && mov.cursor_x > 0
			&& mov.cursor_y > 0))
		rotate(vars, &mov, 1);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT)
		|| (mov.cursor_x < ((SCREENWIDTH / 2) - 5) && mov.cursor_x > 0
			&& mov.cursor_y > 0))
		rotate(vars, &mov, 0);
	mlx_set_mouse_pos(vars->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	render(vars);
}
