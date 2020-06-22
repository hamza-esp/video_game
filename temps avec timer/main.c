#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint32 bougerPerso(Uint32 intervalle, void *parametre);


int main(int argc, char *argv[])
{
    SDL_Surface    *ecran = NULL, *Perso = NULL;
    SDL_Rect        positionPerso;
    SDL_Event         event;
    int continuer = 1;
    SDL_TimerID timer; /* Variable pour stocker le numéro du timer */



    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du temps en SDL", NULL);

    Perso = IMG_Load("mario.gif");

    positionPerso.x = 0;
    positionPerso.y = 430;



    while (continuer)
    {
        SDL_PollEvent(&event); /* On utilise PollEvent et non WaitEvent pour ne pas bloquer le programme */
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        }

       timer = SDL_AddTimer(2500, bougerPerso, &positionPerso); /* Démarrage du timer */
        SDL_Delay(30);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(Perso, NULL, ecran, &positionPerso);
        SDL_Flip(ecran);
    }


SDL_RemoveTimer(timer); /* Arrêt du timer */
SDL_FreeSurface(Perso);
    SDL_Quit();

    return EXIT_SUCCESS;
}



/* Fonction de callback (sera appelée toutes les 30 ms) */
Uint32 bougerPerso(Uint32 intervalle, void *parametre)
{
    SDL_Rect* positionPerso = parametre; /* Conversion de void* en SDL_Rect* */
    positionPerso->x++;

    return intervalle;
}

