#include <stdio.h>
#include <stdlib.h>


#include "coupPoss.h"
#include "gestion_matrice.h"
#include "define.h"

void copie(char mat[N][N], char mat2[N][N]){

	int i, j;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			mat2[i][j] = mat[i][j];
		}
	}
}


int retourner(char mat[N][N], char couleur, int lig, int col){

	int i, j, cpt,x;
	int cpt_final = 0;

	if(mat[lig-1][col-1] != '*' && mat[lig-1][col-1] != couleur){
		i = lig-1;
		j = col-1;
		cpt = 0;
		while(mat[i][j] != couleur && mat[i][j] != '*' && !hors_mat(i, j) ){
			i--;
			j--;
			cpt++;
		}
		if(mat[i][j] == couleur){
			i = lig-1;
			j = col-1;
			for(x=0;x<cpt;x++){
				mat[i][j] = couleur;
				i--;
				j--;
				cpt_final++;
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

	return cpt_final;
}



/******************************************
Renvoie 1 si le coup est possible, sinon 0
******************************************/

int coupPoss(char mat[N][N], char mat2[N][N], char couleur, int lig, int col){
	int nb_pions_ret;
	copie(mat, mat2); // copie contenu de mat dans mat2

	if((mat[lig][col] == '*') && !hors_mat(lig,col)){ // si les coordonnées correspondent à une zone vide
		nb_pions_ret = retourner(mat2, couleur, lig, col); // si le pion posé retourne au moins 1 pion
		printf("Le nb retourner est de %i\n", nb_pions_ret);
		return 1;	
	}
	else{
		return 0; // sinon faux
	}
}



