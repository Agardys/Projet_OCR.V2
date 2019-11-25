#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "display.h"


void button(int x, int y, int w, int h, Uint32 color, SDL_Surface *screen)
{
	SDL_Rect r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	SDL_FillRect(screen, &r, color);	
}