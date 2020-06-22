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
    int sprint=0;
    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(900, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Double Buffering akther smoothness
    SDL_WM_SetCaption("Gestion des évènements en SDL", NULL);

    Perso = IMG_Load("mario.gif");
    SDL_SetColorKey(Perso, SDL_SRCCOLORKEY, SDL_MapRGB(Perso->format, 0, 0, 255)); //trodd background transparent

    positionPerso.x = ecran->w / 2 - Perso->w / 2;
    positionPerso.y = 600;

    SDL_ShowCursor(SDL_DISABLE); // curseur invisible dans la fenetre
    SDL_EnableKeyRepeat(5,5 ); // Activation de la répétition des touches

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEMOTION:
            positionPerso.x = event.motion.x;
            //positionPerso.y = event.motion.y; //  yet'harekk verticalement
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
            case SDLK_LSHIFT://if shift is pressed then sprint =1 w vitesse taugmenti
                sprint=1;
                break;
            case SDLK_RIGHT:
                if (sprint==1)
                {
                    positionPerso.x=positionPerso.x+3;

                }

                positionPerso.x++;


                break;
            case SDLK_LEFT:
                if (sprint==1)
                {
                    positionPerso.x=positionPerso.x-3;

                }

                positionPerso.x--;
                break;

            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_LSHIFT:// if shift is  released then vitesse tarjaa aadia w sprint tarjaa 0
                sprint=0;
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

