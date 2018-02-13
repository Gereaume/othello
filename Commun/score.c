#include <stdio.h>
#include <stdlib.h>

#include "score.h"
#include "Gestion_matrice_/jouer.h"

#define N 8

/********************************************************************************************
Prend en compte la matrice et la couleur du joueur, puis renvoie le nb de pions de sa couleur
********************************************************************************************/

int score(char mat[N][N], char couleur){

	int i, j;
	int cpt = 0;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(mat[i][j] == couleur){
				cpt++;
			}
		}
	}
	return cpt;
}
