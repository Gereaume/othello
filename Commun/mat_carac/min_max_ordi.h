#ifndef __MIN_MAX_ORDI_H__
#define __MIN_MAX_ORDI_H__
#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"
#include "define.h"

int fonc_eval(char mat[N][N], char couleur);

int joueur(char mat[N][N], char couleur, int nb_coup_prevu, int alpha, int beta);

int ordi(char mat[N][N], char couleur, int nb_coup_prevu, int alpha, int beta);

void tour_ordi(char mat[N][N], char couleur, int nb_coup_prevu, int *px, int *py);

#endif