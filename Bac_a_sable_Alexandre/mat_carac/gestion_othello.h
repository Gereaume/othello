#ifndef __GESTION_OTHELLO_H__
#define __GESTION_OTHELLO_H__
#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"
#include "define.h"

#define NOIR 'n'
#define BLANC 'b'

int compter_couleur(char mat[N][N],char couleur);

int retourner(char mat[N][N], char couleur, int lig, int col);

int coup_possible(char mat[N][N], char couleur, int lig, int col);

int peut_jouer(char mat[N][N], char couleur);

#endif
