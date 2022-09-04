/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:50 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/04 17:56:59 by jestrada         ###   ########.fr       */
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

void	sort_sprites(int *sprite_order, double *sprite_distance, int amount)
{
	double	old_distances[amount];
	int		i;
	int		j;

	ft_memcpy(old_distances, sprite_distance, amount * sizeof(double));
	ft_qsort_dbl(sprite_distance, amount);
	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount)
		{
			if (sprite_distance[i] == old_distances[j])
			{
				sprite_order[amount - i - 1] = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

t_pos		calc_pos(t_vars *vars, int x);
int			get_side(int side, int step_x, int step_y);

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
int	perform_dda(t_pos *pos, t_dir *dir, t_vars *vars)
{
	while (vars->file.map[pos->map_x][pos->map_y] == '0')
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

void	print_line(t_vars *vars, int x, t_vline *vline)
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

	clean_img(vars->img);
	x = 0;
	while (x < SCREENWIDTH)
	{
		r_vars.pos = calc_pos(vars, x);
		r_vars.dir = calc_dir(vars, &r_vars.pos);
		vline = calc_vline(perform_dda(&r_vars.pos, &r_vars.dir, vars),
				&r_vars.pos, &r_vars.dir, vars);
		print_line(vars, x, &vline);
		g_zbuffer[x] = r_vars.dir.perp_wall_dist;
		x++;
	}
	int sprite_order[NUMSPRITES];
	double sprite_distance[NUMSPRITES];
	for (int i = 0; i < NUMSPRITES; i++) {
		sprite_distance[i] = ((vars->pos_x - g_sprites[i].x) * (vars->pos_x - g_sprites[i].x) + (vars->pos_x - g_sprites[i].x) * (vars->pos_x - g_sprites[i].x));
	}
	sort_sprites(sprite_order, sprite_distance, NUMSPRITES);
	for (int i = 0; i < NUMSPRITES; i++)
	{
		double	sprite_x = g_sprites[sprite_order[i]].x - vars->pos_x;
		double	sprite_y = g_sprites[sprite_order[i]].y - vars->pos_y;
		double	inv_det = 1.0 / (vars->plane_x * vars->dir_y - vars->plane_y * vars->dir_x);
		double	transform_x = inv_det * (vars->dir_y * sprite_x - vars->dir_x * sprite_y);
		double	transform_y = inv_det * (-vars->plane_y * sprite_x + vars->plane_x * sprite_y);
		int	sprite_screenx = (int)((SCREENWIDTH / 2) * (1 + transform_x / transform_y));

		int	sprite_height = abs((int)(SCREENHEIGHT / transform_y));
		int	drawstart_y = -sprite_height / 2 + SCREENHEIGHT / 2;
		if (drawstart_y < 0) drawstart_y = 0;
		int	drawend_y = sprite_height / 2 + SCREENHEIGHT / 2;
		if (drawend_y >= SCREENHEIGHT) drawend_y = SCREENHEIGHT - 1;

		int sprite_width = abs((int)(SCREENHEIGHT / transform_y));
		int	drawstart_x = -sprite_width / 2 + sprite_screenx;
		if (drawstart_x < 0) drawstart_x = 0;
		int	drawend_x = sprite_width / 2 + sprite_screenx;
		if (drawend_x > SCREENWIDTH) drawend_x = SCREENWIDTH;

		for (int stripe = drawstart_x; stripe < drawend_x; stripe++)
		{
			int	tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screenx)) * vline.tex_width / sprite_width) / 256;
			if (transform_y > 0 && transform_y < g_zbuffer[stripe])
			{
				for (int y = drawstart_y; y < drawend_y; y++)
				{
					int d = y * 256 - SCREENHEIGHT * 128 + sprite_height * 128;
					int	tex_y = ((d * vline.tex_height) / sprite_height) / 256;
					uint8_t	*pix;
					pix = &g_textures[g_sprites[sprite_order[i]].texture]->pixels[vline.tex_width * tex_y * 4 + tex_x * 4];
					int	color = (pix[0] << 24) | (pix[1] << 16) | (pix[2] << 8) | pix[3];
					if ((color & 0xFFFFFF00) != 0)
						mlx_put_pixel(vars->img, stripe, y, color);
				}
			}
		}
	}
}
