/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 21:10:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/13 21:10:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

static void					go_forward(t_main *m)
{
	if (m->map.w_map[(int)(m->player.pos[0] + m->player.dir[0] *
						m->frame.move_speed)][(int)(m->player.pos[1])] == 0)
		m->player.pos[0] += m->player.dir[0] * m->frame.move_speed;
	if (m->map.w_map[(int)(m->player.pos[0])][(int)(m->player.pos[1] +
						m->player.dir[1] * m->frame.move_speed)] == 0)
		m->player.pos[1] += m->player.dir[1] * m->frame.move_speed;
}

static void					go_back(t_main *m)
{
	if (m->map.w_map[(int)(m->player.pos[0] - m->player.dir[0] *
						m->frame.move_speed)][(int)(m->player.pos[1])] == 0)
		m->player.pos[0] -= m->player.dir[0] * m->frame.move_speed;
	if (m->map.w_map[(int)(m->player.pos[0])][(int)(m->player.pos[1] -
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
