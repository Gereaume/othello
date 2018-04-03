#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "affichage.h"

int clic(int x, int y, struct SDL_Rect *rect);

int aff_menu(SDL_Renderer* renderer, SDL_Window* fenetre, int j);

int lancer_jeu1(SDL_Renderer* renderer, SDL_Window* fenetre);

int lancer_jeu2(SDL_Renderer* renderer, SDL_Window* fenetre, int nb_coup_prevu);
