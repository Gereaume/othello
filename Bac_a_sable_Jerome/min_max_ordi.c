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



/******************************************************************************************************
Renvoie une valeur par rapport au coup joué, plus le coup est interessant, plus il rapporte de point(s)
******************************************************************************************************/
int fonc_eval(char mat[N][N], char couleur, int lig, int col, int nb_pions_en_plus){
	if(couleur == 'blanc'){	/* Si c'est ordi */

		/* S'il joue dans le coin */
		if(lig == 0 && col == 0 || lig == N-1 && col == N-1 || lig == 0 && col == N-1 || lig == N-1 && col == 0){
			/* On retourne la valeur max */
			return (N*N);
		}
		
		/* S'il joue sur le bord */
		else if(lig == 0 || lig == N-1 || col == 0 || col == N-1){


			/* Si la ligne vaut 0 (ligne du haut), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			if(lig == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en haut à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Si la ligne vaut N-1 (ligne du bas), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(lig == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Si la colonne vaut 0 (colonne de gauche), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Si la colonne vaut N-1 (colonne de droite), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à droite */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Sinon, il n'y a aucune suite continue jusqu'a un coin de la meme couleur, 
			donc c'est juste un bord normal, avec risque de se le faire reprendre */
			else{
				return (N*N/6);
			}

		}

		/* Sinon on renvoie le nb de pions en plus */
		else{
			return nb_pions_en_plus+1;
		}

	}
	else{	/* Sinon c'est joueur */

		/* S'il joue dans le coin */
		if(lig == 0 && col == 0 || lig == N-1 && col == N-1 || lig == 0 && col == N-1 || lig == N-1 && col == 0){
			/* On retourne la valeur max */
			return -(N*N);
		}
		
		/* S'il joue sur le bord */
		else if(lig == 0 || lig == N-1 || col == 0 || col == N-1){


			/* Si la ligne vaut 0 (ligne du haut), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			if(lig == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en haut à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Si la ligne vaut N-1 (ligne du bas), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(lig == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Si la colonne vaut 0 (colonne de gauche), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Si la colonne vaut N-1 (colonne de droite), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à droite */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Sinon, il n'y a aucune suite continue jusqu'a un coin de la meme couleur, 
			donc c'est juste un bord normal, avec risque de se le faire reprendre */
			else{
				return -(N*N/6);
			}

		}

		/* Sinon on renvoie le nb de pions en plus */
		else{
			return -nb_pions_en_plus;
		}
		
	}
}


/*************
Renvoie le min
*************/
int joueur(char mat[N][N], char couleur, int nb_coup_prevu, int * x, int * y){

	int lig, col, val_ret;
	char mat2[N][N];
	/* On fait toutes les possibilitées */
	for(lig=0;lig<N;lig++){
		for(col=0;col<N;col++){
			/* Si le coup est possible */
			if(coup_possible(mat,couleur,lig,col) != 0 && (isdigit(lig) && isdigit(col))){
				
				/* On effectue les calculs sur une copie de mat */
				copie(mat, mat2);
				ecrire_mat(mat,couleur,lig,col);
				/* On effectue le placement du pion et on retourne le(s) pion(s) à retourner */
				val_ret = retourner(mat2, couleur, lig, col);
				/* Si on a atteint le nombre de coup que l'on voulait prévoir */
				if(nb_coup_prevu == 1){
					/* Si le coup rapporte plus que la valeur max */
					if(fonc_eval(mat2, couleur, lig, col, val_ret) < val_min){
						/* La valeur max prend la valeur retourné par fonc_eval */
						val_min = fonc_eval(mat2, couleur, lig, col, val_ret);
					}
				}
				/* Sinon, on va voir un coup plus loin */
				else{
					joueur(mat2, blanc, nb_coup_prevu-1, val_max, val_min);
				}
			}
			/* On passe à la case suivante */
		}
	}
	return val_min;
}



/*************
Renvoie le max
*************/
int ordi(char mat[N][N], char couleur, int nb_coup_prevu, int val_max, int val_min){

	int lig, col, val_ret;
	char mat2[N][N];
	/* On fait toutes les possibilitées */
	for(lig=0;lig<N;lig++){
		for(col=0;col<N;col++){
			/* Si le coup est possible */
			if(coup_possible(mat,couleur,lig,col) != 0 && (isdigit(lig) && isdigit(col))){
				
				/* On effectue les calculs sur une copie de mat */
				copie(mat, mat2);
				/* On effectue le placement du pion et on retourne le(s) pion(s) à retourner */
				ecrire_mat(mat,couleur,lig,col);
				val_ret = retourner(mat2, couleur, lig, col);

				/* Si le coup rapporte plus que la valeur max */
				if(fonc_eval(mat2, couleur, lig, col, val_ret) > val_max){
					/* La valeur max prend la valeur retourné par fonc_eval */
					val_max = fonc_eval(mat2, couleur, lig, col, val_ret);
				}

				/* Si on n'a pas atteint le nombre de coup que l'on voulait prévoir */
				if(nb_coup_prevu > 1){
					joueur(mat2, noir, nb_coup_prevu-1, val_max, val_min);
				}
			}
			/* On passe à la case suivante */
		}
	}
	return val_max;
}



void ordi_cb(char mat[N][N], char couleur, int nb_coup_prevu){
	
	ordi(mat, couleur, nb_coup_prevu, -999, 999); /* On initialise la valeur pointer par x et y par la valeur -1 */
}