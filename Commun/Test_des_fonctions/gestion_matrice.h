#include <stdlib.h>
#include <stdio.h>

#include "define.h"

void init_mat(char mat[N][N]);

void lire_mat(char mat[N][N]);

void ecrire_mat(char mat[N][N],char symbole,int lig,int col);

int compter_elem(char mat[N][N],char elem);

int hors_mat(int lig,int col);

void copie(char mat[N][N], char mat2[N][N]);