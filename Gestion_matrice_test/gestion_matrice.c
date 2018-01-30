#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"

#define N 8 // defini la taille de la matrice

/*********************************************
Cette fonction permet d'initialiser la matrice
**********************************************/

void init_mat(char mat[N][N])
{
	
	int lig,col;//Declaration des variables a incrementer
	for(lig=0;lig<N;lig++)//Incrementation de ligne
	{
		for(col=0;col<N;col++)//Incrementation de colonne
		{
			mat[lig][col]='*';//On place des points dans chaque case
			if((lig == 3 && col == 3) || (lig == 4 && col == 4))//Sauf les cases ou nous plaçons les pions du départ
				mat[lig][col] = 'b';
			else if((lig == 3 && col == 4) || (lig == 4 && col == 3))
				mat[lig][col] = 'n';
		}
	}
}
/****************************************
Cette fonction permet de lire la matrice
*****************************************/

void lire_mat(char mat[N][N])
{
	int lig,col;//Declaration des variables a incrementer
	printf("|");
	for(lig=0;lig<N;lig++)//Incrementation de ligne
	{
		for(col=0;col<N;col++)//Incrementation de colonne
		{
			printf("%c|",mat[lig][col]);//Affichage de la matrice
		}
		printf("\n|");
	}
}
/*****************************************************************
Cette fonction permet d'ecrire dans une matrice a une case donnée
*****************************************************************/
void ecrire_mat(char mat[N][N],int lig,int col,char symbole)
{
	mat[lig][col] = symbole;
}
