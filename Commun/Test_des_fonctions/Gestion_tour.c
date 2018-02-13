#include <stdio.h>
#include <stdlib.h>
	
#include "gestion_matrice.c"

int gestion_tour(){
	int i = 0;
	char noir = "n";
	char blanc = "b";
	while(coup_possible())
	{	
		if((i%2)!=1)
		{
			system("clear");
			printf("\tTour du joueur n°1\n");
			lire_mat(mat);
			printf("\tVeuillez saisir les coordonnées ou vous souhaitez jouer");
			scanf("%i%i",&lig,&col);
			while(!coup_possible())
			{
				printf("\tCe coup la n'est pas possible ");
				scanf("%i%i",&lig,&col);
			}
			ecrire_mat(mat,noir,lig,col);
			lire_mat(mat)
			i+=1;
		}		
		else if((i%1)=1)
		{
			system("clear");
			printf("\tTour du joueur n°2\n");
			lire_mat(mat);
			printf("\tVeuillez saisir les coordonnées ou vous souhaitez jouer");
			scanf("%i%i",&lig,&col);
			while(!coup_possible())
			{
				printf("\tCe coup la n'est pas possible ");
				scanf("%i%i",&lig,&col);
			}
			ecrire_mat(mat,blanc,lig,col);
			lire_mat(mat)
			i+=1
		}
	}
}