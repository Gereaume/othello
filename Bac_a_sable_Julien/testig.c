#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL;
    SDL_Event othello; // gestion souris

    SDL_Init(SDL_INIT_VIDEO);

    fenetre = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Gestion des événements en SDL", NULL);

    int continuer = 1;
    while (continuer)
{
    SDL_WaitEvent(&othello); // récupération de du clic de souris
    switch(othello.type) // test
    {
        case SDL_QUIT: // si on veut quitter
            continuer = 0;
            break;
        case SDL_MOUSEMOTION:
            position.x = othello.motion.x;
            position.y = othello.motion.y;
            break;
    }

    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
    SDL_BlitSurface(cas, NULL, fenetre, &position);
    SDL_Flip(fenetre);
    }

    SDL_Quit();
    return EXIT_SUCCESS;

}
