#include <stdlib.h>
#include <stdio.h>

#include "gestion_matrice.c"
#include "gestion_tour.c"
#include "coupPoss.c"
#include "define.h"

int main(){
	char mat[N][N];
	init_mat(mat);
	lire_mat(mat);
	gestion_tour(mat);
	
}