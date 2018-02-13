/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:55:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/13 16:55:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

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
