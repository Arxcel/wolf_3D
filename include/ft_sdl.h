/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sdl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 13:45:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/11 13:45:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SDL_H
# define FT_SDL_H
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

typedef struct		s_img
{
	size_t			width;
	size_t			height;
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
void				sdl_put_image(t_img *img, t_sdl sdl);
void				sdl_pixel_put(t_img *img, int x, int y, int color);
void				sdl_hook(t_sdl *sdl);
#endif
