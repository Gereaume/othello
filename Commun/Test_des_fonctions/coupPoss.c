/**
*\file coupPoss.c
*\brief Ce fichier contient des fonctions permettant de savoir si un coup est possible et cb de pions sont retournés
*\author Alexandre Laloy
*\version 1.0
*\date 20 fevrier 2018
**/



#include <stdio.h>
#include <stdlib.h>


#include "coupPoss.h"
#include "gestion_matrice.h"
#include "define.h"


/**
*\brief Renvoie le nombre de pions retourné, si aucun retourné, return 0
**/
int retourner(char mat[N][N], char couleur, int lig, int col){

	int i, j, cpt,x;
	int cpt_final = 0;




/*********************************************************************************
Il y a 8 fois ce traitement pour les 8 directions possibles pour retourner un pion
*********************************************************************************/

	if(mat[lig-1][col-1] != '*' && mat[lig-1][col-1] != couleur){	/** Si la case est de la couleur de l'adversaire **/
		i = lig-1;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
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
int coupPoss(char mat[N][N], char couleur, int lig, int col){
	char mat2[N][N];
	int nb_pions_ret;
	copie(mat, mat2);	/** copie contenu de mat dans mat2	**/

	if((mat[lig][col] == '*') && !hors_mat(lig,col)){ // si les coordonnées correspondent à une zone vide
		printf("coucou1");
		nb_pions_ret = retourner(mat2, couleur, lig, col); // si le pion posé retourne au moins 1 pion
		printf("coucou2");
		if(nb_pions_ret != 0){
			printf("coucou3");
			printf("Le nb retourner est de %i\n", nb_pions_ret);
			return 1;
		}
		else{
			printf("coucou4");
			return 0;
		}
	}
	else{
		printf("coucou5");
		return 0; // sinon faux
	}
}



