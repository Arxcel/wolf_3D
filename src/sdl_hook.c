/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:57:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/13 13:57:00 by vkozlov          ###   ########.fr       */
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
		m->frame.speed_mod = 7;
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

static void			mouse_motion(int x, int y, t_main *m)
{
	(void)y;
	SDL_WarpMouseInWindow(m->sdl.win, WIN_W / 2, WIN_H / 2);
	if (x < WIN_W / 2)
		m->mouse.x1 = x;
	if (x > WIN_W / 2)
		m->mouse.x2 = x;
}

/*
**printf("x1: %d\tx2 %d\n",m->mouse.x1,m->mouse.x2);
*/

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
		else if (m->sdl.e.type == SDL_MOUSEMOTION)
			mouse_motion(m->sdl.e.motion.x, m->sdl.e.motion.y, m);
	}
}
