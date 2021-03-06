/**
*\file coupPoss.c
*\brief Ce fichier contient des fonctions permettant de savoir si un coup est possible et cb de pions sont retournés
*\author Alexandre Laloy
*\version 1.0
*\date 20 fevrier 2018
**/



#include <stdio.h>
#include <stdlib.h>


#include "coup_possible_retourner.h"
#include "gestion_matrice.h"
#include "define.h"


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
	if(mat[lig-1][col-1] != '*' && mat[lig-1][col-1] != couleur){	/** Si la case est de la couleur de l'adversaire **/
		i = lig-1;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){	/** Tant que la case est de la couleur de l'adversaire **/
			i--;
			j--;
			cpt++;
		}
		if(mat[i][j] == couleur){	/** Si la case est de la couleur du joueur, alors on retourne les pions précédemment compté **/
			i = lig-1;
			j = col-1;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				i--;
				j--;
				cpt_final++;	/** On incrémente le compteur final **/
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
		if(mat[i][j] == couleur){
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
		if(mat[i][j] == couleur){
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
		if(mat[i][j] == couleur){
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
		if(mat[i][j] == couleur){
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
		if(mat[i][j] == couleur){
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
		if(mat[i][j] == couleur){
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
		if(mat[i][j] == couleur){
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

	return cpt_final;	/** On renvoie le nombre de pions retournés **/
}


/**
*\brief La fonction coup_possible nous renvoie 1 si le coup est possible et renvoie 0 si le coup n'est pas possible
**/
int coup_possible(char mat[N][N], char couleur, int lig, int col){
	char mat2[N][N];
	int nb_pions_ret;
	copie(mat, mat2);	/** copie contenu de mat dans mat2	**/

	if((mat[lig][col] == '*') && !hors_mat(lig,col)){ // si les coordonnées correspondent à une zone vide
		
		nb_pions_ret = retourner(mat2, couleur, lig, col); // si le pion posé retourne au moins 1 pion
		
		if(nb_pions_ret != 0){
			return nb_pions_ret;
		}
		else{
			return 0;
		}
	}
	else{
		return 0; // sinon faux
	}
}



int peut_jouer(char mat[N][N], char couleur){
	int lig, col;

	for(lig=0;lig<N;lig++){
		for(col=0;col<N;col++){
			if(coup_possible(mat,couleur,lig,col) != 0){
				return 1;
			}
		}
	}
	return 0;
}