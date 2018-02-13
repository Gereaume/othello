#include<stdlib.h>
#include<stdio.h>

#include "gestion_matrice.h"
#include "define.h"

int main(){
	char mat[N][N];
	init_mat(mat);
	lire_mat(mat);
	char c = 'b';
	ecrire_mat(mat,c,1,1);
	lire_mat(mat);




}