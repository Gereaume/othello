#include <stdlib.h>
#include <stdio.h>

#define N 8

void init_mat(char mat[N][N]);

void lire_mat(char mat[N][N]);

void ecrire_mat(char mat[N][N],int lig,int col,char symbole);

void gestion_mat(char mat[N][N],void(*operation)(char mat[N][N]));