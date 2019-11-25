#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "display.h"
#include "segmentation.h"

void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}



int main()
{
	SDL_Surface *screen = NULL;

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(640,480, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("OCR", NULL);
	
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 169, 169, 169));
	SDL_Flip(screen);

	button(400, 100, 125, 40, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff), screen);
	//button(200, 100, 197, 40, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00), screen);
	button(245, 250, 150, 60, SDL_MapRGB(screen->format, 0xc9, 0xc9, 0xc9), screen);

	SDL_Flip(screen);

	int clicked = 0;

	int continuer = 1;
	while(continuer)
	{
		SDL_WaitEvent(&event);


		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;




			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					if(event.button.x < 396 && event.button.x > 244 && event.button.y < 310 && event.button.y > 250)
					{
						button(245, 250, 150, 60, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00), screen);
						clicked = 1;
						SDL_Flip(screen);	
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					button(245, 250, 150, 60, SDL_MapRGB(screen->format, 0xc9, 0xc9, 0xc9), screen);
					SDL_Flip(screen);
					if(clicked == 1)
					{
						segmentation("alphabet.bmp");
						clicked = 0;
					}
				}
		}
	}



	SDL_Quit();
	return 0;
}