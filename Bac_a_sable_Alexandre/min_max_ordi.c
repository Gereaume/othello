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


/*
Le but est de tester toutes les positions possibles jouables par l'ordi, 
puis de faire jouer tous les coups du joueur humain, et ainsi de suite jusqu'a un N-ème terme.
Puis par rapport au différentes matrices que cela donnera, garder le chemin étant le meilleur pour l'ordi.
*/


int min_max(char mat[N][N]){




}



int joueur(char mat[N][N], int max, char couleur, int nb_coup_prevu){

	int i, col;

	for(lig=0;lig<max;lig++){
		for(col=0;col<max;col++){
			if(coup_possible(mat,couleur,lig-'0',col-'0') != 0 && (isdigit(lig) && isdigit(col))){
				if(nb_coup_prevu == 1){

				}
				else{
					if(couleur == 'blanc'){
						ordi(mat, max-1, noir, nb_coup_prevu-1);
					}
					else{
						ordi(mat, max-1, blanc, nb_coup_prevu-1);
					}
				}
				
				
			}

		}
	}

}

int ordi(char mat[N][N], int max, char couleur, int nb_coup_prevu, int pions_calcul, int pions_max){

	int lig, col;

	for(lig=0;lig<max;lig++){
		for(col=0;col<max;col++){
			if(coup_possible(mat,couleur,lig-'0',col-'0') != 0 && (isdigit(lig) && isdigit(col))){
				if(nb_coup_prevu == 1){
					if(pions_calcul > pions_max){
						pions_max = pions_calcul;
					}
					
				}
				else{
					retourner(mat2, couleur, lig, col)
					if(couleur == 'blanc'){
						joueur(mat, max-1, noir, nb_coup_prevu-1, );
					}
					else{
						joueur(mat, max-1, blanc, nb_coup_prevu-1);
					}
				}
				
				
			}

		}
	}
}



int ordi_cb(char mat[N][N], int max, char couleur, int nb_coup_prevu, int pions_calcul, int pions_max){
	char mat2[N][N];
	copie(mat, mat2);
	ordi(mat2, max, couleur, nb_coup_prevu, pions_calcul, pions_max);
}