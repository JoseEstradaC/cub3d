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
}			t_dir;

typedef struct s_render_vars
{
	t_pos	pos;
	t_dir	dir;
}			t_render_vars;

typedef struct s_vline
{
	int	draw_start;
	int	draw_end;
	int	color;
}		t_vline;

// Calculate x-coordinate in camera space, which box of the map,
// and length of ray from current position to next x or y-side
t_pos	calc_pos(t_vars *vars, int x)
{
	t_pos	pos;
	double	camera_x;

	camera_x = 2 * x / (double)SCREENWIDTH - 1;
	pos.ray_dir_x = vars->dirX + vars->planeX * camera_x;
	pos.ray_dir_y = vars->dirY + vars->planeY * camera_x;
	pos.map_x = (int)vars->posX;
	pos.map_y = (int)vars->posY;
	if (pos.ray_dir_x == 0)
		pos.delta_dist_x = 1e30;
	else
		pos.delta_dist_x = fabs(1 / pos.ray_dir_x);
	if (pos.ray_dir_y == 0)
		pos.delta_dist_y = 1e30;
	else
		pos.delta_dist_y = fabs(1 / pos.ray_dir_y);
	return (pos);
}

// Calculate step and initial sideDist
t_dir	calc_dir(t_vars *vars, t_pos *pos)
{
	t_dir	dir;

	if (pos->ray_dir_x < 0)
	{
		dir.step_x = -1;
		dir.side_dist_x = (vars->posX - pos->map_x) * pos->delta_dist_x;
	}
	else
	{
		dir.step_x = 1;
		dir.side_dist_x = (pos->map_x + 1.0 - vars->posX) * pos->delta_dist_x;
	}
	if (pos->ray_dir_y < 0)
	{
		dir.step_y = -1;
		dir.side_dist_y = (vars->posY - pos->map_y) * pos->delta_dist_y;
	}
	else
	{
		dir.step_y = 1;
		dir.side_dist_y = (pos->map_y + 1.0 - vars->posY) * pos->delta_dist_y;
	}
	return (dir);
}

// return perpendicular wall distance
double	perform_dda(t_pos *pos, t_dir *dir, int *side)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (dir->side_dist_x < dir->side_dist_y)
		{
			dir->side_dist_x += pos->delta_dist_x;
			pos->map_x += dir->step_x;
			*side = 0;
		}
		else
		{
			dir->side_dist_y += pos->delta_dist_y;
			pos->map_y += dir->step_y;
			*side = 1;
		}
		if (worldMap[pos->map_x][pos->map_y] > 0)
			hit = 1;
	}
	if (*side == 0)
		return (dir->side_dist_x - pos->delta_dist_x);
	else
		return (dir->side_dist_y - pos->delta_dist_y);
}

t_vline	calc_vline(double perpWallDist, t_pos *pos, int side)
{
	t_vline	vline;
	int		line_height;
	int		box;

	line_height = (int)(SCREENHEIGHT / perpWallDist);
	vline.draw_start = -line_height / 2 + SCREENHEIGHT / 2;
	if (vline.draw_start < 0)
		vline.draw_start = 0;
	vline.draw_end = line_height / 2 + SCREENHEIGHT / 2;
	if (vline.draw_end >= SCREENHEIGHT)
		vline.draw_end = SCREENHEIGHT - 1;
	box = worldMap[pos->map_x][pos->map_y];
	if (box == 1)
		vline.color = 0xFF0000FF;
	else if (box == 2)
		vline.color = 0x00FF00FF;
	else if (box == 3)
		vline.color = 0x0000FFFF;
	else if (box == 4)
		vline.color = 0xFFFFFFFF;
	else
		vline.color = 0xFFFF00FF;
	if (side == 1)
		vline.color = vline.color - 88;
	return (vline);
}

void	render(t_vars *vars)
{
	t_render_vars	r_vars;
	int				side;
	t_vline			vline;
	int				x;
	int				y;

	clean_img(vars->img);
	x = 0;
	while (x < SCREENWIDTH)
	{
		r_vars.pos = calc_pos(vars, x);
		r_vars.dir = calc_dir(vars, &r_vars.pos);
		vline = calc_vline(perform_dda(&r_vars.pos, &r_vars.dir, &side),
				&r_vars.pos, side);
		y = vline.draw_start;
		while (y < vline.draw_end)
		{
			mlx_put_pixel(vars->img, x, y, vline.color);
			y++;
		}
		x++;
	}
}
