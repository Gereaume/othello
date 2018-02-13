#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"

#include "define.h" // defini la taille de la matrice

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
	printf("\n\n");
}
/*****************************************************************
Cette fonction permet d'ecrire dans une matrice a une case donnée
*****************************************************************/
void ecrire_mat(char mat[N][N],char symbole,int lig,int col)
{	
	mat[lig-1][col-1] = symbole;//On decremente les coordonnées saisie par le joueur pour que cela corresponde visuelement a l'affichage
	system("clear");//On nettoie l'affichage du terminal pour ne pu voir les coordonnées précedentes
}

/*****************************************************************
Cette fonction permet de compter le nombre d'element elem sur le plateau
*****************************************************************/

int compter_elem(char mat[N][N],char elem)
{
	int cpt_elem,lig,col;//Declaration des variables a incrementer

	for(lig=0;lig<N;lig++)//Incrementation de ligne
	{
		for(col=0;col<N;col++)//Incrementation de colonne
		{
			if(mat[lig][col] == elem)
				cpt_elem++;//Incrementation du compteur si la case contient l'elem
		}
	}
	return(cpt_elem);//Retourne la valeur de cpt_elem
}