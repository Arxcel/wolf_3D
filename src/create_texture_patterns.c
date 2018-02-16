/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture_patterns.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 14:16:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/16 14:55:36 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

static void		fill_texture_std(t_main *m, int x, int y)
{
	m->texture[0][TEX_W * y + x] =
			(65536 * 254 * (x != y && x != TEX_W - y));
	m->texture[1][TEX_W * y + x] =
			(XY_C(x, y) + 256 * XY_C(x, y) + 65536 * XY_C(x, y));
	m->texture[2][TEX_W * y + x] =
			(256 * XY_C(x, y) + 65536 * XY_C(x, y));
	m->texture[3][TEX_W * y + x] =
			(XOR_C(x, y) + 256 * XOR_C(x, y) + 65536 * XOR_C(x, y));
	m->texture[4][TEX_W * y + x] =
			(256 * XOR_C(x, y));
	m->texture[5][TEX_W * y + x] =
			(65536 * 192 * (x % 16 && y % 16));
	m->texture[6][TEX_W * y + x] =
			(65536 * Y_C(x, y));
	m->texture[7][TEX_W * y + x] =
			(128 + 256 * 128 + 65536 * 128);
}

static int		get_col_by_i(void *ptr, int i)
{
	unsigned char *tmp;

	tmp = (unsigned char*)ptr;
	return (set_rgb(tmp[i], tmp[i + 1], tmp[i + 2]));
}

static void		ft_get_image(int *pixels, const char *path)
{
	SDL_Surface		*sur;
	int				i;
	int				size;
	int				k;

	i = -1;
	size = TEX_H * TEX_W;
	k = 0;
	sur = IMG_Load(path);
	while (++i < size)
	{
		pixels[i] = get_col_by_i(sur->pixels, k);
		k += 3;
	}
	SDL_FreeSurface(sur);
}

static void		fill_texture_custom(t_main *m)
{
	ft_get_image(m->texture[0], "./pics/eagle.png");
	ft_get_image(m->texture[1], "./pics/redbrick.png");
	ft_get_image(m->texture[2], "./pics/bluestone.png");
	ft_get_image(m->texture[3], "./pics/wood.png");
	ft_get_image(m->texture[4], "./pics/greystone.png");
	ft_get_image(m->texture[5], "./pics/mossy.png");
	ft_get_image(m->texture[6], "./pics/colorstone.png");
	ft_get_image(m->texture[7], "./pics/purplestone.png");
}

void			create_textures(t_main *m)
{
	int		i;
	int		y;

	i = -1;
	while (++i < 8)
		m->texture[i] = (int*)malloc(sizeof(int) * (int)TEX_H * (int)TEX_W);
	if (m->tex_custom)
		fill_texture_custom(m);
	else
	{
		i = -1;
		while (++i < TEX_W)
		{
			y = -1;
			while (++y < TEX_H)
				fill_texture_std(m, i, y);
		}
	}
}
