#include <stdio.h>
#include <stdlib.h>


#include "coupPossible.h"


/******************************************
Renvoie 1 si le coup est possible, sinon 0
******************************************/

int coupPoss(char mat[N][N], char mat2[N][N], char couleur, int lig, int col){

	copie(mat, mat2); // copie contenu de mat dans mat2

	if(mat[lig][col] == '*'){ // si les coordonnées correspondent à une zone vide
		return(retourner(mat2, couleur)); // si le pion posé retourne au moins 1 pion
	}
	else{
		return 0; // sinon faux
	}
}