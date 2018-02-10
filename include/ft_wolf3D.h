/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf3D.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:09:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/07 17:09:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MY_CL_H
# define _MY_CL_H
# include <stdio.h>
# include "ft_libftu.h"
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# define WIN_WIDTH			1280
# define WIN_HEIGHT			720
# define MSG(x)				ft_killer(x)


int				ft_killer(const char *reason);

#endif
