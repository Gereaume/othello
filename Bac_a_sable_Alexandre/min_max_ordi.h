#ifndef __MIN_MAX_ORDI_H__
#define __MIN_MAX_ORDI_H__
#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"
#include "define.h"

int fonc_eval(char mat[N][N], char couleur, int lig, int col, int nb_pions_en_plus);

int joueur(char mat[N][N], char couleur, int nb_coup_prevu, int * x, int * y);

int ordi(char mat[N][N], char couleur, int nb_coup_prevu, int * x, int * y);

void ordi_cb(char mat[N][N], char couleur, int nb_coup_prevu);

#endif