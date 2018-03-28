#ifndef __GESTION_OTHELLO_H__
#define __GESTION_OTHELLO_H__
#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"
#include "define.h"

#define NOIR 1
#define BLANC 2

int compter_couleur(int mat[N][N],int couleur);

int retourner(int mat[N][N], int couleur, int lig, int col);

int coup_possible(int mat[N][N], int couleur, int lig, int col);

int peut_jouer(int mat[N][N], int couleur);

#endif
