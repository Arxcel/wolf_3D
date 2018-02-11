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
								SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH,
								WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		MSG(SDL_GetError());
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1,
								SDL_RENDERER_ACCELERATED)))
		MSG(SDL_GetError());
	if (!(sdl->texture = SDL_CreateTexture(sdl->ren,
								SDL_PIXELFORMAT_RGBA8888,
								SDL_TEXTUREACCESS_STREAMING,
								WIN_WIDTH, WIN_HEIGHT)))
		MSG(SDL_GetError());
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 0xFF);
	SDL_RenderClear(sdl->ren);
	SDL_RenderPresent(sdl->ren);
	sdl->img = sdl_create_image(WIN_WIDTH, WIN_HEIGHT);
	sdl->running = 1;
}

t_img				sdl_create_image(size_t w, size_t h)
{
	t_img img;

	img.width = w;
	img.height = h;
	if (!(img.pixels = ft_memalloc(sizeof(int) * img.width * img.height)))
		MSG("Error allocating memory for pixels");
	sdl_clear_image(&img);
	return (img);
}

void				sdl_clear_image(t_img *img)
{
	ft_bzero(img->pixels, img->width * img->height * 4);
}

void				sdl_put_image(t_img *img, t_sdl sdl)
{
	SDL_UpdateTexture(sdl.texture, NULL, img->pixels, WIN_WIDTH * 4);
	sdl_clear_image(img);
	SDL_RenderCopy(sdl.ren, sdl.texture, NULL, NULL);
	SDL_RenderPresent(sdl.ren);
}

void				sdl_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || (size_t)x > img->width || y < 0 || (size_t)y > img->height)
		return ;
	img->pixels[x + y * img->width] = color;
}

void				sdl_hook(t_sdl *sdl)
{
	while (SDL_PollEvent(&sdl->e) != 0)
	{
		if (sdl->e.type == SDL_QUIT)
			sdl->running = 0;
		else if (sdl->e.type == SDL_KEYDOWN)
		{
			if (sdl->e.key.keysym.sym == 27)
				sdl->running = 0;
		}
		else if (sdl->e.type == SDL_MOUSEMOTION)
		{
			printf("x: %d\ty: %d\n", sdl->e.motion.x, sdl->e.motion.y);
		}
	}
}
