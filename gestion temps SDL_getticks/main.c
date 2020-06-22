#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *Perso = NULL;
    SDL_Rect positionPerso;
    SDL_Event event;
    int continuer = 1;
    int tempsPrecedent = 0, tempsActuel = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du temps en SDL", NULL);

    Perso = IMG_Load("mario.gif");

    positionPerso.x = 0;
    positionPerso.y = 430;

    SDL_EnableKeyRepeat(10, 10);

    while (continuer)
    {
        SDL_PollEvent(&event); /* On utilise PollEvent et non WaitEvent pour ne pas bloquer le programme */
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            positionPerso.x++; /* On bouge Perso */
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }
        else /* Si ça fait moins de 30 ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
        {
           SDL_Delay(30 - (tempsActuel - tempsPrecedent));
        } 

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(Perso, NULL, ecran, &positionPerso);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(Perso);
    SDL_Quit();

    return EXIT_SUCCESS;
}
