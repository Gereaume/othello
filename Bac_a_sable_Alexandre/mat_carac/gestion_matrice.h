#ifndef __GESTION_MATRICE_H__
#define __GESTION_MATRICE_H__
#include <stdio.h>
#include <stdlib.h>

#include "define.h"

void init_mat(char mat[N][N]);

void lire_mat(char mat[N][N]);

void ecrire_mat(char mat[N][N],char couleur,int lig,int col);

int compter_couleur(char mat[N][N],char couleur);

int hors_mat(int lig,int col);

void copie(char mat[N][N], char mat2[N][N]);

int retourner(char mat[N][N], char couleur, int lig, int col);

int coup_possible(char mat[N][N], char couleur, int lig, int col);

int peut_jouer(char mat[N][N], char couleur);

#endif
