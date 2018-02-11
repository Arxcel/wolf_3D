/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector22.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:56:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/11 16:56:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_wolf.h"

t_vector2		v_mult_d(t_vector2 v, double d)
{
	v[0] *= d;
	v[1] *= d;
	return (v);
}

t_vector2		v_div_d(t_vector2 v, double d)
{
	v[0] /= d;
	v[1] /= d;
	return (v);
}

double			v_length(t_vector2 v)
{
	double norm;
	double sqrt_calculated;
	double length;

	norm = v[0] * v[0] + v[1] * v[1];
	sqrt_calculated = sqrt(norm);
	length = sqrt_calculated < 0 ? -sqrt_calculated : sqrt_calculated;
	return (length);
}

t_vector2		v_normalize(t_vector2 v)
{
	double		norm;
	t_vector2	res;

	norm = v_length(v);
	res = v_div_d(v, norm);
	return (res);
}

double			v_dot(t_vector2 v1, t_vector2 v2)
{
	double	res;

	res = v1[0] * v2[0] + v1[1] * v2[1];
	return (res);
}