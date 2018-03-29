/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sdl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 13:45:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/03/29 15:36:28 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SDL_H
# define FT_SDL_H
# include "SDL.h"
# include "SDL_image.h"

typedef struct		s_img
{
	size_t			w;
	size_t			h;
	int				*pixels;
}					t_img;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*texture;
	SDL_Event		e;
	t_img			img;
	int				running;
}					t_sdl;
void				sdl_init(t_sdl *sdl);
t_img				sdl_create_image(size_t w, size_t h);
void				sdl_clear_image(t_img *img);
void				sdl_put_image(t_sdl *sdl);
void				sdl_pixel_put(t_img *img, int x, int y, int color);
#endif
