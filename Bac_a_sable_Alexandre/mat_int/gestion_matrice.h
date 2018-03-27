#ifndef __GESTION_MATRICE_H__
#define __GESTION_MATRICE_H__
#include <stdio.h>
#include <stdlib.h>

#include "define.h"

void init_mat(int mat[N][N]);

void lire_mat(int mat[N][N]);

void ecrire_mat(int mat[N][N],int couleur,int lig,int col);

int compter_couleur(int mat[N][N],int couleur);

int hors_mat(int lig,int col);

void copie(int mat[N][N], int mat2[N][N]);

int retourner(int mat[N][N], int couleur, int lig, int col);

int coup_possible(int mat[N][N], int couleur, int lig, int col);

int peut_jouer(int mat[N][N], int couleur);

#endif
