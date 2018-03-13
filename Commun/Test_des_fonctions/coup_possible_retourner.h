#include <stdio.h>
#include <stdlib.h>

#include "define.h"

void copie(char mat[N][N], char mat2[N][N]);

int retourner(char mat[N][N], char couleur, int lig, int col);

int coup_possible(char mat[N][N], char couleur, int lig, int col);