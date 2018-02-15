/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 17:00:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/14 17:00:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

static void		check_wall_dir(t_ray *r, double *floor)
{
	if (r->side == 0 && r->ray_dir[0] > 0)
	{
		floor[0] = r->ray_position[0];
		floor[1] = r->ray_position[1] + r->wall_hit_pos;
	}
	else if (r->side == 0 && r->ray_dir[0] < 0)
	{
		floor[0] = r->ray_position[0] + 1.0;
		floor[1] = r->ray_position[1] + r->wall_hit_pos;
	}
	else if (r->side == 1 && r->ray_dir[1] > 0)
	{
		floor[0] = r->ray_position[0] + r->wall_hit_pos;
		floor[1] = r->ray_position[1];
	}
	else
	{
		floor[0] = r->ray_position[0] + r->wall_hit_pos;
		floor[1] = r->ray_position[1] + 1.0;
	}
}

static void		get_floor_point(t_main *m, t_ray *r, int t_id)
{
	r->color = m->texture[t_id][TEX_H * r->floor_tex_pos[1] +
														r->floor_tex_pos[0]];
	r->color = set_rgb((unsigned int)((r->color & 0x00ff0000) >> 16) / 2,
					(unsigned int)((r->color & 0x0000ff00) >> 8) / 2,
					(unsigned int)((r->color & 0x000000ff)) / 2);
	if (m->hard_mod && r->curr_dist > m->player.view_area)
		r->color = set_rgb((unsigned int)(((r->color & 0x00ff0000) >> 16) /
				r->curr_dist), (unsigned int)(((r->color & 0x0000ff00) >> 8) /
				r->curr_dist), (unsigned int)(((r->color & 0x000000ff)) /
				r->curr_dist));
}

static void		get_top_point(t_main *m, t_ray *r, int t_id)
{
	r->color = m->texture[t_id][TEX_H * r->floor_tex_pos[1] +
														r->floor_tex_pos[0]];
	if (r->curr_dist > 1)
		r->color = set_rgb((unsigned int)(((r->color & 0x00ff0000) >> 16) /
				r->curr_dist), (unsigned int)(((r->color & 0x0000ff00) >> 8) /
				r->curr_dist), (unsigned int)(((r->color & 0x000000ff)) /
				r->curr_dist));
}

void			floor_cast(t_ray *r, t_main *m, int x)
{
	int		y;

	check_wall_dir(r, r->floor);
	r->dist_to_wall = r->ray_length;
	r->dist_to_player = 0.0;
	if (r->draw[1] < 0)
		r->draw[1] = WIN_H;
	y = r->draw[1];
	while (++y < WIN_H)
	{
		r->curr_dist = WIN_H / (2.0 * y - WIN_H);
		r->percent = (r->curr_dist - r->dist_to_player) /
				(r->dist_to_wall - r->dist_to_player);
		r->curr_floor[0] = r->percent * r->floor[0] +
				(1.0 - r->percent) * m->player.pos[0];
		r->curr_floor[1] = r->percent * r->floor[1] +
				(1.0 - r->percent) * m->player.pos[1];
		r->floor_tex_pos[0] = (int)(r->curr_floor[0] * TEX_W / 2) % TEX_W;
		r->floor_tex_pos[1] = (int)(r->curr_floor[1] * TEX_W / 2) % TEX_W;
		get_floor_point(m, r, 4);
		sdl_pixel_put(&m->sdl.img, x, y, r->color);
		get_top_point(m, r, 3);
		sdl_pixel_put(&m->sdl.img, x, WIN_H - y, r->color);
	}
}
