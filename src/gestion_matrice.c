/**
*\file gestion_matrice.c
*\brief Ce fichier contient des fonctions permettant la gestion de matrice
*\author Alexandre Laloy / Jérôme Le Querrec
*\version 1.1
*\date 01 fevrier 2018
**/

#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"
#include "gestion_othello.h"
#include "define.h"



/**
*\brief La fonction init_mat permet d'initialiser la matrice
**/
void init_mat(int mat[N][N]){
	
	int lig, col;																		/** Declaration des variables a incrementer	**/

	for(lig=0;lig<N;lig++)																/** Incrementation de ligne	**/
	{
		for(col=0;col<N;col++)															/** Incrementation de colonne **/
		{
			mat[lig][col] = 0;														/** On place des étoile dans chaque case **/
			if((lig == (N/2)-1 && col == (N/2)-1) || (lig == N/2 && col == N/2))		/** Sauf les cases ou nous plaçons les pions du départ **/
				mat[lig][col] = BLANC;
			else if((lig == (N/2)-1 && col == N/2) || (lig == N/2 && col == (N/2)-1))
				mat[lig][col] = NOIR;
		}
	}
}



/**
*\brief La fonction lire_mat permet de lire la matrice
**/
void lire_mat(int mat[N][N]){	
	
	int lig, col;								/** Declaration des variables a incrementer	**/

	printf("\n\t + |");
	for(col=0;col<N;col++){						/** Sert à indiquer les numéros de colonnes **/
		if(col<=9){
			printf(" %i |", col);
		}
		else{
			printf("%i |", col);	
		}
	}
	
	for(lig=0;lig<N;lig++){						/** Incrementation de ligne	**/
		if(lig<=9){								/** Sert à indiquer les numéros de lignes **/
			printf("\n\t %i |", lig);
		}
		else{
			printf("\n\t%i |", lig);
		}
		
		for(col=0;col<N;col++){					
			printf(" %i |", mat[lig][col]);		/** Affichage de la matrice **/
		}
	}
	printf("\n\n");
}



/**
*\brief La fonction ecrire_mat permet d'ecrire dans une matrice a une case donnée
**/
void ecrire_mat(int mat[N][N],int elem,int lig,int col){	

	mat[lig][col] = elem;		/** On met l'élément au coordonnées souhaité **/
}



/**
*\brief La fonction hors_mat nous permet de voir si l'on est en dehors de la matrice
**/
int hors_mat(int lig,int col){

	if( lig < 0 || lig > (N-1) || col < 0 || col > (N-1) )		/** Si on est en dehors de la matrice, on return 1 **/
		return 1;
	else														/** Autrement on return 0 **/
		return 0;
} 



/**
*\brief la fonction copie permet de copier une matrice dans une autre
**/
void copie(int mat[N][N], int mat2[N][N]){

	int lig, col;									/** Déclaration des variables **/

	for(lig=0;lig<N;lig++){							/** Incrémentation de ligne	**/
		for(col=0;col<N;col++){						/** Incrémentation de colonne **/
			mat2[lig][col] = mat[lig][col];			/** On copie le contenue de la première matrice dans la seconde	**/
		}
	}
}



/*
int ecrire_mat_clic(mat[N][N])
{
	int lig = 0;
	int col = 0;
	coordonnes(lig,col)
	lig /= 100;
	col /= 100;
	if(coupPoss(mat,mat2,blanc,lig,col) == 0))
		return 0;
	else
	{
		mat[lig][col] = ;
		return 1;
	}
}
*/