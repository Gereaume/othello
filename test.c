#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include <SDL/SDL.h>
#include "gestion_matrice.h"
#define N 8


int main(){
	char mat[N][N];
	char mat2[N][N];
	init_mat(mat);
	afficher_matrice(mat);
	




}