#ifndef __MIN_MAX_ORDI_H__
#define __MIN_MAX_ORDI_H__
#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"
#include "gestion_othello.h"
#include "define.h"

int fonc_eval(int mat[N][N], int couleur);

int joueur(int mat[N][N], int couleur, int nb_coup_prevu, int alpha, int beta);

int ordi(int mat[N][N], int couleur, int nb_coup_prevu, int alpha, int beta);

void tour_ordi(int mat[N][N], int couleur, int nb_coup_prevu, int *px, int *py);

#endif