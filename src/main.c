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

int							ft_killer(const char *reason)
{
	if (reason && *reason)
		ft_putendl_fd(reason, 2);
	exit(0);
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

int							main(int ac, char **av)
{
	t_main		m;

	ft_bzero(&m, sizeof(m));
	if (ac != 2)
		MSG("Wrong number of arguments.");
	ft_ftoa(av[1], &m.map);
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
