#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
//#include <SDL/SDL_ttf.h>
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

	//SDL_Color black = {0, 0, 0};

	SDL_Init(SDL_INIT_VIDEO);

	/*if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
	}

	TTF_Font *font;
	font = TTF_OpenFont("externals/fonts/aleo-light-webfont.ttf", 16);
	*/
	screen = SDL_SetVideoMode(350,480, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("OCR", NULL);
	
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 169, 169, 169));
	SDL_Flip(screen);


	button(4, 100, 342, 40, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00), screen);
	button(5, 145, 125, 40, SDL_MapRGB(screen->format, 0xc9, 0xc9, 0xc9), screen);

	//SDL_Rect position;
	//position.x = 5;
	//position.y = 145; 
	//SDL_Surface *text_surface;

	//text_surface = TTF_RenderText_Shaded(font, "Start", black)



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
						button(5, 145, 125, 40, SDL_MapRGB(screen->format, 0xc9, 0xc9, 0xc9), screen);
						clicked = 1;
						SDL_Flip(screen);	
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					button(5, 145, 125, 40, SDL_MapRGB(screen->format, 0xc9, 0xc9, 0xc9), screen);
					SDL_Flip(screen);
					if(clicked == 1)
					{
						segmentation("alphabet.bmp");
						clicked = 0;
					}
				}
		}

		//SDL_BlitSurface(text_surface, NULL, screen, position);
	}

	//TTF_CloseFont(font);
	//TTF_Quit();
	SDL_Quit();
	return 0;
}