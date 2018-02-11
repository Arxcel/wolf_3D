/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:09:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/07 17:09:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF_H
# define FT_WOLF_H
# include <stdio.h>
# include "ft_libftu.h"
# include "ft_sdl.h"
# include "ft_vector2.h"
# include "ft_matrix33.h"


# define WIN_WIDTH			700
# define WIN_HEIGHT			600
# define MSG(x)				ft_killer(x)

int				ft_killer(const char *reason);

#endif
