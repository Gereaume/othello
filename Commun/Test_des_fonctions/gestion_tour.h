#ifndef __GESTION_TOUR_H__
#define __GESTION_TOUR_H__
#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "joueur.h"


int gagnant(char mat[N][N]);

void gestion_tour(char mat[N][N],t_joueur joueur1,t_joueur joueur2);

#endif