/**
*\file affichage.c
*\brief Fichier qui lance le jeu de l'othello
*\author Julien Le Roux
*\version 2.0
*\date 01 avril 2018
**/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Commun/mat_int/define.h"
#include "sdljeu.h"



int main(int argc, char** argv)
{

	SDL_Window* fenetre = NULL;  /** pointeur création fenetre SDL **/ 

	SDL_Renderer* renderer = NULL; /** creation du renderer 	**/
	
	aff_menu(renderer, fenetre, 0); /** appel du menu 	**/

	return 0;

}

