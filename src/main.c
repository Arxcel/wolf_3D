/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 14:11:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/16 18:24:50 by vkozlov          ###   ########.fr       */
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
	SDL_DestroyTexture(m->u.ui);
	SDL_DestroyTexture(m->g.gun_sprite);
	SDL_DestroyRenderer(m->sdl.ren);
	SDL_DestroyWindow(m->sdl.win);
	SDL_Quit();
}

static void				init_wolf(t_main *m)
{
	m->hard_mod = 0;
	m->ui = 1;
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
	int				wh[2];

	m->u.ui = IMG_LoadTexture(m->sdl.ren, "./pics/Zap_Gun_Dual_Wield_BO.png");
	SDL_QueryTexture(m->u.ui, NULL, NULL, &wh[0], &wh[1]);
	m->u.tex.x = 0;
	m->u.tex.y = (int)(WIN_H - wh[1]);
	m->u.tex.w = WIN_W;
	m->u.tex.h = (int)(wh[1]);
	SDL_RenderCopy(m->sdl.ren, m->u.ui, NULL, &m->u.tex);
	m->g.gun_sprite = IMG_LoadTexture(m->sdl.ren, "./pics/pistol.png");
	SDL_QueryTexture(m->g.gun_sprite, NULL, NULL, &wh[0], &wh[1]);
	m->g.curr_sprite.x = 0;
	m->g.curr_sprite.y = 0;
	m->g.curr_sprite.w = (int)((wh[0]) / 4);
	m->g.curr_sprite.h = (int)(wh[1] * 2);
	m->g.all_sprites.x = (int)(WIN_W / 2.2);
	m->g.all_sprites.y = (int)(WIN_H - m->u.tex.h - wh[1] * 2 + 15);
	m->g.all_sprites.w = (int)(wh[0] * 2 / 4);
	m->g.all_sprites.h = (int)(wh[1] * 2);
	m->g.boom = 0;
}

int						main(int ac, char **av)
{
	t_main		m;
	int			i;

	ft_bzero(&m, sizeof(m));
	ac != 2 ? MSG(USAGE) : ft_ftoa(av[1], &m.map);
	sdl_init(&m.sdl);
	init_wolf(&m);
	get_ui(&m);
	while (m.sdl.running)
	{
		create_textures(&m);
		sdl_hook(&m);
		ray_cast(&m);
		sdl_put_image(&m.sdl);
		if (m.ui)
			put_ui(&m);
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
