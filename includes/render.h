#ifndef RENDER_H
# define RENDER_H

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
	int			draw_start;
	int			draw_end;
	uint32_t	color;
	int			box;
	int			line_height;
	int			tex_width;
	int			tex_height;
	int			tex_x;
	int			tex_y;
}			t_vline;

t_pos	calc_pos(t_vars *vars, int x);
int		get_side(int side, int step_x, int step_y);
void	sprites(t_vars *vars);

#endif
