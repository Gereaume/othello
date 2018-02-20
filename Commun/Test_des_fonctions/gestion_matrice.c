,,,,,,,,,,/**
*\file gestion_matrice.c
*\brief Ce fichier contient des fonctions permettant la gestion de matrice tel que initialisé une matrice, lire une matrice, ecrire dans une matrice, compter le nombre d'elem dans une matrice, verifier si on est dans la matrice
*\author Jérôme Le Querrec
*\version 1.0
*\date 01 fevrier 2018
**/

/* Include des bibliothèques c de base */
#include <stdio.h>
#include <stdlib.h>

/* Include du .h correspondant a ce fichier */
#include "gestion_matrice.h"

#include "define.h" 									/*define.h defini la taille de la matrice	*/

/**
*\brief La fonction init_mat permet d'initialiser la matrice
**/
void init_mat(char mat[N][N])
{
	
	int lig,col;									/** Declaration des variables a incrementer	**/

	for(lig=0;lig<N;lig++)								/** Incrementation de ligne	**/
	{
		for(col=0;col<N;col++)							/** Incrementation de colonne	**/
		{
			mat[lig][col]='*';						/** On place des points dans chaque case	**/
			if((lig == 3 && col == 3) || (lig == 4 && col == 4))		/** Sauf les cases ou nous plaçons les pions du départ	**/
				mat[lig][col] = 'b';
			else if((lig == 3 && col == 4) || (lig == 4 && col == 3))
				mat[lig][col] = 'n';
		}
	}
}
/**
*\brief La fonction lire_mat permet de lire la matrice
**/

void lire_mat(char mat[N][N])
{	
	int lig,col;									/** Declaration des variables a incrementer	**/
	printf("\t X |0|1|2|3|4|5|6|7|");	
	for(lig=0;lig<N;lig++)								/** Incrementation de ligne	**/
	{
		printf("\n\t %i |",lig);
		for(col=0;col<N;col++)							/** Incrementation de colonne	**/
		{
			printf("%c|",mat[lig][col]);					/** Affichage de la matrice	**/
		}
		
	}
	printf("\n\n");
}
/**
*\brief La fonction ecrire_mat permet d'ecrire dans une matrice a une case donnée
**/

void ecrire_mat(char mat[N][N],char symbole,int lig,int col)
{	
	mat[lig][col] = symbole;							/** On met le symbole au coordonnées souhaité	**/
	system("clear");								/** On nettoie l'affichage du terminal pour ne pu voir les coordonnées précedentes	**/
}

/**
*\brief La fonction compter_elem permet de compter le nombre d'element elem sur le plateau
**/

int compter_elem(char mat[N][N],char elem)
{
	int cpt_elem = 0,lig,col;								/** Declaration des variables a incrementer	**/

	for(lig=0;lig<N;lig++)								/** Incrementation de ligne	**/
	{
		for(col=0;col<N;col++)							/** Incrementation de colonne	**/
		{
			if(mat[lig][col] == elem)
				cpt_elem++;						/** Incrementation du compteur si la case contient l'elem	**/
		}
	}
	return(cpt_elem);								/** Retourne la valeur de cpt_elem	**/
}

/**
*\brief La fonction hors_mat nous permet de voir si l'on est en dehors de la matrice
**/

int hors_mat(int lig,int col)
{
	if((lig < 0 || lig > 7) || (col < 0 || col > 7))				/**  ce test nous permet de verifier si l'on  est en dehors de la matrice si c'est le cas on return 1	**/
		return 1;
	else										/** Autrement on return 0	**/
		return 0;
} 
