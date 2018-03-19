#ifndef __JOUEUR_H__
#define __JOUEUR_H__
#include <stdio.h>
#include <stdlib.h>

typedef struct joueur_s
{
	char nom_joueur[50];
	int score_joueur;
	//int nb_partie_gagne;
} t_joueur;

void afficher_nom(char nom[50]);
#endif
