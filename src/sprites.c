/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:58:47 by jarredon          #+#    #+#             */
/*   Updated: 2022/09/05 12:46:29 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_spt {
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screenx;
	int		sprite_height;
	int		drawstart_y;
	int		drawend_y;
	int		sprite_width;
	int		drawstart_x;
	int		drawend_x;
}			t_spt;

static void	sort_sprites(int *sprite_order, double *sprite_distance, int amount)
{
	double	*old_distances;
	int		i;
	int		j;

	old_distances = (double *)malloc(amount * sizeof(double));
	if (old_distances == NULL)
		return ;
	ft_memcpy(old_distances, sprite_distance, amount * sizeof(double));
	ft_qsort_dbl(sprite_distance, amount);
	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount)
		{
			if (sprite_distance[i] == old_distances[j])
			{
				sprite_order[amount - i - 1] = j;
				break ;
			}
		}
	}
	free(old_distances);
}

static void	do_math(t_vars *vars, int *sprite_order, int i, t_spt *spt)
{
	spt->sprite_x = g_sprites[sprite_order[i]].x - vars->pos_x;
	spt->sprite_y = g_sprites[sprite_order[i]].y - vars->pos_y;
	spt->inv_det = 1.0
		/ (vars->plane_x * vars->dir_y - vars->plane_y * vars->dir_x);
	spt->transform_x = spt->inv_det
		* (vars->dir_y * spt->sprite_x - vars->dir_x * spt->sprite_y);
	spt->transform_y = spt->inv_det
		* (-vars->plane_y * spt->sprite_x + vars->plane_x * spt->sprite_y);
	spt->sprite_screenx = (int)((SCREENWIDTH / 2)
			* (1 + spt->transform_x / spt->transform_y));
	spt->sprite_height = abs((int)(SCREENHEIGHT / spt->transform_y));
	spt->drawstart_y = -spt->sprite_height / 2 + SCREENHEIGHT / 2;
	if (spt->drawstart_y < 0)
		spt->drawstart_y = 0;
	spt->drawend_y = spt->sprite_height / 2 + SCREENHEIGHT / 2;
	if (spt->drawend_y >= SCREENHEIGHT)
		spt->drawend_y = SCREENHEIGHT - 1;
	spt->sprite_width = abs((int)(SCREENHEIGHT / spt->transform_y));
	spt->drawstart_x = -spt->sprite_width / 2 + spt->sprite_screenx;
	if (spt->drawstart_x < 0)
		spt->drawstart_x = 0;
	spt->drawend_x = spt->sprite_width / 2 + spt->sprite_screenx;
	if (spt->drawend_x > SCREENWIDTH)
		spt->drawend_x = SCREENWIDTH;
}

typedef struct s_s {
	int			idx_tex;
	int			tex_x;
	int			tex_y;
	int			d;
}				t_s;

static void	print_stripe(t_vars *vars, t_spt *spt, int stripe, int i_sprite)
{
	t_s			s;
	int			y;
	uint8_t		*pix;
	uint32_t	color;

	s.idx_tex = g_sprites[i_sprite].texture;
	s.tex_x = (int)(256 * (stripe - (-spt->sprite_width / 2
					+ spt->sprite_screenx)) * g_textures[s.idx_tex]->width
			/ spt->sprite_width) / 256;
	if (spt->transform_y > 0 && spt->transform_y < g_zbuffer[stripe])
	{
		y = spt->drawstart_y;
		while (y < spt->drawend_y)
		{
			s.d = y * 256 - SCREENHEIGHT * 128 + spt->sprite_height * 128;
			s.tex_y = ((s.d * g_textures[s.idx_tex]->height)
					/ spt->sprite_height) / 256;
			pix = &g_textures[s.idx_tex]->pixels[g_textures[s.idx_tex]->width
				* s.tex_y * 4 + s.tex_x * 4];
			color = (pix[0] << 24) | (pix[1] << 16) | (pix[2] << 8) | pix[3];
			if ((color & 0xFFFFFF00) != 0)
				mlx_put_pixel(vars->img, stripe, y, color);
			y++;
		}
	}
}

void	sprites(t_vars *vars)
{
	int		sprite_order[NUMSPRITES];
	double	sprite_distance[NUMSPRITES];
	int		i;
	t_spt	spt;
	int		stripe;

	i = -1;
	while (++i < NUMSPRITES)
		sprite_distance[i] = (vars->pos_x - g_sprites[i].x)
			* (vars->pos_x - g_sprites[i].x) + (vars->pos_y - g_sprites[i].y)
			* (vars->pos_y - g_sprites[i].y);
	sort_sprites(sprite_order, sprite_distance, NUMSPRITES);
	i = -1;
	while (++i < NUMSPRITES)
	{
		do_math(vars, sprite_order, i, &spt);
		stripe = spt.drawstart_x;
		while (stripe < spt.drawend_x)
		{
			print_stripe(vars, &spt, stripe, sprite_order[i]);
			stripe++;
		}
	}
}
