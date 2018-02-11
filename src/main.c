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
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
		{
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

int				ft_killer(const char *reason)
{
	if (reason && *reason)
		ft_putendl_fd(reason, 2);
	exit(0);
}

static void		ray_cast(t_img *img)
{
	t_vector2	pos;
	t_vector2	dir;
	t_vector2	cam;
	int			x;
	double		cam_x;
	t_vector2	ray_dir;
	double		ray_length;
	int			map[2];
	t_vector2	sideDist;
	t_vector2	deltaDist;
	int			step[2];
	int			hit;
	int			side;
	int			line_height;
	int			draw[2];
	int			color;


	pos = (t_vector2){22 ,12};
	dir = (t_vector2){-1, 0};
	cam = (t_vector2){0, 0.66};
	x = -1;
	while (++x < (int)img->width)
	{
		cam_x = 2 * x / (double)img->width - 1;
		ray_dir[0] = dir[0] + cam[0] * cam_x;
		ray_dir[1] = dir[1] + cam[1] * cam_x;
		map[0] = (int)pos[0];
		map[1] = (int)pos[1];
		deltaDist[0] = fabs(1 / ray_dir[0]);
		deltaDist[1] = fabs(1 / ray_dir[1]);
		hit = 0;

		if (ray_dir[0] < 0)
		{
			step[0] = -1;
			sideDist[0] = (pos[0] - map[0]) * deltaDist[0];
		}
		else
		{
			step[0] = 1;
			sideDist[0] = (map[0] + 1 - pos[0]) * deltaDist[0];
		}

		if (ray_dir[1] < 0)
		{
			step[1] = -1;
			sideDist[1] = (pos[1] - map[1]) * deltaDist[1];
		}
		else
		{
			step[1] = 1;
			sideDist[1] = (map[1] + 1 - pos[1]) * deltaDist[1];
		}

		while (hit == 0)
		{
			if (sideDist[0] < sideDist[1])
			{
				sideDist[0] += deltaDist[0];
				map[0] += step[0];
				side = 0;
			}
			else
			{
				sideDist[1] += deltaDist[1];
				map[1] += step[1];
				side = 1;
			}
			if (worldMap[map[0]][map[1]] > 0) hit = 1;
		}

		if (side == 0)
			ray_length = (map[0] - pos[0] + (1 - step[0]) / 2) / ray_dir[0];
		else
			ray_length = (map[1] - pos[1] + (1 - step[1]) / 2) / ray_dir[1];

		line_height = (int) (WIN_HEIGHT / ray_length);
		draw[0] = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw[0] < 0)
			draw[0] = 0;
		draw[1] = line_height / 2 + WIN_HEIGHT / 2;
		if (draw[1] >= WIN_HEIGHT)
			draw[1] = WIN_HEIGHT - 1;
		color = 0xFFFFFFFF;
		if (worldMap[map[0]][map[1]] == 1)
			color = 0xFF0000FF;
		else if (worldMap[map[0]][map[1]] == 2)
			color = 0x00FFFFFF;
		else if (worldMap[map[0]][map[1]] == 3)
			color = 0x0000FFFF;
		else if (worldMap[map[0]][map[1]] == 4)
			color = 0x0F0F0FFF;
		else if (worldMap[map[0]][map[1]] == 5)
			color = 0xF00F0FFF;
		if (side == 1)
			color = color / 2;
		while (draw[0] != draw[1])
		{
			sdl_pixel_put(img, x, draw[0], color);
			draw[0]++;
		}
	}
}

int				main(void)
{
	t_sdl		sdl;
	int oldTime = 0;
	int currTime = 0;
	double	frame_time;

	ft_bzero(&sdl, sizeof(sdl));
	sdl_init(&sdl);
	while (sdl.running)
	{
		sdl_hook(&sdl);
		oldTime = currTime;
		ray_cast(&sdl.img);
		sdl_put_image(&sdl.img, sdl);
		currTime = SDL_GetTicks();
		SDL_Delay(10);
		frame_time = (currTime - oldTime) / 1000.0;
		printf("FPS: %f\n", 1 / frame_time );
	}
	free(sdl.img.pixels);
	SDL_DestroyRenderer(sdl.ren);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
