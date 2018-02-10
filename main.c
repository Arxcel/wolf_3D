
#include "ft_wolf3D.h"

int				ft_killer(const char *reason)
{
	if (reason && *reason)
		ft_putendl_fd(reason, 2);
	exit(0);
}

int					main(void) {

//	SDL_DisplayMode		displayMode;
	SDL_Window			*win;
	SDL_Renderer		*ren;
	int					isactive;
	SDL_Event			e;

	isactive = 1;
	if (SDL_Init(SDL_INIT_EVERYTHING))
		MSG(SDL_GetError());
	if (!(win = SDL_CreateWindow("My SDL", SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH,
								WIN_HEIGHT, SDL_WINDOW_SHOWN)
	))
		MSG(SDL_GetError());
	if (!(ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)))
		MSG(SDL_GetError());
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);
	while (isactive)
	{
		while(SDL_PollEvent( &e ) != 0)
		{
			if (e.type == SDL_QUIT)
				isactive = 0;
			else if (e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == 27)
					isactive = 0;
		}
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}