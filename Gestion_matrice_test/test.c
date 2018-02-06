#include<stdlib.h>
//#include<unistd.h>
#include<stdio.h>
#include "gestion_matrice.h"

#define N 8


int main(){
	char mat[N][N];
	init_mat(mat);
	lire_mat(mat);
	char c = 'b';
	ecrire_mat(mat,c);
	lire_mat(mat);




}