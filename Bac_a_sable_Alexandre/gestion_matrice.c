/**
*\file gestion_matrice.c
*\brief Ce fichier contient des fonctions permettant la gestion de matrice tel que initialisé une matrice, lire une matrice, ecrire dans une matrice, compter le nombre d'elem dans une matrice, verifier si on est dans la matrice et copier une matrice dans une autre
*\author Jérôme Le Querrec
*\version 1.1
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
			if((lig == (N/2)-1 && col == (N/2)-1) || (lig == N/2 && col == N/2))		/** Sauf les cases ou nous plaçons les pions du départ	**/
				mat[lig][col] = BLANC;
			else if((lig == (N/2)-1 && col == N/2) || (lig == N/2 && col == (N/2)-1))
				mat[lig][col] = NOIR;
		}
	}
}



/**
*\brief La fonction lire_mat permet de lire la matrice
**/
void lire_mat(char mat[N][N])
{	
	int lig,col;									/** Declaration des variables a incrementer	**/
	printf("\n\t + |");
	for(int i= 0;i<N+8;i++)
	{
		if(i<=9)
		{
			printf(" %i |",i);
		}
		else
		{
			printf("%i |",i);	
		}
	}
	
	for(lig=0;lig<N+8;lig++)								/** Incrementation de ligne	**/
	{
		if(lig<=9)
		{
			printf("\n\t %i |",lig);
		}
		else
		{
			printf("\n\t%i |",lig);
		}
		
		for(col=0;col<N+8;col++)							/** Incrementation de colonne	**/
		{
			printf(" %c |",mat[lig][col]);					/** Affichage de la matrice	**/
		}
		
	}
	printf("\n\n");
}

/**
*\brief La fonction ecrire_mat permet d'ecrire dans une matrice a une case donnée
**/
void ecrire_mat(char mat[N][N],char couleur,int lig,int col)
{	
	mat[lig][col] = couleur;							/** On met la couleur au coordonnées souhaité	**/
}

/**
*\brief La fonction compter_elem permet de compter le nombre d'element elem sur le plateau
**/

int compter_elem(char mat[N][N],char couleur)
{
	int cpt_elem = 0,lig,col;							/** Declaration des variables a incrementer	**/

	for(lig=0;lig<N;lig++)								/** Incrementation de ligne	**/
	{
		for(col=0;col<N;col++)							/** Incrementation de colonne	**/
		{
			if(mat[lig][col] == couleur)
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
	if( lig < 0 || lig > (N-1) || col < 0 || col > (N-1) )				/** Ce test nous permet de verifier si l'on  est en dehors de la matrice si c'est le cas on return 1	**/
		return 1;
	else										/** Autrement on return 0	**/
		return 0;
} 

/**
*\brief la fonction copie permet de copier une matrice dans une autre
**/
void copie(char mat[N][N], char mat2[N][N])
{
	int lig, col;									/** Déclaration des variables	**/
	for(lig=0;lig<N;lig++)								/** Incrémentation de ligne	**/
	{
		for(col=0;col<N;col++)							/** Incrémentation de colonne	**/
		{
			mat2[lig][col] = mat[lig][col];					/** On copie le contenue de la première matrice dans la seconde	**/
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