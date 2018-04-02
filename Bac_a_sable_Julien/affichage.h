#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "Commun/mat_int/gestion_matrice.h"
#include "Commun/mat_int/gestion_othello.h"
#include "Commun/mat_int/joueur.h"
#include "Commun/mat_int/min_max_ordi.h"

#define N 8

void init(SDL_Renderer *renderer, SDL_Window* fenetre);

int aff_regle(SDL_Renderer* renderer, SDL_Window* fenetre);

int aff_cercleblanc(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* b, SDL_Window * fenetre);

int aff_cerclenoir(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* n, SDL_Window * fenetre);

int aff_mat(SDL_Renderer* renderer, SDL_Window* fenetre);

int aff_ordi(int mat[N][N],t_joueur joueur1,t_joueur joueur2, SDL_Renderer *renderer, SDL_Surface* n, SDL_Window * fenetre, int nb_coup_prevu, int i);

int aff_menu_jouer(SDL_Renderer* renderer, SDL_Window* fenetre);