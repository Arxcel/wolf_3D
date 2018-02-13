/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 14:11:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/11 14:11:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int g_world_map[MAP_WIDTH][MAP_HEIGHT] =
{
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
	{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
	{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
	{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
	{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
	{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
	{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
	{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
	{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
	{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}
};

static void					go_forward(t_main *m)
{
	if (g_world_map[(int)(m->player.pos[0] + m->player.dir[0] *
						m->frame.move_speed)][(int)(m->player.pos[1])] == 0)
		m->player.pos[0] += m->player.dir[0] * m->frame.move_speed;
	if (g_world_map[(int)(m->player.pos[0])][(int)(m->player.pos[1] +
						m->player.dir[1] * m->frame.move_speed)] == 0)
		m->player.pos[1] += m->player.dir[1] * m->frame.move_speed;
}

static void					go_back(t_main *m)
{
	if (g_world_map[(int)(m->player.pos[0] - m->player.dir[0] *
						m->frame.move_speed)][(int)(m->player.pos[1])] == 0)
		m->player.pos[0] -= m->player.dir[0] * m->frame.move_speed;
	if (g_world_map[(int)(m->player.pos[0])][(int)(m->player.pos[1] -
						m->player.dir[1] * m->frame.move_speed)] == 0)
		m->player.pos[1] -= m->player.dir[1] * m->frame.move_speed;
}

static void					turn_right(t_main *m)
{
	m->player.dir = m_mult_v(v_rot(m->frame.rot_speed), m->player.dir);
	m->player.cam = m_mult_v(v_rot(m->frame.rot_speed), m->player.cam);
	m->mouse.x2 = 0;
}

static void					turn_left(t_main *m)
{
	m->player.dir = m_mult_v(v_rot(-m->frame.rot_speed), m->player.dir);
	m->player.cam = m_mult_v(v_rot(-m->frame.rot_speed), m->player.cam);
	m->mouse.x1 = 0;
}

void						move_player(t_main *m)
{
	if (m->kb.key1 == MOVE_FORWARD)
		go_forward(m);
	else if (m->kb.key1 == MOVE_BACKWARD)
		go_back(m);
	if (m->kb.key2 == TURN_RIGHT || m->mouse.x2)
		turn_right(m);
	else if (m->kb.key2 == TURN_LEFT || m->mouse.x1)
		turn_left(m);
}

int							ft_killer(const char *reason)
{
	if (reason && *reason)
		ft_putendl_fd(reason, 2);
	exit(0);
}

static void					ray_cast_init(t_ray *r, t_main *m)
{
	r->ray_dir[0] = m->player.dir[0] + m->player.cam[0] * r->cam_x;
	r->ray_dir[1] = m->player.dir[1] + m->player.cam[1] * r->cam_x;
	r->ray_position[0] = (int)m->player.pos[0];
	r->ray_position[1] = (int)m->player.pos[1];
	r->delta_dist[0] = fabs(1 / r->ray_dir[0]);
	r->delta_dist[1] = fabs(1 / r->ray_dir[1]);
	r->hit = 0;
}

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
	(void)m;
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
		if (g_world_map[r->ray_position[0]][r->ray_position[1]] > 0)
			r->hit = 1;
	}
}

static void					calculate_texture(t_ray *r, t_main *m)
{
	r->tex_id = g_world_map[r->ray_position[0]][r->ray_position[1]] - 1;
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

static void					draw_vertical_line(t_ray *r, t_main *m, int x)
{
	int d;
	int y;

	y = r->draw[0] - 1;
	while (++y < r->draw[1])
	{
		d = y * 256 - WIN_H * 128 + r->line_height * 128;
		r->tex[1] = ((d * TEX_H) / r->line_height) / 256;
		r->color = m->texture[r->tex_id][TEX_H * r->tex[1] + r->tex[0]];
		if (r->side == 1)
			r->color /= 2;
		sdl_pixel_put(&m->sdl.img, x, y, r->color);
	}
}

static void					calc_wall_height(t_ray *r, t_main *m)
{
	if (r->side == 0)
		r->ray_length = (r->ray_position[0] - m->player.pos[0]
						+ (1 - r->step[0]) / 2) / r->ray_dir[0];
	else
		r->ray_length = (r->ray_position[1] - m->player.pos[1]
						+ (1 - r->step[1]) / 2) / r->ray_dir[1];
	r->line_height = (int)(m->sdl.img.height / r->ray_length);
	r->draw[0] = -r->line_height / 2 +
			(int)(m->sdl.img.height / m->player.state);
	if (r->draw[0] < 0)
		r->draw[0] = 0;
	r->draw[1] = r->line_height / 2 +
			(int)(m->sdl.img.height / m->player.state);
	if (r->draw[1] >= WIN_H)
		r->draw[1] = WIN_H - 1;
}

static void					ray_cast(t_main *m)
{
	int			x;
	t_ray		ray;

	x = -1;
	while (++x < (int)m->sdl.img.width)
	{
		ray.cam_x = 2 * x / (double)m->sdl.img.width - 1;
		ray_cast_init(&ray, m);
		setup_ray_dir(&ray, m);
		cast_ray(&ray, m);
		calc_wall_height(&ray, m);
		calculate_texture(&ray, m);
		draw_vertical_line(&ray, m, x);
	}
}

static void					calc_performance(t_frame *f)
{
	f->old_time = f->curr_time;
	f->curr_time = SDL_GetTicks();
	f->frame_time = (f->curr_time - f->old_time) / 1000.0;
	f->move_speed = f->frame_time * f->speed_mod;
	f->rot_speed = f->frame_time * 3.0;
}

static void					finish(t_main *m)
{
	free(m->sdl.img.pixels);
	SDL_DestroyRenderer(m->sdl.ren);
	SDL_DestroyWindow(m->sdl.win);
	SDL_Quit();
}

int							main(void)
{
	t_main		m;

	ft_bzero(&m, sizeof(m));
	sdl_init(&m.sdl);
	m.player.pos = (t_vector2){22, 11.5};
	m.player.dir = (t_vector2){-1, 0};
	m.player.cam = (t_vector2){0, 0.66};
	m.player.state = 2;
	m.frame.speed_mod = 5;
	create_std_texture(&m);
	while (m.sdl.running)
	{
		sdl_hook(&m);
		ray_cast(&m);
		sdl_put_image(&m.sdl);
		calc_performance(&m.frame);
		move_player(&m);
	}
	finish(&m);
	return (0);
}
