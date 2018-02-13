#include <stdio.h>
#include <stdlib.h>

#include "afficherSP.h"
#include "score.h"

void afficherSP(char mat[N][N], char couleur){

	int score = score(mat,couleur);
	printf("%s - Votre Score : %i\n", pseudo, score);
}