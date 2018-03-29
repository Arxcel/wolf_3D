/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 21:19:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/03/29 15:50:42 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

static void					setup_ray_dir(t_ray *r, t_main *m)
{
	if (r->ray_dir[0] < 0)
	{
		r->step[0] = -1;
		r->side_dist[0] = (m->player.pos[0] -
						r->ray_position[0]) * r->delta_dist[0];
	}
	else
	{
		r->step[0] = 1;
		r->side_dist[0] = (r->ray_position[0] + 1 -
						m->player.pos[0]) * r->delta_dist[0];
	}
	if (r->ray_dir[1] < 0)
	{
		r->step[1] = -1;
		r->side_dist[1] = (m->player.pos[1] -
						r->ray_position[1]) * r->delta_dist[1];
	}
	else
	{
		r->step[1] = 1;
		r->side_dist[1] = (r->ray_position[1] + 1 -
						m->player.pos[1]) * r->delta_dist[1];
	}
}

static void					cast_ray(t_ray *r, t_main *m)
{
	while (r->hit == 0)
	{
		if (r->side_dist[0] < r->side_dist[1])
		{
			r->side_dist[0] += r->delta_dist[0];
			r->ray_position[0] += r->step[0];
			r->side = 0;
		}
		else
		{
			r->side_dist[1] += r->delta_dist[1];
			r->ray_position[1] += r->step[1];
			r->side = 1;
		}
		if (m->map.w_map[r->ray_position[0]][r->ray_position[1]] > 0)
			r->hit = 1;
	}
}

static void					draw_vertical_line(t_ray *r, t_main *m, int x)
{
	int d;
	int y;

	y = r->draw[0] - 1;
	while (++y < r->draw[1])
	{
		d = y * 256 - WIN_H * 128 + r->line_h * 128;
		r->tex[1] = ((d * TEX_H) / r->line_h) / 256;
		r->color = m->texture[r->tex_id][TEX_H * r->tex[1] + r->tex[0]];
		if (r->side == 1)
			r->color = set_rgb((unsigned int)((r->color & 0x00ff0000) >> 16) /
							2, (unsigned int)((r->color & 0x0000ff00) >> 8) / 2,
							(unsigned int)((r->color & 0x000000ff)) / 2);
		if (m->hard_mod && r->ray_length > m->player.view_area)
			r->color = set_rgb((unsigned int)(((r->color & 0x00ff0000) >> 16) /
			r->ray_length), (unsigned int)(((r->color & 0x0000ff00) >> 8) /
			r->ray_length), (unsigned int)(((r->color & 0x000000ff)) /
					r->ray_length));
		sdl_pixel_put(&m->sdl.img, x, y, r->color);
	}
}

static void					calc_wall_h_tex(t_ray *r, t_main *m)
{
	if (r->side == 0)
		r->ray_length = (r->ray_position[0] - m->player.pos[0]
						+ (1 - r->step[0]) / 2) / r->ray_dir[0];
	else
		r->ray_length = (r->ray_position[1] - m->player.pos[1]
						+ (1 - r->step[1]) / 2) / r->ray_dir[1];
	if (r->ray_length >= 1)
		r->line_h = (int)(m->sdl.img.h / r->ray_length);
	else
		r->line_h = (int)m->sdl.img.h;
	r->draw[0] = -r->line_h / 1 + (int)(m->sdl.img.h / m->player.state);
	if (r->draw[0] < 0)
		r->draw[0] = 0;
	r->draw[1] = r->line_h / 2 + (int)(m->sdl.img.h / m->player.state);
	if (r->draw[1] >= WIN_H)
		r->draw[1] = WIN_H - 1;
	r->tex_id = m->map.w_map[r->ray_position[0]][r->ray_position[1]] - 1;
	if (r->side == 0)
		r->wall_hit_pos = m->player.pos[1] + r->ray_length * r->ray_dir[1];
	else
		r->wall_hit_pos = m->player.pos[0] + r->ray_length * r->ray_dir[0];
	r->wall_hit_pos -= (int)(r->wall_hit_pos);
	r->tex[0] = (int)(r->wall_hit_pos * TEX_W);
	if (r->side == 0 && r->ray_dir[0] > 0)
		r->tex[0] = TEX_W - r->tex[0] - 1;
	if (r->side == 1 && r->ray_dir[1] < 0)
		r->tex[0] = TEX_W - r->tex[0] - 1;
}

void						ray_cast(t_main *m)
{
	int			x;
	t_ray		ray;

	x = -1;
	while (++x < (int)m->sdl.img.w)
	{
		ray.cam_x = 2 * x / (double)m->sdl.img.w - 1;
		ray.ray_dir[0] = m->player.dir[0] + m->player.cam[0] * ray.cam_x;
		ray.ray_dir[1] = m->player.dir[1] + m->player.cam[1] * ray.cam_x;
		ray.ray_position[0] = (int)m->player.pos[0];
		ray.ray_position[1] = (int)m->player.pos[1];
		ray.delta_dist[0] = fabs(1 / ray.ray_dir[0]);
		ray.delta_dist[1] = fabs(1 / ray.ray_dir[1]);
		ray.hit = 0;
		setup_ray_dir(&ray, m);
		cast_ray(&ray, m);
		calc_wall_h_tex(&ray, m);
		draw_vertical_line(&ray, m, x);
		floor_cast(&ray, m, x);
	}
}
