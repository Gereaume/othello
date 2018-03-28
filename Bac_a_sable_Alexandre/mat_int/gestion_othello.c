/**
*\file gestion_othello.c
*\brief Ce fichier contient des fonctions permettant la gestion du jeu othello
*\author Alexandre Laloy
*\version 1.1
*\date 28 mars 2018
**/

#include <stdio.h>
#include <stdlib.h>

#include "gestion_matrice.h"
#include "gestion_othello.h"
#include "define.h"

#define NOIR 1
#define BLANC 2



/**
*\brief La fonction compter_elem permet de compter le nombre d'element elem sur le plateau
**/
int compter_couleur(int mat[N][N],int couleur){

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
\brief Renvoie le nombre de pions retourné, si aucun retourné, return 0
**/
int retourner(int mat[N][N], int couleur, int lig, int col){

	int i, j, cpt,x;
	int cpt_final = 0;


/*********************************************************************************
Il y a 8 fois ce traitement pour les 8 directions possibles pour retourner un pion
*********************************************************************************/

	/***************
	En haut à gauche
	***************/
	if(mat[lig-1][col-1] != 0 && mat[lig-1][col-1] != couleur){				/** Si la case est de la couleur de l'adversaire **/
		i = lig-1;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){	/** Tant que la case est de la couleur de l'adversaire **/
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
	if(mat[lig-1][col] != 0 && mat[lig-1][col] != couleur){
		i = lig-1;
		j = col;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){
			
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
	if(mat[lig-1][col+1] != 0 && mat[lig-1][col+1] != couleur){
		i = lig-1;
		j = col+1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){
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
	if(mat[lig][col-1] != 0 && mat[lig][col-1] != couleur){
		i = lig;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){
			
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
	if(mat[lig][col+1] != 0 && mat[lig][col+1] != couleur){
		
		i = lig;
		j = col+1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){
			
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
	if(mat[lig+1][col-1] != 0 && mat[lig+1][col-1] != couleur){
		i = lig+1;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){
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
	if(mat[lig+1][col] != 0 && mat[lig+1][col] != couleur){
		i = lig+1;
		j = col;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){
			
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
	if(mat[lig+1][col+1] != 0 && mat[lig+1][col+1] != couleur){
		i = lig+1;
		j = col+1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != 0 && !hors_mat(i, j) ){
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
int coup_possible(int mat[N][N], int couleur, int lig, int col){

	int mat2[N][N];
	int nb_pions_ret;
	copie(mat, mat2);											/** copie contenu de mat dans mat2	**/

	if((mat[lig][col] == 0) && !hors_mat(lig,col)){			/** si les coordonnées correspondent à une zone vide **/
		
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
int peut_jouer(int mat[N][N], int couleur){

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
