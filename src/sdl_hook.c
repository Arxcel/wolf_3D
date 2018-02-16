/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:57:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/16 18:07:57 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

static void			key_down(int key, t_main *m)
{
	if (key == SDLK_ESCAPE)
		m->sdl.running = 0;
	else if (key == SDLK_UP || key == SDLK_w)
		m->kb.key1 = MOVE_FORWARD;
	else if (key == SDLK_DOWN || key == SDLK_s)
		m->kb.key1 = MOVE_BACKWARD;
	else if (key == SDLK_RIGHT || key == SDLK_d)
		m->kb.key2 = TURN_RIGHT;
	else if (key == SDLK_LEFT || key == SDLK_a)
		m->kb.key2 = TURN_LEFT;
	else if (key == 1073742049)
		m->frame.speed_mod = 10;
	else if (key == SDLK_1)
		m->hard_mod = !m->hard_mod;
	else if (key == SDLK_2)
		m->tex_custom = !m->tex_custom;
	else if (key == SDLK_3)
		m->player.view_area = 1;
	else if (key == SDLK_4)
		m->player.view_area = m->player.view_area + 1 > 3 ? 3 :
							m->player.view_area + 1;
	else if (key == SDLK_5)
		m->ui = !m->ui;
	else if (key == SDLK_SPACE)
		m->g.boom = 1;
}

static void			key_up(int key, t_main *m)
{
	if (key == SDLK_UP || key == SDLK_w)
		m->kb.key1 = 0;
	else if (key == SDLK_DOWN || key == SDLK_s)
		m->kb.key1 = 0;
	else if (key == SDLK_RIGHT || key == SDLK_d)
		m->kb.key2 = 0;
	else if (key == SDLK_LEFT || key == SDLK_a)
		m->kb.key2 = 0;
	else if (key == 1073742049)
		m->frame.speed_mod = 5;
}

void				sdl_hook(t_main *m)
{
	while (SDL_PollEvent(&m->sdl.e) != 0)
	{
		if (m->sdl.e.type == SDL_QUIT)
			m->sdl.running = 0;
		else if (m->sdl.e.type == SDL_KEYDOWN)
			key_down(m->sdl.e.key.keysym.sym, m);
		else if (m->sdl.e.type == SDL_KEYUP)
			key_up(m->sdl.e.key.keysym.sym, m);
	}
}
