#include <stdio.h>
#include <stdlib.h>
#define N 8
#include "fin.h"
#include "gestion_matrice.h"



int rand_a_b(int a, int b){  /* fonction aléatoire pour choisir qui commence à jouer */

    return rand()%(b-a) +a;

}

int jouer(char mat[N][N]){

	int i;
	char pre1[20];
	char pre2[20];
	init_mat(mat);
	lire_mat(mat);

	printf("Joueur 1, entrez votre prénom \n ");
	scanf("%s \n", pre1);
	
	printf("Joueur2, entrez votre prénom \n");
	scanf("%s \n",pre2);

	
	if(rand_a_b(1,2) == 1){
		printf("%s, vous aurez les noirs, vous commencez \n", pre1);
		printf("%s, vous aurez les blancs \n", pre2);
		ecrire_mat(mat,'n');
		ecrire_mat(mat,'b');
		while(fin(mat) != 1){
			ecrire_mat(mat,'n');
			ecrire_mat(mat,'b');
			lire_mat(mat);
		}
	}
	else{
		printf("%s, vous aurez les noirs, vous commencez \n", pre2);
		printf("%s, vous aurez les blancs \n", pre1);
		ecrire_mat(mat,'n');
		ecrire_mat(mat,'b');
		while(fin(mat) != 1){
			ecrire_mat(mat,'n');
			ecrire_mat(mat,'b');
			lire_mat(mat);
		}	
	
	}
}