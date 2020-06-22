#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> /* Inclusion du header de SDL_image (adapter le dossier au besoin) */

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *Perso = NULL;
    SDL_Rect positionPerso;
    SDL_Event event;
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Double Buffering akther smoothness
    SDL_WM_SetCaption("Gestion des évènements en SDL", NULL);

    Perso = IMG_Load("mario.gif");
    

    positionPerso.x = ecran->w / 2 - Perso->w / 2;
    positionPerso.y = 750;

    
    SDL_EnableKeyRepeat(5,5 ); // Activation de la répétition des touches

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
          case SDL_MOUSEBUTTONUP: // clic gauche ychedd mouvement souris 
            positionPerso.x = event.button.x;
            positionPerso.y = event.button.y;
            break;


            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                   /* case SDLK_UP:
                        positionPerso.y--;
                        break;
                    case SDLK_DOWN:
                        positionPerso.y++;
                        break; */
                    case SDLK_RIGHT:
                        positionPerso.x++;
                        break;
                    case SDLK_LEFT:
                        positionPerso.x--;
                        break;
                }
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(Perso, NULL, ecran, &positionPerso);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(Perso);
    SDL_Quit();

    return EXIT_SUCCESS;
}

