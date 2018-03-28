#ifndef __GESTION_TOUR_H__
#define __GESTION_TOUR_H__
#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "joueur.h"
#include "gestion_othello.h"
#include "gestion_matrice.h"
#include "min_max_ordi.h"

void gestion_tour(int mat[N][N],t_joueur joueur1, t_joueur joueur2);

void gestion_tour_ia(int mat[N][N], t_joueur joueur1, t_joueur joueur2, int nb_coup_prevu);

#endif