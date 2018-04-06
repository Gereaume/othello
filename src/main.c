/**
*\file affichage.c
*\brief Fichier qui lance le jeu de l'othello
*\author Julien Le Roux
*\version 2.0
*\date 06 avril 2018
**/

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "define.h"
#include "sdljeu.h"



int main(int argc, char** argv)
{

	SDL_Window* fenetre = NULL;  /** pointeur création fenetre SDL **/ 

	SDL_Renderer* renderer = NULL; /** creation du renderer 	**/
	
	aff_menu(renderer, fenetre, 0); /** appel du menu 	**/

	return 0;

}

