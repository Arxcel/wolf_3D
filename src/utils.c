/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:55:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/16 18:23:35 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

int					set_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r << 16) | (g << 8) | b);
}

int					ft_killer(const char *reason)
{
	if (reason && *reason)
		ft_putendl_fd(reason, 2);
	exit(0);
}

t_matrix33			v_rot(double angle)
{
	t_matrix33	a;
	double		an;

	an = angle;
	a.r[0] = (t_mrow3){cos(an), -sin(an), 0};
	a.r[1] = (t_mrow3){sin(an), cos(an), 0};
	a.r[2] = (t_mrow3){0, 0, 1};
	return (a);
}

void				put_ui(t_main *m)
{
	SDL_RenderCopy(m->sdl.ren, m->u.ui, NULL, &m->u.tex);
	SDL_RenderCopy(m->sdl.ren, m->g.gun_sprite,
					&m->g.curr_sprite, &m->g.all_sprites);
}

void				shoot(t_main *m)
{
	if (m->g.boom && m->g.curr_sprite.x <= (int)(m->g.all_sprites.w))
	{
		m->g.curr_sprite.x += (m->g.all_sprites.w) * 2 / 4;
		m->g.curr_sprite.y = 0;
	}
	else
	{
		m->g.boom = 0;
		m->g.curr_sprite.x = 0;
		m->g.curr_sprite.y = 0;
	}
}
