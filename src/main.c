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

static void				calc_performance(t_frame *f)
{
	f->old_time = f->curr_time;
	f->curr_time = SDL_GetTicks();
	f->frame_time = (f->curr_time - f->old_time) / 1000.0;
	f->move_speed = f->frame_time * f->speed_mod;
	f->rot_speed = f->frame_time * 3.0;
}

static void				finish(t_main *m)
{
	free(m->sdl.img.pixels);
	SDL_DestroyTexture(m->sdl.texture);
	SDL_DestroyRenderer(m->sdl.ren);
	SDL_DestroyWindow(m->sdl.win);
	SDL_Quit();
}

static void				init_wolf(t_main *m)
{
	m->hard_mod = 0;
	m->ui = 0;
	m->tex_custom = 0;
	m->player.pos = m->map.player_pos;
	m->player.dir = (t_vector2){-1, 0};
	m->player.cam = (t_vector2){0, 0.66};
	m->player.state = 2;
	m->player.view_area = 1;
	m->frame.speed_mod = 5;
}

static void				get_ui(t_main *m)
{
	SDL_Rect		texr;
	SDL_Texture		*img;
	int				wh[2];

	img = IMG_LoadTexture(m->sdl.ren, "../pics/Zap_Gun_Dual_Wield_BO.png");
	SDL_QueryTexture(img, NULL, NULL, &wh[0], &wh[1]);
	texr.x = (int)(WIN_W / 10.0);
	texr.y = (int)(WIN_H / 1.65);
	texr.w = (int)(wh[0] / 1.5);
	texr.h = (int)(wh[1] / 1.5);
	SDL_RenderCopy(m->sdl.ren, img, NULL, &texr);
	SDL_DestroyTexture(img);
}

int						main(int ac, char **av)
{
	t_main		m;
	int			i;

	ft_bzero(&m, sizeof(m));
	ac != 2 ? MSG(USAGE) : ft_ftoa(av[1], &m.map);
	sdl_init(&m.sdl);
	init_wolf(&m);
	while (m.sdl.running)
	{
		create_textures(&m);
		sdl_hook(&m);
		ray_cast(&m);
		sdl_put_image(&m.sdl);
		if (m.ui)
			get_ui(&m);
		SDL_RenderPresent(m.sdl.ren);
		calc_performance(&m.frame);
		move_player(&m);
		i = -1;
		while (++i < 8)
			free(m.texture[i]);
	}
	finish(&m);
	return (0);
}
