#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "gestion_matrice.h"
#include "gestion_othello.h"
#include "joueur.h"
#include "min_max_ordi.h"


#define N 8

int aff_regle(SDL_Renderer* renderer, SDL_Window* fenetre);

int aff_cercleblanc(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* b, SDL_Window * fenetre);

int aff_cerclenoir(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* n, SDL_Window * fenetre);

int aff_mat(SDL_Renderer* renderer, SDL_Window* fenetre);

int aff_ordi(int mat[N][N],t_joueur joueur1,t_joueur joueur2, SDL_Renderer *renderer, SDL_Surface* n, SDL_Window * fenetre, int nb_coup_prevu, int j);

int aff_menu_jouer(SDL_Renderer* renderer, SDL_Window* fenetre);
