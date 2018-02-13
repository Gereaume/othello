#include <stdio.h>
#include <stdlib.h>
	
#include "gestion_matrice.h"
#include "gestion_tour.h"
#include "define.h"
#include "coupPoss.h"


/******************************************************************************************
Cette fonction permet de savoir qui a gagné
******************************************************************************************/

int gagnant(char mat[N][N]){
	int nb_noir = 0, nb_blanc = 0;						//Déclaration des variables				
	char noir = 'n';
	char blanc = 'b';
	nb_noir = compter_elem(mat,noir);					//On compte le nombre de pion noir
	nb_blanc = compter_elem(mat,blanc);					//On compte le nombre de pion blanc
	
	if(nb_noir>nb_blanc)							//Si il y a plus de pion noir on return 1 donc le joueur n°1 a gagné
		return 1;
	else									//Si il y a plus de pion blanc on return donc le joueur n°2 a gagné
		return 0;

}



/******************************************************************************************
Cette fonction permet le bon déroulement du tour des différents joueurs
******************************************************************************************/
void gestion_tour(char mat[N][N]){


	int i = 0, lig=0, col=0;						//Déclaration des variables
	char noir = 'n';
	char blanc = 'b';	
	char mat2[N][N];
	while(i<20)
	{	
		if((i%2)!=1)
		{
			system("clear");					//On nettoie le terminal au debut du tour
			printf("\tTour du joueur n°1\n");			//On indique que c'est le tour du joueur n°1
			lire_mat(mat);						//On affiche la matrice
			printf("\n\tVeuillez saisir les coordonnées ou vous souhaitez jouer");
			scanf("%i%i",&lig,&col);				//Le joueur saisie les coordonnées où il veut jouer
			while(!coupPoss(mat,mat2,noir,lig,col))			//Tant que le coup est impossible le joueur doit ressaisir les coordonnées de l'endroit ou il veut jouer
			{
				printf("\n\tCe coup la n'est pas possible ");
				scanf("%i%i",&lig,&col);
			}
			ecrire_mat(mat,noir,lig,col);				//Une fois que l'endroit où le joueur a décider de jouer est possible on l'ecrit dans la matrice
			lire_mat(mat);						//On affiche la matrice une fois le coup fait
			i+=1;							//On incrémente i
		}		
		else if((i%2)==1)
		{
			system("clear");					//On nettoie le terminal au debut du tour
			printf("\tTour du joueur n°2\n");			//On indique que c'est le tour du joueur n°2
			lire_mat(mat);						//On affiche la matrice
			printf("\n\tVeuillez saisir les coordonnées ou vous souhaitez jouer");
			scanf("%i%i",&lig,&col);				//Le joueur saisie les coordonnées où il veut jouer
			while(!coupPoss(mat,mat2,blanc,lig,col))		//Tant que le coup est impossible le joueur doit ressaisir les coordonnées de l'endroit ou il veut jouer
			{
				printf("\n\tCe coup la n'est pas possible ");
				scanf("%i%i",&lig,&col);
			}
			ecrire_mat(mat,blanc,lig,col);				//Une fois que l'endroit ou le joueur a décider de jouer est possible on l'ecrit dans la matrice
			lire_mat(mat);						//On affiche la matrice une fois le coup fait
			i+=1;							//On incrémente i
		}
	}
	
	if(gagnant(mat) == 1)
		printf("\tC'est le joueur n°1 qui a gagné\n");
	else
		printf("\tC'est le joueur n°2 qui a gagné\n");
	return;

}
