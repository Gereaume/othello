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
#include "joueur.h"

/**
*\brief Cette fonction permet le bon déroulement du tour des différents joueurs
**/
void gestion_tour(char mat[N][N],t_joueur joueur1,t_joueur joueur2)
{


	int i = 0,nb_ret = 0;					/** Déclaration des variables	**/
	char lig = '0',col = '0';
	
	system("clear");
	printf("\nBIENVENUE AU JEU DE L'OTHELLO\n\n");
	sleep(1);
	joueur1.score = 2;					/** Initialisation des scores des joueurs	**/
	joueur2.score = 2;
	

	while(i<(N*N)-4)
	{	
		
		
		if(peut_jouer(mat, noir) == 1)
		{
			system("clear");					/** On nettoie le terminal au debut du tour	**/
		
			printf("\n\tNb de pions blanc %i",joueur2.score); /** On affiche le score actuel **/
			printf("\n\tNb de pions noir %i\n", joueur1.score);			
			printf("\n\t%s c'est ton tour (noir)\n",joueur1.nom_joueur);			/** On indique que c'est le tour du joueur n°1	**/
			lire_mat(mat);						/** On affiche la matrice	**/

			printf("\n\tVeuillez saisir les coordonnées ou vous souhaitez jouer \n\tLa ligne : ");
			scanf("%c%*c",&lig);
			printf("\n\tLa colonne : ");
			scanf("%c%*c",&col);				/** Le joueur saisie les coordonnées où il veut jouer	**/		
			
			while(coup_possible(mat,noir,lig-'0',col-'0') == 0 || (!isdigit(lig)||!isdigit(col)))		/** Tant que le coup est impossible le joueur doit ressaisir les coordonnées de l'endroit ou il veut jouer	**/
			{
				printf("\n\tCe coup la n'est pas possible\n\tVeuillez resaisir\n\tLa ligne : ");
				scanf("%c%*c",&lig);
				printf("\n\tLa colonne : ");
				scanf("%c%*c",&col);
			}
		
			ecrire_mat(mat,noir,lig-'0',col-'0');				/** Une fois que l'endroit où le joueur a décider de jouer est possible on l'ecrit dans la matrice	**/
			nb_ret = retourner(mat,noir,lig-'0',col-'0');
			joueur1.score += (nb_ret+1);
			joueur2.score -= nb_ret;
			printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);
			i+=1;							/** On incrémente i	**/

		}	
		else{				
			printf("\n\t%s ne peut pas jouer\n",joueur1.nom_joueur);	
		}


		
		if(peut_jouer(mat, blanc) == 1)
		{
			system("clear");					/** On nettoie le terminal au debut du tour	**/
		
			printf("\n\tNb de pions blanc %i", joueur2.score); /** On affiche le score actuel **/
			printf("\n\tNb de pions noir %i\n", joueur1.score);			
			printf("\n\t%s c'est ton tour (blanc)\n",joueur2.nom_joueur);		/** On indique que c'est le tour du joueur n°2	**/

			lire_mat(mat);						/** On affiche la matrice	**/

			printf("\n\tVeuillez saisir les coordonnées ou vous souhaitez jouer \n\tLa ligne : ");
			scanf("%c%*c",&lig);
			printf("\n\tLa colonne : ");
			scanf("%c%*c",&col);				/** Le joueur saisie les coordonnées où il veut jouer	**/

			while(coup_possible(mat,blanc,lig-'0',col - '0') == 0 || (!isdigit(lig)||!isdigit(col)))		/** Tant que le coup est impossible le joueur doit ressaisir les coordonnées de l'endroit ou il veut jouer	**/
			{
				printf("\n\tCe coup la n'est pas possible\n\tVeuillez resaisir\n\tLa ligne : ");
				scanf("%c%*c",&lig);
				printf("\n\tLa colonne : ");
				scanf("%c%*c",&col);
			}
		
			ecrire_mat(mat,blanc,lig-'0',col-'0');				/** Une fois que l'endroit ou le joueur a décider de jouer est possible on l'ecrit dans la matrice	**/
			nb_ret=retourner(mat,blanc,lig-'0',col-'0');
			joueur2.score += (nb_ret+1);
			joueur1.score -= nb_ret;
			printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);
			i+=1;							/** On incrémente i	**/
		}
		else{				
			printf("\n\t%s ne peut pas jouer\n",joueur2.nom_joueur);
		}
		if(peut_jouer(mat, blanc) == 0 && peut_jouer(mat, noir) == 0){
			printf("\n\tAucun joueur ne peut jouer\n");
			sleep(1);
			break;
		}
	}
	system("clear");
	printf("\n\tNb de pions blanc %i",joueur2.score);
	printf("\n\tNb de pions noir %i", joueur1.score);
	lire_mat(mat);
	if(joueur1.score>joueur2.score)
		printf("\tC'est %s qui a gagné !\n",joueur1.nom_joueur);
	else if(joueur1.score<joueur2.score)
		printf("\tC'est %s qui a gagné !\n",joueur2.nom_joueur);
	else
		printf("\tEx-aequo !\n");
	return;

}
