/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:09:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/07 17:09:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF_H
# define FT_WOLF_H
# include <stdio.h>
# include "ft_libftu.h"
# include "ft_sdl.h"
# include "ft_vector2.h"
# include "ft_matrix33.h"

# define WIN_WIDTH			700
# define WIN_HEIGHT			600
# define TEX_WIDTH			64
# define TEX_HEIGHT			64
# define MSG(x)				ft_killer(x)
# define MOVE_FORWARD		1
# define MOVE_BACKWARD		2
# define TURN_LEFT			3
# define TURN_RIGHT			4
# define JUMP				5
# define SIT				6
# define STAND				7
# define MOVE_RIGHT			8
# define MOVE_LEFT			9
# define SPRINT				10
typedef struct				s_player
{
	t_vector2				pos;
	t_vector2				dir;
	t_vector2				cam;
	int						j_time;
	double					state;
}							t_player;

typedef struct				s_frame
{
	int						old_time;
	int						curr_time;
	double					frame_time;
	double					move_speed;
	int						speed_mod;
	double					rot_speed;
}							t_frame;
typedef struct 				s_map
{
	size_t					m_width;
	size_t					m_height;
	int						**w_map;
}							t_map;
typedef struct				s_keyboard
{
	int						key1;
	int						key2;
	int						key3;
	int						key4;
}							t_keyboard;
typedef struct				s_mouse
{
	int						x1;
	int						y1;
	int						x2;
	int						y2;
}							t_mouse;
typedef struct				s_main
{
	t_sdl					sdl;
	t_map					map;
	t_player				player;
	t_frame					frame;
	t_keyboard				kb;
	t_mouse					mouse;
	SDL_Texture				*texture[8];
}							t_main;
int							ft_killer(const char *reason);
void						sdl_hook(t_main *m);
#endif
