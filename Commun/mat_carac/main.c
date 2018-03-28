/**
*\file min_max_ordi.c
*\brief Ce fichier contient le main permettant de jouer une partie d'othello
*\author Alexandre Laloy
*\version 1.0
*\date 16 mars 2018
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestion_matrice.h"
#include "gestion_tour.h"
#include "define.h"
#include "joueur.h"



/**
*\brief Le main permet de jouer à l'othello, en mode humain vs humain, ou contre l'ordinateur avec différents niveaux
**/
int main(){

	t_joueur joueur1;
	t_joueur joueur2;
	char mat[N][N];
	int choix;

    do{
        printf("\nBienvenue au Jeu de l'Othello\n");
        printf("\nMenu :\n");
        printf(" 1 - Jouer mode Humain VS Humain\n");
        printf(" 2 - Jouer mode Humain VS Ordi (Easy)\n");
        printf(" 3 - Jouer mode Humain VS Ordi (Medium)\n");
        printf(" 4 - Jouer mode Humain VS Ordi (Hard)\n");
        printf(" 5 - Jouer mode Humain VS Ordi (Impossible)\n");
        printf(" 6 - Quitter\n");
        printf("Votre choix  : ");
        scanf("%i",&choix);

        switch(choix){
            case 1 : 	init_mat(mat);
            			printf("\n\tJoueur n°1 entrez votre pseudo : ");
						scanf("%s%*c",joueur1.nom_joueur);
						printf("\n\tJoueur n°2 entrez votre pseudo : ");
						scanf("%s%*c",joueur2.nom_joueur);
						gestion_tour(mat,joueur1,joueur2); break;

            case 2 : 	init_mat(mat);
            			/*
            			joueur2.nom_joueur[50] = "Ordi";
            			*/
            			joueur2.nom_joueur[0] = 'O';
            			joueur2.nom_joueur[1] = 'r';
            			joueur2.nom_joueur[2] = 'd';
            			joueur2.nom_joueur[3] = 'i';
            			joueur2.nom_joueur[4] = '\0';
            			
            			printf("\n\tJoueur entrez votre pseudo : ");
						scanf("%s%*c",joueur1.nom_joueur);
						gestion_tour_ia(mat,joueur1,joueur2, 3); break;

			case 3 : 	init_mat(mat);
            			/*
            			joueur2.nom_joueur[50] = "Ordi";
            			*/
            			joueur2.nom_joueur[0] = 'O';
            			joueur2.nom_joueur[1] = 'r';
            			joueur2.nom_joueur[2] = 'd';
            			joueur2.nom_joueur[3] = 'i';
            			joueur2.nom_joueur[4] = '\0';
            			
            			printf("\n\tJoueur entrez votre pseudo : ");
						scanf("%s%*c",joueur1.nom_joueur);
						gestion_tour_ia(mat,joueur1,joueur2, 5); break;

			case 4 : 	init_mat(mat);
            			/*
            			joueur2.nom_joueur[50] = "Ordi";
            			*/
            			joueur2.nom_joueur[0] = 'O';
            			joueur2.nom_joueur[1] = 'r';
            			joueur2.nom_joueur[2] = 'd';
            			joueur2.nom_joueur[3] = 'i';
            			joueur2.nom_joueur[4] = '\0';
            			
            			printf("\n\tJoueur entrez votre pseudo : ");
						scanf("%s%*c",joueur1.nom_joueur);
						gestion_tour_ia(mat,joueur1,joueur2, 7); break;

			case 5 : 	init_mat(mat);
            			/*
            			joueur2.nom_joueur[50] = "Ordi";
            			*/
            			joueur2.nom_joueur[0] = 'O';
            			joueur2.nom_joueur[1] = 'r';
            			joueur2.nom_joueur[2] = 'd';
            			joueur2.nom_joueur[3] = 'i';
            			joueur2.nom_joueur[4] = '\0';
            			
            			printf("\n\tJoueur entrez votre pseudo : ");
						scanf("%s%*c",joueur1.nom_joueur);
						gestion_tour_ia(mat,joueur1,joueur2, (N*N-4)); break;
						
            case 6 : break;
            default: printf("Erreur : votre choix doit être compris entre 1 et 6\n");
        }
    }
    while(choix != 6);
    printf("Au revoir !\n");
    return EXIT_SUCCESS;
}
