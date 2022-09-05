/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:50 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/05 17:24:46 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

// Calculate step and initial sideDist
static t_dir	calc_dir(t_vars *vars, t_pos *pos)
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
static int	perform_dda(t_pos *pos, t_dir *dir, t_vars *vars)
{
	while (vars->file.map[pos->map_x][pos->map_y] != '1')
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

static t_vline	calc_vl(int line_height, t_pos *pos, t_dir *dir, t_vars *vars)
{
	t_vline	vline;
	double	wall_x;

	vline.draw_start = -line_height / 2 + SCREENHEIGHT / 2;
	if (vline.draw_start < 0)
		vline.draw_start = 0;
	vline.draw_end = line_height / 2 + SCREENHEIGHT / 2;
	if (vline.draw_end >= SCREENHEIGHT)
		vline.draw_end = SCREENHEIGHT;
	vline.box = get_side(dir->side, pos->map_x - vars->pos_x, pos->map_y
			- vars->pos_y);
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

static void	print_line(t_vars *vars, int x, t_vline *vline)
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
		vline->tex_y = (int)tex_pos;
		if (vline->tex_y > vline->tex_height)
			vline->tex_y = vline->tex_height;
		tex_pos += step;
		pix = &g_textures[vline->box]->pixels[vline->tex_width * vline->tex_y
			* 4 + vline->tex_x * 4];
		vline->color = (pix[0] << 24) | (pix[1] << 16) | (pix[2] << 8) | pix[3];
		mlx_put_pixel(vars->img, x, y, vline->color);
		y++;
	}
}

void	render(t_vars *vars)
{
	t_render_vars	r_vars;
	int				x;
	t_vline			vline;

	clean_img(vars->img, vars->file.c_int, vars->file.f_int);
	x = 0;
	while (x < SCREENWIDTH)
	{
		r_vars.pos = calc_pos(vars, x);
		r_vars.dir = calc_dir(vars, &r_vars.pos);
		vline = calc_vl(perform_dda(&r_vars.pos, &r_vars.dir, vars),
						&r_vars.pos,
						&r_vars.dir,
						vars);
		print_line(vars, x, &vline);
		g_zbuffer[x] = r_vars.dir.perp_wall_dist;
		x++;
	}
	sprites(vars);
}
