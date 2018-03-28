#ifndef __GESTION_MATRICE_H__
#define __GESTION_MATRICE_H__
#include <stdio.h>
#include <stdlib.h>

#include "gestion_othello.h"
#include "define.h"

void init_mat(char mat[N][N]);

void lire_mat(char mat[N][N]);

void ecrire_mat(char mat[N][N],char elem,int lig,int col);

int hors_mat(int lig,int col);

void copie(char mat[N][N], char mat2[N][N]);

#endif
