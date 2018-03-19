#ifndef __COUP_POSSIBLE_RETOURNER_H__
#define __COUP_POSSIBLE_RETOURNER_H__
#include <stdio.h>
#include <stdlib.h>

#include "define.h"

int retourner(char mat[N][N], char couleur, int lig, int col);

int coup_possible(char mat[N][N], char couleur, int lig, int col);

int peut_jouer(char mat[N][N], char couleur);
#endif