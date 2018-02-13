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
# include <fcntl.h>
# include "ft_libftu.h"
# include "ft_sdl.h"
# include "ft_vector2.h"
# include "ft_matrix33.h"
# define WIN_W			700
# define WIN_H			600
# define TEX_W			64
# define TEX_H			64
# define MSG(x)				ft_killer(x)
# define MOVE_FORWARD		1
# define MOVE_BACKWARD		2
# define TURN_LEFT			3
# define TURN_RIGHT			4
# define SPRINT				10

# define XOR_C(x, y)	(x * 256 / TEX_W) ^ (y * 256 / TEX_H)
# define Y_C(x, y)		(y * 256 / TEX_H)
# define XY_C(x, y)		(y * 128 / TEX_H + x * 128 / TEX_W)

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
typedef struct				s_map
{
	int						m_w;
	int						m_h;
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
typedef struct				s_ray
{
	double					cam_x;
	t_vector2				ray_dir;
	double					ray_length;
	int						ray_position[2];
	t_vector2				side_dist;
	t_vector2				delta_dist;
	int						step[2];
	int						hit;
	int						side;
	int						line_h;
	int						draw[2];
	int						color;
	int						tex_id;
	int						tex[2];
	double					wall_hit_pos;
}							t_ray;
typedef struct				s_main
{
	t_sdl					sdl;
	t_map					map;
	t_player				player;
	t_frame					frame;
	t_keyboard				kb;
	t_mouse					mouse;
	int						*texture[8];
}							t_main;
int							ft_killer(const char *reason);
t_matrix33					v_rot(double angle);
void						sdl_hook(t_main *m);
void						move_player(t_main *m);
void						ft_ftoa(const char *file, t_map *map);
void						create_std_texture(t_main *m);
void						ray_cast(t_main *m);
#endif
