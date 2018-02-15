/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 14:11:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/11 14:11:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void				sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		MSG(SDL_GetError());
	if (!(sdl->win = SDL_CreateWindow("My SDL", SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, WIN_W,
								WIN_H, SDL_WINDOW_SHOWN)))
		MSG(SDL_GetError());
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		MSG(SDL_GetError());
	if (!(sdl->texture = SDL_CreateTexture(sdl->ren,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING,
								WIN_W, WIN_H)))
		MSG(SDL_GetError());
	SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 0xFF);
	SDL_RenderClear(sdl->ren);
	SDL_RenderPresent(sdl->ren);
	sdl->img = sdl_create_image(WIN_W, WIN_H);
	sdl->running = 1;
}

t_img				sdl_create_image(size_t w, size_t h)
{
	t_img img;

	img.w = w;
	img.h = h;
	if (!(img.pixels = ft_memalloc(sizeof(int) * img.w * img.h)))
		MSG("Error allocating memory for pixels");
	sdl_clear_image(&img);
	return (img);
}

void				sdl_clear_image(t_img *img)
{
	ft_bzero(img->pixels, img->w * img->h * 4);
}

void				sdl_put_image(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, sdl->img.pixels, WIN_W * 4);
	sdl_clear_image(&sdl->img);
	SDL_RenderCopy(sdl->ren, sdl->texture, NULL, NULL);
}

void				sdl_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || (size_t)x > img->w || y < 0 || (size_t)y > img->h)
		return ;
	img->pixels[x + y * img->w] = color;
}
