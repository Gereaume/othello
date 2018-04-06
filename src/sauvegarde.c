#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define.h"


void sauvegarde_etat_partie(int mat[N][N],int couleur)
{
	FILE * fic= fopen("save_partie.txt","w");
	if(fic != NULL)
	{
		rewind(fic);
		for(int lig = 0;lig<N;lig++)
		{
			for(int col = 0;col<N;col++)
			{
				fprintf(fic,"%i ",mat[lig][col]);
			}
			fprintf(fic,"\n");
		}
		fprintf(fic,"%i",couleur);
	}
	fclose(fic);
	
}


int charger_partie(int mat[N][N])
{
	int couleur = 0;
	int temp = 0;
	
	FILE * fic= fopen("save_partie.txt","r");
	if(fic != NULL)
	{
		rewind(fic);
		for(int lig = 0;lig<N;lig++)
		{
			for(int col = 0;col<N;col++)
			{
				fscanf(fic,"%i",&temp);
				mat[lig][col] = temp;
			}
		}
		fscanf(fic,"%i",&couleur);
	}
	fclose(fic);
	return couleur;
}

