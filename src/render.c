/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:50 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/02 13:13:09 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_pos
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
}			t_pos;

typedef struct s_dir
{
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	perp_wall_dist;
}			t_dir;

typedef struct s_render_vars
{
	t_pos	pos;
	t_dir	dir;
}			t_render_vars;

typedef struct s_vline
{
	int		draw_start;
	int		draw_end;
	int		color;
	int		box;
	int		line_height;
	int		tex_width;
	int		tex_height;
	int		tex_x;
	int		tex_y;
}			t_vline;

t_pos	calc_pos(t_vars *vars, int x);
int		get_side(int side, int step_x, int step_y);

// Calculate step and initial sideDist
t_dir	calc_dir(t_vars *vars, t_pos *pos)
{
	t_dir	dir;

	if (pos->ray_dir_x < 0)
	{
		dir.step_x = -1;
		dir.side_dist_x = (vars->pos_x - pos->map_x) * pos->delta_dist_x;
	}
	else
	{
		dir.step_x = 1;
		dir.side_dist_x = (pos->map_x + 1.0 - vars->pos_x) * pos->delta_dist_x;
	}
	if (pos->ray_dir_y < 0)
	{
		dir.step_y = -1;
		dir.side_dist_y = (vars->pos_y - pos->map_y) * pos->delta_dist_y;
	}
	else
	{
		dir.step_y = 1;
		dir.side_dist_y = (pos->map_y + 1.0 - vars->pos_y) * pos->delta_dist_y;
	}
	return (dir);
}

// return line height
int	perform_dda(t_pos *pos, t_dir *dir)
{
	while (g_world_map[pos->map_x][pos->map_y] <= 0)
	{
		if (dir->side_dist_x < dir->side_dist_y)
		{
			dir->side_dist_x += pos->delta_dist_x;
			pos->map_x += dir->step_x;
			dir->side = 0;
		}
		else
		{
			dir->side_dist_y += pos->delta_dist_y;
			pos->map_y += dir->step_y;
			dir->side = 1;
		}
	}
	if (dir->side == 0)
		dir->perp_wall_dist = dir->side_dist_x - pos->delta_dist_x;
	else
		dir->perp_wall_dist = dir->side_dist_y - pos->delta_dist_y;
	return ((int)(SCREENHEIGHT / dir->perp_wall_dist));
}

t_vline	calc_vline(int line_height, t_pos *pos, t_dir *dir, t_vars *vars)
{
	t_vline	vline;
	double	wall_x;

	vline.draw_start = -line_height / 2 + SCREENHEIGHT / 2;
	if (vline.draw_start < 0)
		vline.draw_start = 0;
	vline.draw_end = line_height / 2 + SCREENHEIGHT / 2;
	if (vline.draw_end >= SCREENHEIGHT)
		vline.draw_end = SCREENHEIGHT;
	vline.box = get_side(dir->side, pos->map_x - vars->pos_x,
			pos->map_y - vars->pos_y);
	vline.tex_width = g_textures[vline.box]->width;
	vline.tex_height = g_textures[vline.box]->height;
	if (dir->side == 0)
		wall_x = vars->pos_y + dir->perp_wall_dist * pos->ray_dir_y;
	else
		wall_x = vars->pos_x + dir->perp_wall_dist * pos->ray_dir_x;
	wall_x -= (int)wall_x;
	vline.tex_x = (int)(wall_x * (double)vline.tex_width);
	if (dir->side == 0 && pos->ray_dir_x > 0)
		vline.tex_x = vline.tex_width - vline.tex_x - 1;
	if (dir->side == 1 && pos->ray_dir_y < 0)
		vline.tex_x = vline.tex_width - vline.tex_x - 1;
	vline.line_height = line_height;
	return (vline);
}

void	print_line(t_vars *vars, int x, t_dir *dir, t_vline *vline)
{
	double	step;
	double	tex_pos;
	int		y;
	uint8_t	*pix;

	step = 1.0 * vline->tex_height / vline->line_height;
	tex_pos = (vline->draw_start - SCREENHEIGHT / 2 + vline->line_height / 2)
		* step;
	y = vline->draw_start;
	while (y < vline->draw_end)
	{
		vline->tex_y = (int)tex_pos & (vline->tex_height - 1);
		tex_pos += step;
		pix = &g_textures[vline->box]->pixels[vline->tex_height
			* vline->tex_y * 4 + vline->tex_x * 4];
		vline->color = (pix[0] << 24) | (pix[1] << 16) | (pix[2] << 8) | pix[3];
		if (dir->side == 1)
			vline->color = (vline->color >> 1) & 0x7f7f7fff;
		mlx_put_pixel(vars->img, x, y, vline->color);
		y++;
	}
}

void	render(t_vars *vars)
{
	t_render_vars	r_vars;
	int				x;
	t_vline			vline;

	clean_img(vars->img);
	x = 0;
	while (x < SCREENWIDTH)
	{
		r_vars.pos = calc_pos(vars, x);
		r_vars.dir = calc_dir(vars, &r_vars.pos);
		vline = calc_vline(perform_dda(&r_vars.pos, &r_vars.dir),
				&r_vars.pos, &r_vars.dir, vars);
		print_line(vars, x, &r_vars.dir, &vline);
		x++;
	}
}
