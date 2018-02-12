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
	SDL_SetWindowGrab(sdl->win, SDL_TRUE);
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

void				sdl_put_image(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, sdl->img.pixels, WIN_WIDTH * 4);
	sdl_clear_image(&sdl->img);
	SDL_RenderCopy(sdl->ren, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
}

void				sdl_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || (size_t)x > img->width || y < 0 || (size_t)y > img->height)
		return ;
	img->pixels[x + y * img->width] = color;
}

void				sdl_hook(t_main *m)
{
	while (SDL_PollEvent(&m->sdl.e) != 0)
	{
		if (m->sdl.e.type == SDL_QUIT)
			m->sdl.running = 0;
		else if (m->sdl.e.type == SDL_KEYDOWN)
		{
			if (m->sdl.e.key.keysym.sym == SDLK_ESCAPE)
				m->sdl.running = 0;
			else if (m->sdl.e.key.keysym.sym == SDLK_UP ||
					m->sdl.e.key.keysym.sym == SDLK_w)
				m->kb.key1 = MOVE_FORWARD;
			else if (m->sdl.e.key.keysym.sym == SDLK_DOWN ||
					 m->sdl.e.key.keysym.sym == SDLK_s)
				m->kb.key1 = MOVE_BACKWARD;
			else if (m->sdl.e.key.keysym.sym == SDLK_RIGHT ||
					 m->sdl.e.key.keysym.sym == SDLK_d)
				m->kb.key2 = TURN_RIGHT;
			else if (m->sdl.e.key.keysym.sym == SDLK_LEFT ||
					 m->sdl.e.key.keysym.sym == SDLK_a)
				m->kb.key2 = TURN_LEFT;
			else if (m->sdl.e.key.keysym.sym == SDLK_SPACE)
				m->kb.key3 = JUMP;
			else if (m->sdl.e.key.keysym.sym == 1073742048)
				m->kb.key4 = SIT;
			else if (m->sdl.e.key.keysym.sym == 1073742049)
				m->frame.speed_mod = 10;
//			printf("key: %d\n", m->sdl.e.key.keysym.sym);
		}
		else if (m->sdl.e.type == SDL_KEYUP)
		{
			if (m->sdl.e.key.keysym.sym == SDLK_UP ||
					 m->sdl.e.key.keysym.sym == SDLK_w)
				m->kb.key1 = 0;
			else if (m->sdl.e.key.keysym.sym == SDLK_DOWN ||
					 m->sdl.e.key.keysym.sym == SDLK_s)
				m->kb.key1 = 0;
			else if (m->sdl.e.key.keysym.sym == SDLK_RIGHT ||
					 m->sdl.e.key.keysym.sym == SDLK_d)
				m->kb.key2 = 0;
			else if (m->sdl.e.key.keysym.sym == SDLK_LEFT ||
					 m->sdl.e.key.keysym.sym == SDLK_a)
				m->kb.key2 = 0;
			else if (m->sdl.e.key.keysym.sym == 1073742048)
			{
				m->kb.key4 = STAND;
				m->player.j_time = 0;
			}
			else if (m->sdl.e.key.keysym.sym == SDLK_q)
				m->kb.key4 = 0;
			else if (m->sdl.e.key.keysym.sym == 1073742049)
				m->frame.speed_mod = 5;

		}
		else if (m->sdl.e.type == SDL_MOUSEMOTION)
		{
			SDL_WarpMouseInWindow(m->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2 );
			if (m->sdl.e.motion.x < WIN_WIDTH / 2)
				m->mouse.x1 = m->sdl.e.motion.x ;//- m->mouse.x1;
			if (m->sdl.e.motion.x > WIN_WIDTH / 2)
				m->mouse.x2 = m->sdl.e.motion.x;
//		printf("x1: %d\tx2 %d\n",m->mouse.x1,m->mouse.x2);
		}
	}
}
