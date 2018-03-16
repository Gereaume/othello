/**
*\file gestion_tour.c
*\brief Ce fichier contient des fonctions permettant la gestion des tours tel que le bon déroulement des tours et verifier qui est le gagnant
*\author Jérôme Le Querrec
*\version 1.0
*\date 08 fevrier 2018
**/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
	
#include "gestion_matrice.h"
#include "gestion_tour.h"
#include "define.h"
#include "coup_possible_retourner.c"
#include "joueur.c"

/**
*\brief la fonction gagnant permet de savoir qui a gagné
**/



int gagnant(char mat[N][N])
{
	int nb_noir = 0, nb_blanc = 0;						/** Déclaration des variables	**/				
	nb_noir = compter_elem(mat,noir);					/** On compte le nombre de pion noir	**/
	nb_blanc = compter_elem(mat,blanc);					/** On compte le nombre de pion blanc	**/
	
	if(nb_noir>nb_blanc)							/** Si il y a plus de pion noir on return 1 donc le joueur n°1 a gagné	**/
		return 1;
	else if(nb_noir<nb_blanc)								/** Si il y a plus de pion blanc on return donc le joueur n°2 a gagné	**/
		return 0;
	else
		return -1;

}



/**
*\brief Cette fonction permet le bon déroulement du tour des différents joueurs
**/
void gestion_tour(char mat[N][N])
{


	int i = 0;
	char lig = '0',col = '0';				/** Déclaration des variables	**/
	
	system("clear");
	printf("\nBIENVENUE AU JEU DE L'OTHELLO\n\n");
	sleep(0.1);
	

	while(i<(N*N)-4)
	{	
		system("clear");					/** On nettoie le terminal au debut du tour	**/
		
		printf("\n\tNb de pions blanc %i", compter_elem(mat, blanc));
		printf("\n\tNb de pions noir %i", compter_elem(mat, noir));
		if((i%2)==0)
		{
			printf("\n\tTour du joueur n°1 (noir)\n");			/** On indique que c'est le tour du joueur n°1	**/
			lire_mat(mat);						/** On affiche la matrice	**/
			printf("\n\tVeuillez saisir les coordonnées ou vous souhaitez jouer \n\t(d'abord la ligne puis la colonne) : ");
			scanf("%c%*c",&lig);
			scanf("%c%*c",&col);				/** Le joueur saisie les coordonnées où il veut jouer	**/
			while(!isdigit(lig)||!isdigit(col))
			{
				printf("\n\tIl y a eu un soucis avec la saisie veuillez recommencer\t");
				scanf("%c%*c",&lig);
				scanf("%c%*c",&col);
			}			
			while(coup_possible(mat,noir,lig-'0',col - '0') == 0)		/** Tant que le coup est impossible le joueur doit ressaisir les coordonnées de l'endroit ou il veut jouer	**/
			{
				printf("\n\tCe coup la n'est pas possible\n\tVeuillez resaisir : ");
				scanf("%c%*c",&lig);
				scanf("%c%*c",&col);
				printf("%c    ;  %c",lig,col);
			}
			
			ecrire_mat(mat,noir,lig-'0',col-'0');				/** Une fois que l'endroit où le joueur a décider de jouer est possible on l'ecrit dans la matrice	**/
			
			/* cette fonction renvoie un entier dont on ne se sert pas */
			retourner(mat,noir,lig-'0',col-'0');	
			sleep(1.5);
			
			i+=1;							/** On incrémente i	**/
		}		
		else if((i%2)!=0)
		{
			printf("\n\tTour du joueur n°2 (blanc)\n");			/** On indique que c'est le tour du joueur n°2	**/
			lire_mat(mat);						/** On affiche la matrice	**/
			printf("\n\tVeuillez saisir les coordonnées ou vous souhaitez jouer \n\t(d'abord la ligne puis la colonne) : ");
			//scanf("%i%i",&lig,&col);				/** Le joueur saisie les coordonnées où il veut jouer	**/
			while(coup_possible(mat,blanc,lig,col) == 0)		/** Tant que le coup est impossible le joueur doit ressaisir les coordonnées de l'endroit ou il veut jouer	**/
			{
				printf("\n\tCe coup la n'est pas possible\n\tVeuillez resaisir : ");
				//scanf("%i%i",&lig,&col);
			}
			ecrire_mat(mat,blanc,lig,col);				/** Une fois que l'endroit ou le joueur a décider de jouer est possible on l'ecrit dans la matrice	**/
			retourner(mat,blanc,lig,col);
			sleep(1.5);
			
			i+=1;							/** On incrémente i	**/
		}
	}
	system("clear");
	printf("\n\tNb de pions blanc %i", compter_elem(mat, blanc));
	printf("\n\tNb de pions noir %i", compter_elem(mat, noir));
	lire_mat(mat);
	if(gagnant(mat) == 1)
		printf("\tC'est le joueur n°1 qui a gagné !\n");
	else if(gagnant(mat) == 0)
		printf("\tC'est le joueur n°2 qui a gagné !\n");
	else
		printf("\tEx-aequo !\n");
	return;

}
