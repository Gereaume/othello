#include <stdlib.h>
#include <stdio.h>

#include "gestion_matrice.h"
#include "gestion_tour.h"
#include "define.h"
#include "joueur.h"

int main()
{
	t_joueur joueur1;
	t_joueur joueur2;
	char mat[N][N];
	init_mat(mat);
	printf("\n\tJoueur n°1 entrez votre pseudo : ");
	scanf("%s%*c",joueur1.nom_joueur);
	printf("\n\tJoueur n°2 entrez votre pseudo : ");
	scanf("%s%*c",joueur2.nom_joueur);
	gestion_tour(mat,joueur1,joueur2);
	
}
