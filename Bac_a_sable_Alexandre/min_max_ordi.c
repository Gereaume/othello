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
#include "coup_possible_retourner.h"


/*
Le but est de tester toutes les positions possibles jouables par l'ordi, 
puis de faire jouer tous les coups du joueur humain, et ainsi de suite jusqu'a un N-ème terme.
Puis par rapport au différentes matrices que cela donnera, garder le chemin étant le meilleur pour l'ordi.
*/



/******************************************************************************************************
Renvoie une valeur par rapport au coup joué, plus le coup est interessant, plus il rapporte de point(s)
******************************************************************************************************/
int fonc_eval(char mat[N][N], char couleur){
	int val_eval = 0;
	if(couleur==NOIR){ /* si c'est joueur, on minimise */
		val_eval -= compter_elem(mat, couleur);
		val_eval += compter_elem(mat, BLANC);
	}
	else{
		val_eval += compter_elem(mat, couleur);
		val_eval -= compter_elem(mat, NOIR);
	}
	return val_eval;
}


/*************
Renvoie le min
*************/
int joueur(char mat[N][N], char couleur, int nb_coup_prevu, int alpha, int beta){

	int lig, col, val_ret;
	char mat2[N][N];
	int val_min = 999;

	if(nb_coup_prevu == 1){
		return fonc_eval(mat, couleur);
	}
	/* On fait toutes les possibilitées */
	for(lig=0;lig<N;lig++){
		for(col=0;col<N;col++){
			/* Si le coup est possible */
			if(coup_possible(mat,couleur,lig,col) != 0){
				
				/* On effectue les calculs sur une copie de mat */
				copie(mat, mat2);
				
				/* On effectue le placement du pion et on retourne le(s) pion(s) à retourner */
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);
			
					
				val_ret = ordi(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, alpha, beta);
				if(val_ret < val_min) 
					val_min=val_ret;
				
			}
			/* On passe à la case suivante */
		}
	}
	return val_min;
}



/*************
Renvoie le max
*************/
int ordi(char mat[N][N], char couleur, int nb_coup_prevu, int alpha, int beta){

	int lig, col, val_ret;
	int val_max = -999;
	char mat2[N][N];

	if(nb_coup_prevu == 1){
		return fonc_eval(mat, couleur);
	}
	/* On fait toutes les possibilitées */
	for(lig=0;lig<N;lig++){
		for(col=0;col<N;col++){
			/* Si le coup est possible */
			if(coup_possible(mat,couleur,lig,col) != 0){
				
				/* On effectue les calculs sur une copie de mat */
				copie(mat, mat2);

				/* On effectue le placement du pion et on retourne le(s) pion(s) à retourner */
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);

				
				val_ret = joueur(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, alpha, beta);
				if(val_ret > val_max) 
					val_max=val_ret;
				
			}
			/* On passe à la case suivante */
		}
	}
	return val_max;
}

void tour_ordi(char mat[N][N], char couleur, int nb_coup_prevu, int *px, int *py){

	int lig, col, val_ret, lig_max, col_max;
	int val_max = -999;
	char mat2[N][N];

	/* On fait toutes les possibilitées */
	for(lig=0;lig<N;lig++){
		for(col=0;col<N;col++){
			/* Si le coup est possible */
			if(coup_possible(mat,couleur,lig,col) != 0){
				
				/* On effectue les calculs sur une copie de mat */
				copie(mat, mat2);

				/* On effectue le placement du pion et on retourne le(s) pion(s) à retourner */
				ecrire_mat(mat2,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);

				if(nb_coup_prevu == 1){
					return fonc_eval(mat, couleur);
				}
				else{
					val_ret = joueur(mat2, couleur==NOIR?BLANC:NOIR, nb_coup_prevu-1, 999, -999);
				}
				
				if(val_ret > val_max) {
					val_max=val_ret;
					lig_max=lig;
					col_max=col;
				}
				
			}
			/* On passe à la case suivante */
		}
	}
	printf("\n\n\tVal de lig_max %i et val de col_max %i\n\n", lig_max, col_max);
	*px=lig_max;
	*py=col_max;
}

