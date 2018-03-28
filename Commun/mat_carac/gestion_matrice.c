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
#include "define.h"



/**
*\brief La fonction init_mat permet d'initialiser la matrice
**/
void init_mat(char mat[N][N]){
	
	int lig, col;																		/** Declaration des variables a incrementer	**/

	for(lig=0;lig<N;lig++)																/** Incrementation de ligne	**/
	{
		for(col=0;col<N;col++)															/** Incrementation de colonne **/
		{
			mat[lig][col] = '*';														/** On place des étoile dans chaque case **/
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
void lire_mat(char mat[N][N]){	
	
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
			printf(" %c |", mat[lig][col]);		/** Affichage de la matrice **/
		}
	}
	printf("\n\n");
}



/**
*\brief La fonction ecrire_mat permet d'ecrire dans une matrice a une case donnée
**/
void ecrire_mat(char mat[N][N],char couleur,int lig,int col){	

	mat[lig][col] = couleur;		/** On met la couleur au coordonnées souhaité **/
}



/**
*\brief La fonction compter_elem permet de compter le nombre d'element elem sur le plateau
**/
int compter_couleur(char mat[N][N],char couleur){

	int cpt_pions = 0,lig,col;						/** Declaration des variables a incrementer	**/

	for(lig=0;lig<N;lig++){							/** Incrementation de ligne	**/
		for(col=0;col<N;col++){						/** Incrementation de colonne **/
			if(mat[lig][col] == couleur)
				cpt_pions++;						/** Incrementation du compteur si la case contient la couleur **/
		}
	}
	return cpt_pions;								/** Retourne la valeur de cpt_pions	**/
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
void copie(char mat[N][N], char mat2[N][N]){

	int lig, col;									/** Déclaration des variables **/

	for(lig=0;lig<N;lig++){							/** Incrémentation de ligne	**/
		for(col=0;col<N;col++){						/** Incrémentation de colonne **/
			mat2[lig][col] = mat[lig][col];			/** On copie le contenue de la première matrice dans la seconde	**/
		}
	}
}



/**
\brief Renvoie le nombre de pions retourné, si aucun retourné, return 0
**/
int retourner(char mat[N][N], char couleur, int lig, int col){

	int i, j, cpt,x;
	int cpt_final = 0;


/*********************************************************************************
Il y a 8 fois ce traitement pour les 8 directions possibles pour retourner un pion
*********************************************************************************/

	/***************
	En haut à gauche
	***************/
	if(mat[lig-1][col-1] != '*' && mat[lig-1][col-1] != couleur){				/** Si la case est de la couleur de l'adversaire **/
		i = lig-1;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){	/** Tant que la case est de la couleur de l'adversaire **/
			i--;
			j--;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){							/** Si la case est de la couleur du joueur, alors on retourne les pions précédemment compté **/
			i = lig-1;
			j = col-1;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				i--;
				j--;
				cpt_final++;													/** On incrémente le compteur final **/
			}
		}
	}

	/******
	En haut
	******/
	if(mat[lig-1][col] != '*' && mat[lig-1][col] != couleur){
		i = lig-1;
		j = col;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			
			i--;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){
			i = lig-1;
			j = col;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				i--;
				cpt_final++;
			}
		}
	}

	/***************
	En haut à droite
	***************/
	if(mat[lig-1][col+1] != '*' && mat[lig-1][col+1] != couleur){
		i = lig-1;
		j = col+1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			i--;
			j++;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){
			i = lig-1;
			j = col+1;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				i--;
				j++;
				cpt_final++;
			}
		}
	}

	/*******
	A gauche
	*******/
	if(mat[lig][col-1] != '*' && mat[lig][col-1] != couleur){
		i = lig;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			
			j--;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){
			i = lig;
			j = col-1;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				
				j--;
				cpt_final++;
			}
		}
	}

	/*******
	A droite
	*******/
	if(mat[lig][col+1] != '*' && mat[lig][col+1] != couleur){
		
		i = lig;
		j = col+1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			
			j++;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){
			
			i = lig;
			j = col+1;
			for(x=0;x<cpt;x++){
				
				mat[i][j] = couleur;
				
				j++;
				cpt_final++;
			}
		}
	}

	/**************
	En bas à gauche
	**************/
	if(mat[lig+1][col-1] != '*' && mat[lig+1][col-1] != couleur){
		i = lig+1;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			i++;
			j--;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){
			i = lig+1;
			j = col-1;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				i++;
				j--;
				cpt_final++;
			}
		}
	}

	/*****
	En bas
	*****/
	if(mat[lig+1][col] != '*' && mat[lig+1][col] != couleur){
		i = lig+1;
		j = col;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			
			i++;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){
			i = lig+1;
			j = col;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				
				i++;
				cpt_final++;
			}
		}
	}

	/**************
	En bas à droite
	**************/
	if(mat[lig+1][col+1] != '*' && mat[lig+1][col+1] != couleur){
		i = lig+1;
		j = col+1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			i++;
			j++;
			cpt++;
		}
		if(mat[i][j] == couleur && !hors_mat(i, j)){
			i = lig+1;
			j = col+1;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				i++;
				j++;
				cpt_final++;
			}
		}
	}

	return cpt_final;		/** On renvoie le nombre de pions retournés **/
}



/**
*\brief La fonction coup_possible nous renvoie 1 si le coup est possible et renvoie 0 si le coup n'est pas possible
**/
int coup_possible(char mat[N][N], char couleur, int lig, int col){

	char mat2[N][N];
	int nb_pions_ret;
	copie(mat, mat2);											/** copie contenu de mat dans mat2	**/

	if((mat[lig][col] == '*') && !hors_mat(lig,col)){			/** si les coordonnées correspondent à une zone vide **/
		
		nb_pions_ret = retourner(mat2, couleur, lig, col);		
		
		if(nb_pions_ret != 0){									/** si le pion posé retourne au moins 1 pion **/
			return nb_pions_ret;								/** on renvoie le nombre de pions retourné(s) **/
		}
		else{													/** sinon on renvoie 0 **/
			return 0;
		}
	}
	else{
		return 0;
	}
}


/**
*\brief La fonction peut_jouer nous renvoie 1 si le joueur peut jouer et renvoie 0 s'il ne peut pas
**/
int peut_jouer(char mat[N][N], char couleur){

	int lig, col;

	for(lig=0;lig<N;lig++){									/** on teste toutes les cases **/
		for(col=0;col<N;col++){
			if(coup_possible(mat,couleur,lig,col) != 0){	/** si il y a au moins 1 coup possible **/
				return 1;									/** on renvoie 1 **/
			}
		}
	}
	return 0;												/** sinon 0 **/
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