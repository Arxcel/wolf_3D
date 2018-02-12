/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix33.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:59:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/11 16:59:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATRIX33_H
# define FT_MATRIX33_H

typedef double	t_mrow3 __attribute__((vector_size(sizeof(double)*3)));
typedef struct	s_matrix
{
	t_mrow3		r[3];
}				t_matrix33;

t_matrix33		m_mult_m(t_matrix33 a, t_matrix33 b);
t_matrix33		m_transpose(t_matrix33 a);
t_vector2		m_mult_v(t_matrix33 m, t_vector2 v);
t_vector2		m_mult_p(t_matrix33 m, t_vector2 v);
#endif
