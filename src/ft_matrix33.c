/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix33.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:59:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/11 16:59:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

t_matrix33	m_mult_m(t_matrix33 a, t_matrix33 b)
{
	int			i;
	int			j;
	t_matrix33	c;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			c.r[i][j] = a.r[i][0] * b.r[0][j] + a.r[i][1] * b.r[1][j] +
						a.r[i][2] * b.r[2][j];
		}
	}
	return (c);
}

t_matrix33	m_transpose(t_matrix33 a)
{
	int			i;
	int			j;
	t_matrix33	c;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			c.r[i][j] = a.r[j][i];
	}
	return (c);
}

t_vector2	m_mult_p(t_matrix33 m, t_vector2 v)
{
	double		a;
	double		b;
	double		w;
	t_vector2	res;

	a = v[0] * m.r[0][0] + v[1] * m.r[1][0];
	b = v[0] * m.r[0][1] + v[1] * m.r[1][1];
	w = v[0] * m.r[0][2] + v[1] * m.r[1][2];
	res[0] = a / w;
	res[1] = b / w;
	return (res);
}

t_vector2	m_mult_v(t_matrix33 m, t_vector2 v)
{
	double		a;
	double		b;
	double		c;
	t_vector2	res;

	a = v[0] * m.r[0][0] + v[1] * m.r[1][0];
	b = v[0] * m.r[0][1] + v[1] * m.r[1][1];
	c = v[0] * m.r[0][2] + v[1] * m.r[1][2];
	res[0] = a;
	res[1] = b;
	return (res);
}
