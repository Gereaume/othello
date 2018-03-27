/**
*\file min_max_ordi.c
*\brief Ce fichier contient la fonction permettant à l'ordinateur de jouer
*\author Alexandre Laloy
*\version 1.0
*\date 16 mars 2018
**/

#include <stdio.h>
#include <stdlib.h>

#include "min_max_ordi.h"
#include "gestion_matrice.h"
#include "define.h"



/**
*\brief Cette fonction envoie une valeur par rapport au coup joué, plus le coup est interessant, plus il rapporte de point(s)
**/
int fonc_eval(char mat[N][N], char couleur){

	int i, j, val_calcul = 0, cpt_final = 0;
	int haut_G = 0, haut_D = 0, bas_G = 0, bas_D = 0;

		/** La mobilité : chaque case jouable rapporte des pts **/
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(coup_possible(mat, couleur, i, j) == 1)
				cpt_final += 2;
		}
	}

		/** Le matériel : la différence de pions rapporte des pts **/
	val_calcul += compter_couleur(mat, couleur);
	val_calcul -= compter_couleur(mat, couleur==BLANC?NOIR:BLANC);

	cpt_final += val_calcul;



		/** La force : la possession de certaines cases rapporte des pts **/
		/** Pts pour les coins du plateau **/
	if(mat[0][0] == couleur){
		haut_G = 1;
		cpt_final += 500;
	}
	if(mat[N-1][N-1] == couleur){
		bas_D = 1;
		cpt_final += 500;
	}
	if(mat[0][N-1] == couleur){
		haut_D = 1;
		cpt_final += 500;
	}
	if(mat[N-1][0] == couleur){
		bas_G = 1;
		cpt_final += 500;
	}

		/** Pts pour les cotés du plateau **/
	if(haut_G == 1){
		i = 1;
		j = 1;
		while(mat[0][j] == couleur && j < N-1){
			cpt_final += 250;
			j++;
		}
		while(mat[i][0] == couleur && i < N-1){
			cpt_final += 250;
			i++;
		}	
	}
	else{
		i = 1;
		j = 1;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j < N-1){
			if(mat[0][j] == couleur)
				cpt_final -= 150;
			j++;
		}
		while(i < N-1){
			if(mat[i][0] == couleur)
				cpt_final -= 150;
			i++;
		}
	}
	if(bas_D == 1){
		i = N-2;
		j = N-2;
		while(mat[N-1][j] == couleur && j > 0){
			cpt_final += 250;
			j--;
		}
		while(mat[i][N-1] == couleur && i > 0){
			cpt_final += 250;
			i--;
		}	
	}
	else{
		i = N-2;
		j = N-2;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j > 0){
			if(mat[N-1][j] == couleur)
				cpt_final -= 150;
			j--;
		}
		while(i > 0){
			if(mat[i][N-1] == couleur)
				cpt_final += 150;
			i--;
		}
	}
	if(haut_D == 1){
		i = 1;
		j = N-2;
		while(mat[0][j] == couleur && j > 0){
			cpt_final += 250;
			j--;
		}
		while(mat[i][N-1] == couleur && i < N-1){
			cpt_final += 250;
			i++;
		}	
	}
	else{
		i = 1;
		j = N-2;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j > 0){
			if(mat[0][j] == couleur)
				cpt_final -= 150;
			j--;
		}
		while(i < N-1){
			if(mat[i][N-1] == couleur)
				cpt_final -= 150;
			i++;
		}
	}
	if(bas_G == 1){
		i = N-2;
		j = 1;
		while(mat[N-1][j] == couleur && j < N-1){
			cpt_final += 250;
			j++;
		}
		while(mat[i][0] == couleur && i > 0){
			cpt_final += 250;
			i--;
		}	
	}
	else{
		i = N-2;
		j = 1;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j < N-1){
			if(mat[N-1][j] == couleur)
				cpt_final -= 150;
			j++;
		}
		while(i > 0){
			if(mat[i][0] == couleur)
				cpt_final -= 150;
			i--;
		}
	}

		/** Pts pour le centre du plateau **/
	if(mat[N/2][N/2] == couleur)
		cpt_final += 16;
	if(mat[(N/2)-1][N/2] == couleur)
		cpt_final += 16;
	if(mat[N/2][(N/2)-1] == couleur)
		cpt_final += 16;
	if(mat[(N/2)-1][(N/2)-1] == couleur)
		cpt_final += 16;

		/** On renvoie le compteur final **/
	return cpt_final;
}


/**
*\brief Cette fonction simule le tour du joueur, et renvoie la valeur la plus petite calculée (elle appelle la fonction ordi)
**/
int joueur(char mat[N][N], char couleur, int nb_coup_prevu, int alpha, int beta){

	int lig, col, val_ret;
	char mat2[N][N];
	int val_min = 99999;

	if(nb_coup_prevu == 1){									/** Si on est arrivé à la profondeur voulue, on renvoie la valeur de fonc_eval **/
		return fonc_eval(mat, couleur);
	}
								
	for(lig=0;lig<N;lig++){									/** On fait toutes les possibilitées **/
		for(col=0;col<N;col++){
								
			if(coup_possible(mat,couleur,lig,col) != 0){	/** Si le coup est possible **/
								
				copie(mat, mat2);							/** On effectue les calculs sur une copie de mat **/
															/** On effectue le placement du pion et on retourne le(s) pion(s) à retourner **/
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);
			
															/** On regarde un cran plus bas **/
				val_ret = ordi(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, alpha, beta);
				if(val_ret < val_min) 						/** On garde la valeur la plus petite **/
					val_min=val_ret;
				
			}
															/** On passe à la case suivante **/
		}
	}
	return val_min;											/** On renvoie la valeur minimum **/
}



/**
*\brief Cette fonction simule le tour de l'ordinateur, et renvoie la valeur la plus grande calculée (elle appelle la fonction joueur)
**/
int ordi(char mat[N][N], char couleur, int nb_coup_prevu, int alpha, int beta){

	int lig, col, val_ret;
	int val_max = -99999;
	char mat2[N][N];

	if(nb_coup_prevu == 1){									/** Si on est arrivé à la profondeur voulue, on renvoie la valeur de fonc_eval **/
		return fonc_eval(mat, couleur);
	}
	
	for(lig=0;lig<N;lig++){									/** On fait toutes les possibilitées **/
		for(col=0;col<N;col++){
			
			if(coup_possible(mat,couleur,lig,col) != 0){	/** Si le coup est possible **/
				
				copie(mat, mat2);							/** On effectue les calculs sur une copie de mat **/
															/** On effectue le placement du pion et on retourne le(s) pion(s) à retourner **/
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);

															/** On regarde un cran plus bas **/
				val_ret = joueur(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, alpha, beta);
				if(val_ret > val_max) 						/** On garde la valeur la plus grande **/
					val_max=val_ret;
				
			}
															/** On passe à la case suivante **/
		}
	}
	return val_max;											/** On renvoie la valeur maximum **/
}



/**
*\brief Cette fonction simule le tour de l'ordinateur, et permet d'avoir les coordonnées du prochain coup de l'ordinateur
**/
void tour_ordi(char mat[N][N], char couleur, int nb_coup_prevu, int *px, int *py){

	int lig, col, val_ret, lig_max = -1, col_max = -1;
	int val_max = -99999;
	char mat2[N][N];
	
	for(lig=0;lig<N;lig++){									/** On fait toutes les possibilitées **/
		for(col=0;col<N;col++){
			
			if(coup_possible(mat,couleur,lig,col) != 0){	/** Si le coup est possible **/
				
				
				copie(mat, mat2);							/** On effectue les calculs sur une copie de mat **/
															/** On effectue le placement du pion et on retourne le(s) pion(s) à retourner **/
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);

				if(nb_coup_prevu == 1){						/** Si on est arrivé à la profondeur voulue, on garde la valeur de fonc_eval **/
					val_ret = fonc_eval(mat, couleur);
				}
				else{										/** Sinon, on regarde un cran plus bas **/
					val_ret = joueur(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, 999, -999);
				}
				
				if(val_ret > val_max) {						/** On garde la valeur la plus grande **/
					val_max=val_ret;
					lig_max=lig;
					col_max=col;
				}
				
			}
															/** On passe à la case suivante **/
		}
	}
	printf("\n\n\tVal de lig_max %i et val de col_max %i\n\n", lig_max, col_max);
	if(lig_max == -1 || col_max == -1){
		printf("\n\n\tErreur - lig_max ou col_max n'a pas pris de valeur\n\n");
	}
	else{
		*px=lig_max;										/** On met les coordonnées du prochain coup dans des pointeurs **/
		*py=col_max;
	}
	
}

