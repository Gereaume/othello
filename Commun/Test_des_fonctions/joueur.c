#include <stdio.h>
#include <stdlib.h>

typedef struct JOUEUR JOUEUR;
struct JOUEUR
{
	char nom_joueur[50];
	int score_joueur;
	int nb_partie_gagné;
};
