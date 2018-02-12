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
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

static t_matrix33			v_rot(double angle)
{
	t_matrix33	a;
	double		an;

	an = angle;
	a.r[0] = (t_mrow3){cos(an), -sin(an), 0};
	a.r[1] = (t_mrow3){sin(an), cos(an), 0};
	a.r[2] = (t_mrow3){0, 0, 1};
	return (a);
}

int				ft_killer(const char *reason)
{
	if (reason && *reason)
		ft_putendl_fd(reason, 2);
	exit(0);
}

static void		create_texture(t_main *m)
{
	int		i;
/*	int		x;
	int		y;
	int xorcolor;
	int ycolor;
	int xycolor;*/
	SDL_Surface *sur;
	
	i = -1;
	while (++i < 8)
	{
		sur = IMG_Load("../pics/eagle.png");
		m->texture[i] = SDL_CreateTextureFromSurface(m->sdl.ren, sur);
	}

//	x = -1;
//	while (++x < TEX_WIDTH)
//	{
//		y = -1;
//		while (++y < TEX_HEIGHT)
//		{
//			xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
//			ycolor = y * 256 / TEX_HEIGHT;
//			xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
//			m->texture[0][TEX_WIDTH * y + x] = (65536 * 254 * (x != y && x != TEX_WIDTH - y)); //flat red texture with black cross
//			m->texture[1][TEX_WIDTH * y + x] = (xycolor + 256 * xycolor + 65536 * xycolor); //sloped greyscale
//			m->texture[2][TEX_WIDTH * y + x] = (256 * xycolor + 65536 * xycolor); //sloped yellow gradient
//			m->texture[3][TEX_WIDTH * y + x] = (xorcolor + 256 * xorcolor + 65536 * xorcolor); //xor greyscale
//			m->texture[4][TEX_WIDTH * y + x] = (256 * xorcolor); //xor green
//			m->texture[5][TEX_WIDTH * y + x] = (65536 * 192 * (x % 16 && y % 16)); //red bricks
//			m->texture[6][TEX_WIDTH * y + x] = (65536 * ycolor); //red gradient
//			m->texture[7][TEX_WIDTH * y + x] = (128 + 256 * 128 + 65536 * 128); //flat grey texture
//			unsigned long tw, th;
//			loadImage(texture[0], tw, th, "pics/eagle.png");
//			loadImage(texture[1], tw, th, "pics/redbrick.png");
//			loadImage(texture[2], tw, th, "pics/purplestone.png");
//			loadImage(texture[3], tw, th, "pics/greystone.png");
//			loadImage(texture[4], tw, th, "pics/bluestone.png");
//			loadImage(texture[5], tw, th, "pics/mossy.png");
//			loadImage(texture[6], tw, th, "pics/wood.png");
//			loadImage(texture[7], tw, th, "pics/colorstone.png");
//		}
//	}
}

static void		ray_cast(t_main *m)
{
	int			x;
	double		cam_x;
	t_vector2	ray_dir;
	double		ray_length;
	int			map[2];
	t_vector2	side_dist;
	t_vector2	delta_dist;
	int			step[2];
	int			hit;
	int			side;
	int			line_height;
	int			draw[2];
	int			color;
	x = -1;
	while (++x < (int)m->sdl.img.width)
	{
		cam_x = 2 * x / (double)m->sdl.img.width - 1;
		ray_dir[0] = m->player.dir[0] + m->player.cam[0] * cam_x;
		ray_dir[1] = m->player.dir[1] + m->player.cam[1] * cam_x;
		map[0] = (int)m->player.pos[0];
		map[1] = (int)m->player.pos[1];
		delta_dist[0] = fabs(1 / ray_dir[0]);
		delta_dist[1] = fabs(1 / ray_dir[1]);
		hit = 0;
		if (ray_dir[0] < 0)
		{
			step[0] = -1;
			side_dist[0] = (m->player.pos[0] - map[0]) * delta_dist[0];
		}
		else
		{
			step[0] = 1;
			side_dist[0] = (map[0] + 1 - m->player.pos[0]) * delta_dist[0];
		}
		if (ray_dir[1] < 0)
		{
			step[1] = -1;
			side_dist[1] = (m->player.pos[1] - map[1]) * delta_dist[1];
		}
		else
		{
			step[1] = 1;
			side_dist[1] = (map[1] + 1 - m->player.pos[1]) * delta_dist[1];
		}
		while (hit == 0)
		{
			if (side_dist[0] < side_dist[1])
			{
				side_dist[0] += delta_dist[0];
				map[0] += step[0];
				side = 0;
			}
			else
			{
				side_dist[1] += delta_dist[1];
				map[1] += step[1];
				side = 1;
			}
			if (g_world_map[map[0]][map[1]] > 0)
				hit = 1;
		}
		if (side == 0)
			ray_length = (map[0] - m->player.pos[0]
						+ (1 - step[0]) / 2) / ray_dir[0];
		else
			ray_length = (map[1] - m->player.pos[1]
						+ (1 - step[1]) / 2) / ray_dir[1];
		line_height = (int)(m->sdl.img.height / ray_length);
		draw[0] = -line_height / 2 + (int)(m->sdl.img.height / m->player.state);
		if (draw[0] < 0)
			draw[0] = 0;
		draw[1] = line_height / 2 + (int)(m->sdl.img.height / m->player.state);
		if (draw[1] >= WIN_HEIGHT)
			draw[1] = WIN_HEIGHT - 1;

		//texturing calculations
		int texNum = g_world_map[map[0]][map[1]] - 1;
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = m->player.pos[1] + ray_length * ray_dir[1];
		else
			wallX = m->player.pos[0] + ray_length * ray_dir[0];
		wallX -= floor(wallX);

		//x coordinate on the texture
		int texX = (int)(wallX * TEX_WIDTH);
		if(side == 0 && ray_dir[0] > 0)
			texX = TEX_WIDTH - texX - 1;
		if(side == 1 && ray_dir[1] < 0)
			texX = TEX_WIDTH - texX - 1;


		/*color = 0xFFFFFFFF;
		if (g_world_map[map[0]][map[1]] == 1)
			color = 0xFF0000FF;
		else if (g_world_map[map[0]][map[1]] == 2)
			color = 0x00FFFFFF;
		else if (g_world_map[map[0]][map[1]] == 3)
			color = 0x0000FFFF;
		else if (g_world_map[map[0]][map[1]] == 4)
			color = 0x0F0F0FFF;
		else if (g_world_map[map[0]][map[1]] == 5)
			color = 0xF00F0FFF;
		if (side == 1)
			color = color / 2;*/


//		while (draw[0] < draw[1])
//		{
//			int d = draw[0] * 256 - WIN_HEIGHT * 128 + line_height * 128;  //256 and 128
//			int texY = ((d * TEX_HEIGHT) / TEX_HEIGHT) / 256;
//			color = m->texture[texNum][TEX_HEIGHT * texY + texX];
//			if(side == 1)
//				color = (color >> 1) & 8355711;
//			sdl_pixel_put(&m->sdl.img, x, draw[0], color);
//			draw[0]++;
//		}


		for(int y = draw[0]; y<draw[1]; y++)
		{
			int d = y * 256 - WIN_HEIGHT * 128 + line_height * 128;  //256 and 128
			// factors to avoid floats
			int texY = ((d * TEX_HEIGHT) / line_height) / 256;
			color = m->texture[texNum]->pixels[TEX_HEIGHT * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1)
				color /= 2;

			sdl_pixel_put(&m->sdl.img, x, y, color);
//			buffer[y][x] = color;
		}

	}
}

static void		calc_performance(t_frame *f)
{
	f->old_time = f->curr_time;
	f->curr_time = SDL_GetTicks();
	f->frame_time = (f->curr_time - f->old_time) / 1000.0;
	f->move_speed = f->frame_time * f->speed_mod;
	f->rot_speed = f->frame_time * 3.0;
}

static void		finish(t_main *m)
{
	free(m->sdl.img.pixels);
	SDL_DestroyRenderer(m->sdl.ren);
	SDL_DestroyWindow(m->sdl.win);
	SDL_Quit();
}

/*
static void		jump(t_main *m)
{
	if (m->player.j_time == 0)
		m->player.state = 1.95;
	if (m->player.j_time == 5)
		m->player.state = 1.90;
	if (m->player.j_time == 10)
		m->player.state = 1.85;
	if (m->player.j_time == 15)
		m->player.state = 1.80;
	if (m->player.j_time == 20)
		m->player.state = 1.75;
	if (m->player.j_time == 25)
		m->player.state = 1.70;
	if (m->player.j_time == 30)
		m->player.state = 1.65;
	if (m->player.j_time == 35)
		m->player.state = 1.60;
	if (m->player.j_time == 40)
		m->player.state = 1.55;
	if (m->player.j_time == 45)
		m->player.state = 1.50;
	if (m->player.j_time == 50)
		m->player.state = 1.55;
	if (m->player.j_time == 55)
		m->player.state = 1.60;
	if (m->player.j_time == 60)
		m->player.state = 1.65;
	if (m->player.j_time == 65)
		m->player.state = 1.70;
	if (m->player.j_time == 70)
		m->player.state = 1.75;
	if (m->player.j_time == 75)
		m->player.state = 1.8;
	if (m->player.j_time == 80)
		m->player.state = 1.85;
	if (m->player.j_time == 85)
		m->player.state = 1.9;
	if (m->player.j_time == 90)
		m->player.state = 1.95;
	if (m->player.j_time == 95)
	{
		m->player.state = 2;
		m->player.j_time = 0;
		m->kb.key3 = 0;
	}
	m->player.j_time++;
}
*/

/*static void		sit(t_main *m)
{
	if (m->player.j_time == 0)
		m->player.state = 2.1;
	if (m->player.j_time == 5)
		m->player.state = 2.2;
	if (m->player.j_time == 10)
		m->player.state = 2.3;
	if (m->player.j_time == 15)
		m->player.state = 2.4;
	if (m->player.j_time == 20)
		m->player.state = 2.5;
	if (m->player.j_time == 25)
		m->player.state = 2.6;
	if (m->player.j_time == 30)
		m->player.state = 2.7;
	if (m->player.j_time == 35)
		m->player.state = 2.8;
	if (m->player.j_time == 40)
		m->player.state = 2.9;
	if (m->player.j_time == 45)
		m->player.state = 3;
	m->player.j_time++;
}

static void		stand(t_main *m)
{
	if (m->player.j_time == 0)
		m->player.state = 2.9;
	if (m->player.j_time == 5)
		m->player.state = 2.8;
	if (m->player.j_time == 10)
		m->player.state = 2.7;
	if (m->player.j_time == 15)
		m->player.state = 2.6;
	if (m->player.j_time == 20)
		m->player.state = 2.5;
	if (m->player.j_time == 25)
		m->player.state = 2.4;
	if (m->player.j_time == 30)
		m->player.state = 2.3;
	if (m->player.j_time == 35)
		m->player.state = 2.2;
	if (m->player.j_time == 40)
		m->player.state = 2.1;
	if (m->player.j_time == 45)
	{
		m->player.state = 2;
		m->kb.key4 = 0;
		m->player.j_time = -1;
	}
	m->player.j_time++;
}*/

static void		move_player(t_main *m)
{
	if (m->kb.key1 == MOVE_FORWARD)
	{
		if(g_world_map[(int)(m->player.pos[0] + m->player.dir[0] * m->frame.move_speed)][(int)(m->player.pos[1])] == 0)
			m->player.pos[0] += m->player.dir[0] * m->frame.move_speed;
		if(g_world_map[(int)(m->player.pos[0])][(int)(m->player.pos[1] + m->player.dir[1] * m->frame.move_speed)] == 0)
			m->player.pos[1] += m->player.dir[1] * m->frame.move_speed;
	}
	else if (m->kb.key1 == MOVE_BACKWARD)
	{
		if(g_world_map[(int)(m->player.pos[0] - m->player.dir[0] * m->frame.move_speed)][(int)(m->player.pos[1])] == 0)
			m->player.pos[0] -= m->player.dir[0] * m->frame.move_speed;
		if(g_world_map[(int)(m->player.pos[0])][(int)(m->player.pos[1] - m->player.dir[1] * m->frame.move_speed)] == 0)
			m->player.pos[1] -= m->player.dir[1] * m->frame.move_speed;
	}
	if (m->kb.key2 == TURN_RIGHT)
	{
		m->player.dir = m_mult_v(v_rot(m->frame.rot_speed), m->player.dir);
		m->player.cam = m_mult_v(v_rot(m->frame.rot_speed), m->player.cam);
	}
	else if (m->kb.key2 == TURN_LEFT)
	{
		m->player.dir = m_mult_v(v_rot(-m->frame.rot_speed), m->player.dir);
		m->player.cam = m_mult_v(v_rot(-m->frame.rot_speed), m->player.cam);
	}
	else if (m->mouse.x1)
	{
		m->player.dir = m_mult_v(v_rot(-m->frame.rot_speed), m->player.dir);
		m->player.cam = m_mult_v(v_rot(-m->frame.rot_speed), m->player.cam);
		m->mouse.x1 = 0;
	}
	else if (m->mouse.x2)
	{
		m->player.dir = m_mult_v(v_rot(m->frame.rot_speed), m->player.dir);
		m->player.cam = m_mult_v(v_rot(m->frame.rot_speed), m->player.cam);
		m->mouse.x2 = 0;
	}
//	if (m->kb.key3 == JUMP)
//	{
//		jump(m);
//	}
//	if (m->kb.key4 == SIT)
//	{
//		sit(m);
//	}
/*	else if (m->kb.key4 == STAND)
	{
		stand(m);
	}*/
}



int				main(void)
{
	t_main		m;

	ft_bzero(&m, sizeof(m));
	sdl_init(&m.sdl);
	m.player.pos = (t_vector2){22, 11.5};
	m.player.dir = (t_vector2){-1, 0};
	m.player.cam = (t_vector2){0, 0.66};
	m.player.state = 2;
	m.frame.speed_mod = 5;
	create_texture(&m);
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
