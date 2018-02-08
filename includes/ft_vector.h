/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 22:15:03 by vkozlov           #+#    #+#             */
/*   Updated: 2018/01/23 20:01:56 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

typedef double	t_vector __attribute__((vector_size(sizeof(double)*3)));

t_vector			v_normalize(t_vector v);
t_vector			v_mult_d(t_vector v, double d);
t_vector			v_div_d(t_vector v, double d);
double				v_length(t_vector v);
double				v_dot(t_vector v1, t_vector v2);
#endif
