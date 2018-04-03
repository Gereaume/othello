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
#include "gestion_othello.h"
#include "define.h"



/**
*\brief Cette fonction envoie une valeur par rapport au coup joué, plus le coup est interessant, plus il rapporte de point(s)
**/
int fonc_eval(char mat[N][N], char couleur){

	int i, j, val_calcul = 0, cpt_final = 0;
	int haut_G = 0, haut_D = 0, bas_G = 0, bas_D = 0;

	/* Valeur pour la mobilité */
	int val_peut_jouer = 2;
	/* Valeur pour le matériel */
	int val_pion = 3;
	/* Valeur pour la force */
	int val_coin = 40;
	int val_bord = 13;
	int val_adj_coin = 30;
	int val_centre = 4;

		/** La mobilité : chaque case jouable rapporte des pts **/
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(coup_possible(mat, couleur, i, j) == 1)
				cpt_final += val_peut_jouer;
		}
	}

		/** Le matériel : la différence de pions rapporte des pts **/
	val_calcul += (val_pion * compter_couleur(mat, couleur));
	val_calcul -= (val_pion * compter_couleur(mat, couleur==BLANC?NOIR:BLANC));

	cpt_final += val_calcul;



		/** La force : la possession de certaines cases rapporte des pts **/
		/** Pts pour les coins du plateau **/
	if(mat[0][0] == couleur){
		haut_G = 1;
		cpt_final += val_coin;
	}
	else if(mat[0][0] == (couleur==BLANC?NOIR:BLANC)){
		haut_G = -1;
		cpt_final -= val_coin;
	}
	if(mat[N-1][N-1] == couleur){
		bas_D = 1;
		cpt_final += val_coin;
	}
	else if(mat[N-1][N-1] == (couleur==BLANC?NOIR:BLANC)){
		bas_D = -1;
		cpt_final -= val_coin;
	}
	if(mat[0][N-1] == couleur){
		haut_D = 1;
		cpt_final += val_coin;
	}
	else if(mat[0][N-1] == (couleur==BLANC?NOIR:BLANC)){
		haut_D = -1;
		cpt_final -= val_coin;
	}
	if(mat[N-1][0] == couleur){
		bas_G = 1;
		cpt_final += val_coin;
	}
	else if(mat[N-1][0] == (couleur==BLANC?NOIR:BLANC)){
		bas_G = -1;
		cpt_final -= val_coin;
	}

		/** Pts pour les cotés du plateau **/
	if(haut_G == 1){
		i = 1;
		j = 1;
		while(mat[0][j] == couleur && j < (N/2)-1){
			cpt_final += val_bord;
			j++;
		}
		while(mat[i][0] == couleur && i < (N/2)-1){
			cpt_final += val_bord;
			i++;
		}	
	}
	else if(haut_G == -1){
		i = 1;
		j = 1;
		while(mat[0][j] == (couleur==BLANC?NOIR:BLANC) && j < (N/2)-1){
			cpt_final -= val_bord;
			j++;
		}
		while(mat[i][0] == (couleur==BLANC?NOIR:BLANC) && i < (N/2)-1){
			cpt_final -= val_bord;
			i++;
		}
	}
	else{
		if(mat[1][0] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[0][1] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[1][1] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[2][0] == couleur)
			cpt_final += val_bord;
		if(mat[0][2] == couleur)
			cpt_final += val_bord;
	}



	if(bas_D == 1){
		i = N-2;
		j = N-2;
		while(mat[N-1][j] == couleur && j > (N/2)-1){
			cpt_final += val_bord;
			j--;
		}
		while(mat[i][N-1] == couleur && i > (N/2)-1){
			cpt_final += val_bord;
			i--;
		}	
	}
	else if(bas_D == -1){
		i = N-2;
		j = N-2;
		while(mat[N-1][j] == (couleur==BLANC?NOIR:BLANC) && j > (N/2)-1){
			cpt_final -= val_bord;
			j--;
		}
		while(mat[i][N-1] == (couleur==BLANC?NOIR:BLANC) && i > (N/2)-1){
			cpt_final -= val_bord;
			i--;
		}
	}
	else{
		if(mat[N-2][N-1] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[N-1][N-2] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[N-2][N-2] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[N-3][N-1] == couleur)
			cpt_final += val_bord;
		if(mat[N-1][N-3] == couleur)
			cpt_final += val_bord;
	}


	
	if(haut_D == 1){
		i = 1;
		j = N-2;
		while(mat[0][j] == couleur && j > (N/2)-1){
			cpt_final += val_bord;
			j--;
		}
		while(mat[i][N-1] == couleur && i < (N/2)-1){
			cpt_final += val_bord;
			i++;
		}	
	}
	else if(haut_D == -1){
		i = 1;
		j = N-2;
		while(mat[0][j] == (couleur==BLANC?NOIR:BLANC) && j > (N/2)-1){
			cpt_final -= val_bord;
			j--;
		}
		while(mat[i][N-1] == (couleur==BLANC?NOIR:BLANC) && i < (N/2)-1){
			cpt_final -= val_bord;
			i++;
		}
	}
	else{
		if(mat[N-2][0] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[N-1][1] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[N-2][1] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[N-3][0] == couleur)
			cpt_final += val_bord;
		if(mat[N-1][2] == couleur)
			cpt_final += val_bord;
	}
	


	if(bas_G == 1){
		i = N-2;
		j = 1;
		while(mat[N-1][j] == couleur && j < (N/2)-1){
			cpt_final += val_bord;
			j++;
		}
		while(mat[i][0] == couleur && i > (N/2)-1){
			cpt_final += val_bord;
			i--;
		}	
	}
	else if(bas_G == -1){
		i = N-2;
		j = 1;
		while(mat[N-1][j] == (couleur==BLANC?NOIR:BLANC) && j < (N/2)-1){
			cpt_final -= val_bord;
			j++;
		}
		while(mat[i][0] == (couleur==BLANC?NOIR:BLANC) && i > (N/2)-1){
			cpt_final -= val_bord;
			i--;
		}
	}
	else{
		if(mat[0][N-2] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[1][N-1] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[0][N-1] == couleur)
			cpt_final -= val_adj_coin;
		if(mat[0][N-3] == couleur)
			cpt_final += val_bord;
		if(mat[2][N-1] == couleur)
			cpt_final += val_bord;
	}
	



		/** Pts pour le centre du plateau **/
	if(mat[N/2][N/2] == couleur)
		cpt_final += val_centre;
	else{
		cpt_final -= val_centre;
	}
	if(mat[(N/2)-1][N/2] == couleur)
		cpt_final += val_centre;
	else{
		cpt_final -= val_centre;
	}
	if(mat[N/2][(N/2)-1] == couleur)
		cpt_final += val_centre;
	else{
		cpt_final -= val_centre;
	}
	if(mat[(N/2)-1][(N/2)-1] == couleur)
		cpt_final += val_centre;
	else{
		cpt_final -= val_centre;
	}

		/** On renvoie le compteur final **/
	return cpt_final;
}


/**
*\brief Cette fonction simule le tour du joueur, et renvoie la valeur la plus petite calculée (elle appelle la fonction ordi)
**/
int joueur(char mat[N][N], char couleur, int nb_coup_prevu, int *alpha, int *beta){

	int lig, col, val_ret = 0;
	int val_min = 99999;
	char mat2[N][N];

	if(peut_jouer(mat, couleur) == 0)						/** Si on ne peut pas jouer **/
		return (150);

	for(lig=0;lig<N;lig++){									/** On fait toutes les possibilitées **/
		for(col=0;col<N;col++){
								
			if(coup_possible(mat,couleur,lig,col) != 0){	/** Si le coup est possible **/
								
				copie(mat, mat2);							/** On effectue les calculs sur une copie de mat **/
															/** On effectue le placement du pion et on retourne le(s) pion(s) à retourner **/
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);
				if(nb_coup_prevu == 1){
					/*
					printf("\n\t\t\t\tj %i/%i (%c)= %i", lig, col, couleur, fonc_eval(mat2, couleur));
					*/
					val_ret = fonc_eval(mat2, couleur);
				}	
				else{										/** On regarde un cran plus bas **/
					val_ret = ordi(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, alpha, beta);
					/*
					if(nb_coup_prevu == 4)
						printf("\n\t");
					if(nb_coup_prevu == 3)
						printf("\n\t\t");
					if(nb_coup_prevu == 2)
						printf("\n\t\t\t");
					if(nb_coup_prevu == 1)
						printf("\n\t\t\t\t");
					printf("j %i/%i (%c)= %i", lig, col, couleur, val_ret);
					*/
				}
				if(val_ret < val_min) 						/** On garde la valeur la plus petite **/
					val_min = val_ret;
				
			}
															/** On passe à la case suivante **/
		}
	}
	/*
	if(nb_coup_prevu == 4)
		printf("\n\t");
	if(nb_coup_prevu == 3)
		printf("\n\t\t");
	if(nb_coup_prevu == 2)
		printf("\n\t\t\t");
	if(nb_coup_prevu == 1)
		printf("\n\t\t\t\t");
	printf("j (%c)= %i", couleur, val_min);
	*/
	return val_min;											/** On renvoie la valeur minimum **/
}



/**
*\brief Cette fonction simule le tour de l'ordinateur, et renvoie la valeur la plus grande calculée (elle appelle la fonction joueur)
**/
int ordi(char mat[N][N], char couleur, int nb_coup_prevu, int *alpha, int *beta){

	int lig, col, val_ret = 0;
	int val_max = -99999;
	char mat2[N][N];
	
	if(peut_jouer(mat, couleur) == 0)						/** Si on ne peut pas jouer **/
		return (-150);
	
	for(lig=0;lig<N;lig++){									/** On fait toutes les possibilitées **/
		for(col=0;col<N;col++){
			
			if(coup_possible(mat,couleur,lig,col) != 0){	/** Si le coup est possible **/
				
				copie(mat, mat2);							/** On effectue les calculs sur une copie de mat **/
															/** On effectue le placement du pion et on retourne le(s) pion(s) à retourner **/
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);
				if(nb_coup_prevu == 1){									/** Si on est arrivé à la profondeur voulue, on renvoie la valeur de fonc_eval **/
					/*
					printf("\n\t\t\t\to %i/%i (%c)= %i", lig, col, couleur, fonc_eval(mat2, couleur));
					*/
					val_ret = fonc_eval(mat2, couleur);
				}										
				else{										/** On regarde un cran plus bas **/
					val_ret = joueur(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, alpha, beta);
					/*
					if(nb_coup_prevu == 4)
						printf("\n\t");
					if(nb_coup_prevu == 3)
						printf("\n\t\t");
					if(nb_coup_prevu == 2)
						printf("\n\t\t\t");
					if(nb_coup_prevu == 1)
						printf("\n\t\t\t\t");
					printf("o %i/%i (%c)= %i", lig, col, couleur, val_ret);
					*/
				}
				if(val_ret > val_max) 						/** On garde la valeur la plus grande **/
					val_max = val_ret;

			}
															/** On passe à la case suivante **/
		}
	}
	/*
	if(nb_coup_prevu == 4)
		printf("\n\t");
	if(nb_coup_prevu == 3)
		printf("\n\t\t");
	if(nb_coup_prevu == 2)
		printf("\n\t\t\t");
	if(nb_coup_prevu == 1)
		printf("\n\t\t\t\t");
	printf("o (%c)= %i", couleur, val_max);
	*/
	return val_max;											/** On renvoie la valeur maximum **/
}



/**
*\brief Cette fonction simule le tour de l'ordinateur, et permet d'avoir les coordonnées du prochain coup de l'ordinateur
**/
void tour_ordi(char mat[N][N], char couleur, int nb_coup_prevu, int *px, int *py){

	int lig, col, val_ret = 0, lig_max = -1, col_max = -1;
	int val_max = -99999;

	int alpha = -99999;
	int beta = 99999;

	char mat2[N][N];
	

	for(lig=0;lig<N;lig++){									/** On fait toutes les possibilitées **/
		for(col=0;col<N;col++){

			if(coup_possible(mat,couleur,lig,col) != 0){	/** Si le coup est possible **/
				
				copie(mat, mat2);							/** On effectue les calculs sur une copie de mat **/
															/** On effectue le placement du pion et on retourne le(s) pion(s) à retourner **/
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);
				
				if(nb_coup_prevu == 1){						/** Si on est arrivé à la profondeur voulue, on garde la valeur de fonc_eval **/
					val_ret = fonc_eval(mat2, couleur);
				}
				else{										/** Sinon, on regarde un cran plus bas **/
					val_ret = joueur(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, &alpha, &beta);
				}
				/*
				printf("\no %i/%i (%c)= %i", lig, col, couleur, val_ret);
				*/
				if(val_ret > val_max) {						/** On garde la valeur la plus grande **/
					val_max=val_ret;
					lig_max=lig;
					col_max=col;
				}
				
			}
															/** On passe à la case suivante **/
		}
	}
	/*
	printf("\no (%c)= %i", couleur, val_max);
	*/
	*px=lig_max;											/** On met les coordonnées du prochain coup dans des pointeurs **/
	*py=col_max;
}

