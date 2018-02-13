/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture_patterns.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 14:16:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/13 14:16:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

static void	fill_texture(t_main *m, int x, int y)
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

void		create_std_texture(t_main *m)
{
	int		x;
	int		y;

	x = -1;
	while (++x < 8)
		m->texture[x] = (int*)malloc(sizeof(int) * (int)TEX_H * (int)TEX_W);
	x = -1;
	while (++x < TEX_W)
	{
		y = -1;
		while (++y < TEX_H)
			fill_texture(m, x, y);
	}
}
