/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector22.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:55:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/11 16:55:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Ft_vector22_H
# define Ft_vector22_H
typedef double	t_vector2 __attribute__((vector_size(sizeof(double)*2)));

t_vector2			v_normalize(t_vector2 v);
t_vector2			v_mult_d(t_vector2 v, double d);
t_vector2			v_div_d(t_vector2 v, double d);
double				v_length(t_vector2 v);
double				v_dot(t_vector2 v1, t_vector2 v2);
#endif