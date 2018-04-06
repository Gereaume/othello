/**
*\file affichage.c
*\brief Fichier contenant les fonctions d'affichage des cercles et de la matrice, et les règles du jeu
*\author Julien Le Roux
*\version 2.0
*\date 01 avril 2018
**/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Commun/Gestion_matrice_test/gestion_matrice.h"
#include "Commun/Gestion_matrice_test/gestion_othello.h"
#include "Commun/Gestion_matrice_test/joueur.h"
#include "Commun/Gestion_matrice_test/define.h"
#include "Commun/Gestion_matrice_test/min_max_ordi.h"

#include "sdljeu.h"
#include "affichage.h"

/** fonction qui affiche un cercle blanc aux coordonnées passées en paramètre	**/

int aff_cercleblanc(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* b, SDL_Window * fenetre){

	int x,y, nb_ret = 0, tab[54];

	SDL_Rect pos;

	char chaine[1000], totblanc[1000], totnoir[1000], tour[1000], nbpion[1000];
	pos.x = posx;
	pos.y = posy;
	x = posx/100;
	y = posy/100;

	SDL_Surface *message = NULL;
	SDL_Texture *m,*c1;

	b = IMG_Load("objet/cercleblanc.bmp");

	c1 = SDL_CreateTextureFromSurface(renderer,b);
	SDL_FreeSurface(b); /** puisqu'on a la texture, on peut libérer la surface **/


	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("objet/Roboto-Black.ttf", 20); /** police de taille 30  **/

	SDL_Color c_rouge = {255, 0, 0},c_bleu = {38, 196, 236};/** déclaration des couleurs  **/


   
    if(peut_jouer(mat, BLANC)== 1){

    	if(coup_possible(mat,BLANC, x,y) == 0){
		pos.x = 805;
        	pos.y = 300;
		printf("\n\tCe coup la n'est pas possible, recliquez autre part\n : ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer ici. ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
	
        	return 0;
    	}
    }else if(peut_jouer(mat, BLANC)== 0){
    		pos.x = 805;
        	pos.y = 200;
		printf("\n\tVous ne pouvez pas jouer, vous passez votre tour. ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer.",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		pos.x = 805;
        	pos.y = 250;
        	message = TTF_RenderText_Solid(police, "Vous passez votre tour.",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
        	return 1;
    }

	sprintf(totblanc,"Nb de pions blanc(s) : %i", joueur2.score);
	sprintf(totnoir,"Nb de pions noir(s) : %i", joueur1.score);
	sprintf(tour,"%s a toi de jouer", joueur1.nom_joueur);

	system("clear");							/** On nettoie le terminal au debut du tour	**/


	lire_mat(mat);
	ecrire_mat(mat,BLANC,x,y);		/** Une fois que l'endroit ou le joueur a décider de jouer est possible on l'ecrit dans la matrice **/
	nb_ret=retourner(mat,BLANC,x,y, tab);
	joueur2.score += (nb_ret+1);
	joueur1.score -= nb_ret;
	SDL_FreeSurface(message);

	pos.x = 805;
        pos.y = 400;

	message = TTF_RenderText_Solid(police, totblanc,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);
	SDL_FreeSurface(message);

	pos.x = 805;
        pos.y = 450;

	message = TTF_RenderText_Solid(police, totnoir,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);

	SDL_FreeSurface(message);

	pos.x = 805;
        pos.y = 500;

	message = TTF_RenderText_Solid(police, tour,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);

	SDL_FreeSurface(message);

	printf("\n\tNb de pions blanc %i", joueur2.score); 										/** On affiche le score actuel **/
	printf("\n\tNb de pions noir %i\n", joueur1.score);			
	printf("\n\t%s c'est ton tour (blanc)\n",joueur2.nom_joueur);							/** On indique que c'est le tour du joueur n°2 **/


	sprintf(nbpion,"nb pions retournes = %i", nb_ret);

	pos.x = 805;
        pos.y = 550;

	message = TTF_RenderText_Solid(police, nbpion,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);

	SDL_FreeSurface(message);

	printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);

    /** on divise par 100 puis on multiplie par 100 pour avec un nombre multiple de 100, et on ajoute 5 pour bien placer le cercle 	**/

	pos.x = posx;
	pos.y = posy;

	pos.x /= 100;
	pos.y /= 100;
	pos.x = (pos.x*100) + 5;
	pos.y = (pos.y*100) + 5;

	/** appel du cercle pour l'affichage 	**/

    SDL_QueryTexture(c1, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer,c1,NULL,&pos);

	int a = 0;

	while(a<54){
		if(tab[a]!=0 && tab[a+1]!=0){
			pos.x = tab[a];
			pos.y = tab[a+1];
			SDL_QueryTexture(c1, NULL, NULL, &pos.w, &pos.h);
    		SDL_RenderCopy(renderer,c1,NULL,&pos);
		}
		a = a+2;
	}

    if(peut_jouer(mat,BLANC) == 0 && peut_jouer(mat,NOIR) == 0){
	pos.x = 805;
        pos.y = 600;
        if(joueur1.score>joueur2.score){
		printf("Aucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur);
		sprintf(chaine,"Le gagnant est %s.", joueur1.nom_joueur);

		message = TTF_RenderText_Solid(police, "Aucun joueur ne peut jouer, Fin du jeu !" ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

		SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		pos.x = 805;
        	pos.y = 650;

		message = TTF_RenderText_Solid(police, chaine ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

        }
        else if(joueur1.score<joueur2.score){
		printf("Aucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur);
		sprintf(chaine,"Le gagnant est %s.", joueur2.nom_joueur);

		message = TTF_RenderText_Solid(police, "Aucun joueur ne peut jouer, Fin du jeu !" ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

		SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		pos.x = 805;
        	pos.y = 650;

		message = TTF_RenderText_Solid(police, chaine ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);
        }
        else if(joueur1.score == joueur2.score){
	    printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le resultat est ex-aequo.\n");
            message = TTF_RenderText_Solid(police, "Fin du jeu ! Le resultat est ex-aequo.",c_rouge);
            m = SDL_CreateTextureFromSurface(renderer,message);
	    SDL_FreeSurface(message);
        }

        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);
        return -1;
    }
    return 1;
}


/** fonction qui affiche un cercle noir aux coordonnées passées en paramètre	**/
int aff_cerclenoir(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* n, SDL_Window * fenetre){


	int x,y,nb_ret = 0, tab[54];

	char chaine[1000], totblanc[1000],totnoir[1000],nbpion[1000],tour[1000];
	SDL_Rect pos;
	pos.x = posx;
	pos.y = posy;
	x = posx/100;
	y = posy/100;

	SDL_Surface *message = NULL;
	SDL_Texture *m, *c2;

	n = IMG_Load("objet/cerclenoir.bmp");

	c2 = SDL_CreateTextureFromSurface(renderer,n);
	SDL_FreeSurface(n);

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("objet/Roboto-Black.ttf", 20); /** police de taille 30  **/

	SDL_Color c_rouge = {255, 0, 0}, c_bleu = {38, 196, 236};/** déclaration des couleurs  **/

    if(peut_jouer(mat, NOIR)== 1){

    	if(coup_possible(mat,NOIR, x,y) == 0){
		pos.x = 805;
        	pos.y = 300;
		printf("\n\tCe coup la n'est pas possible, recliquez autre part\n : ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer ici.",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

        	return 0;
    	}
    }else if(peut_jouer(mat, NOIR)== 0){
    		pos.x = 805;
        	pos.y = 200;
		printf("\n\tVous ne pouvez pas jouer, vous passez votre tour. ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer.",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
		pos.x = 805;
        	pos.y = 250;
		message = TTF_RenderText_Solid(police, "Vous passez votre tour. ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

        	return -2;
    }

	system("clear");							/** On nettoie le terminal au debut du tour	**/
	

	sprintf(totblanc,"Nb de pions blanc(s) : %i", joueur2.score);
	sprintf(totnoir,"Nb de pions noir(s) : %i", joueur1.score);
	sprintf(tour,"%s a toi de jouer", joueur2.nom_joueur);

	lire_mat(mat);
	ecrire_mat(mat,NOIR,x,y);		/** Une fois que l'endroit ou le joueur a décider de jouer est possible on l'ecrit dans la matrice **/
	nb_ret=retourner(mat,NOIR,x,y, tab);
	joueur1.score += (nb_ret+1);
	joueur2.score -= nb_ret;

	SDL_FreeSurface(message);



	pos.x = 805;
        pos.y = 400;

	message = TTF_RenderText_Solid(police, totblanc,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);

	SDL_FreeSurface(message);

	pos.x = 805;
        pos.y = 450;

	message = TTF_RenderText_Solid(police, totnoir,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);

	SDL_FreeSurface(message);

	pos.x = 805;
        pos.y = 500;

	message = TTF_RenderText_Solid(police, tour,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);

	SDL_FreeSurface(message);

	printf("\n\tNb de pions blanc %i", joueur2.score); 										/** On affiche le score actuel **/
	printf("\n\tNb de pions noir %i\n", joueur1.score);			
	printf("\n\t%s c'est ton tour (noir)\n",joueur1.nom_joueur);							/** On indique que c'est le tour du joueur n°2 **/


	sprintf(nbpion,"nb pions retournes = %i", nb_ret);

	pos.x = 805;
        pos.y = 550;

	message = TTF_RenderText_Solid(police, nbpion,c_bleu);
        m = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);

	SDL_FreeSurface(message);

	printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);

    /** on divise par 100 puis on multiplie par 100 pour avec un nombre multiple de 100, et on ajoute 5 pour bien placer le cercle 	**/

	pos.x = posx;
	pos.y = posy;

	pos.x /= 100;
	pos.y /= 100;
	pos.x = (pos.x*100) + 5;
	pos.y = (pos.y*100) + 5;

	/** appel du cercle pour l'affichage 	**/

    SDL_QueryTexture(c2, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer,c2,NULL,&pos);

	int a = 0;

	while(a<54){
		if(tab[a]!=0 && tab[a+1]!=0){
			pos.x = tab[a];
			pos.y = tab[a+1];
			SDL_QueryTexture(c2, NULL, NULL, &pos.w, &pos.h);
    			SDL_RenderCopy(renderer,c2,NULL,&pos);
		}
		a = a+2;
	}

    if(peut_jouer(mat,BLANC) == 0 && peut_jouer(mat,NOIR) == 0){
	pos.x = 805;
        pos.y = 600;
        if(joueur1.score>joueur2.score){
		printf("Aucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur);
		sprintf(chaine,"Le gagnant est %s.", joueur1.nom_joueur);

		message = TTF_RenderText_Solid(police, "Aucun joueur ne peut jouer, Fin du jeu !" ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

		SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		pos.x = 805;
        	pos.y = 650;

		message = TTF_RenderText_Solid(police, chaine ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

        }
        else if(joueur1.score<joueur2.score){
		printf("Aucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur);
		sprintf(chaine,"Le gagnant est %s.", joueur2.nom_joueur);

		message = TTF_RenderText_Solid(police, "Aucun joueur ne peut jouer, Fin du jeu !" ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

		SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		pos.x = 805;
        	pos.y = 650;

		message = TTF_RenderText_Solid(police, chaine ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);
        }
        else if(joueur1.score == joueur2.score){
	    printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le resultat est ex-aequo.\n");
            message = TTF_RenderText_Solid(police, "Fin du jeu ! Le resultat est ex-aequo.",c_rouge);
            m = SDL_CreateTextureFromSurface(renderer,message);
	    SDL_FreeSurface(message);
        }

        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);
        return -1;
    }
    return 1;
}


/** fonction affichant le signe un cercle noir pour l'ordinateur avec les coordonnées idéaux en fonction de sa vision du jeu via le min-max	**/

int aff_ordi(int mat[N][N],t_joueur joueur1,t_joueur joueur2, SDL_Renderer *renderer, SDL_Surface* b, SDL_Window * fenetre,int nb_coup_prevu, int j){

	int x=0,y=0,nb_ret = 0, tab[54];

	char chaine[1000],totblanc[1000],totnoir[1000],nbpion[1000],tour[1000];
	SDL_Rect pos;

	SDL_Surface *message = NULL;
	SDL_Texture *m, *c2;

	b = IMG_Load("objet/cercleblanc.bmp");

	c2 = SDL_CreateTextureFromSurface(renderer,b);
	SDL_FreeSurface(b);

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("objet/Roboto-Black.ttf", 20); /** police de taille 30  **/

	SDL_Color c_rouge = {255, 0, 0}, c_bleu = {38, 196, 236};/** déclaration des couleurs  **/


    	if(peut_jouer(mat, NOIR)== 1){
    		if(nb_coup_prevu > (N*N-4-j)){
			tour_ordi(mat, BLANC, (N*N-4-j), &x, &y);
		}
		else{
			tour_ordi(mat, BLANC, nb_coup_prevu, &x, &y);
		}
		system("clear");							/** On nettoie le terminal au debut du tour	**/
	

		sprintf(totblanc,"Nb de pions blanc(s) : %i", joueur2.score);
		sprintf(totnoir,"Nb de pions noir(s) : %i", joueur1.score);
		sprintf(tour,"%s a toi de jouer", joueur1.nom_joueur);

		lire_mat(mat);
		ecrire_mat(mat,BLANC,x,y);		/** Une fois que l'endroit ou le joueur a décider de jouer est possible on l'ecrit dans la matrice **/
		nb_ret=retourner(mat,BLANC,x,y, tab);
		joueur2.score += (nb_ret+1);
		joueur1.score -= nb_ret;


		pos.x = 805;
        	pos.y = 400;

		message = TTF_RenderText_Solid(police, totblanc,c_bleu);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
		
		SDL_FreeSurface(message);

		pos.x = 805;
        	pos.y = 450;

		message = TTF_RenderText_Solid(police, totnoir,c_bleu);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		SDL_FreeSurface(message);

		pos.x = 805;
        	pos.y = 500;

		message = TTF_RenderText_Solid(police, tour,c_bleu);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		SDL_FreeSurface(message);

		printf("\n\tNb de pions blanc %i", joueur2.score); 										/** On affiche le score actuel **/
		printf("\n\tNb de pions noir %i\n", joueur1.score);			
		printf("\n\t%s c'est ton tour (noir)\n",joueur2.nom_joueur);							/** On indique que c'est le tour du joueur n°2 **/

		sprintf(nbpion,"nb pions retournes = %i", nb_ret);

		pos.x = 805;
        	pos.y = 550;

		message = TTF_RenderText_Solid(police, nbpion,c_bleu);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		SDL_FreeSurface(message);

		printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);

		pos.x = (x * 100) + 5;
		pos.y = (y * 100) + 5;

    		SDL_QueryTexture(c2, NULL, NULL, &pos.w, &pos.h);
    		SDL_RenderCopy(renderer,c2,NULL,&pos);

		int a = 0;
		while(a<54){
			if(tab[a]!=0 && tab[a+1]!=0){
				pos.x = tab[a];
				pos.y = tab[a+1];
				SDL_QueryTexture(c2, NULL, NULL, &pos.w, &pos.h);
    				SDL_RenderCopy(renderer,c2,NULL,&pos);
			}
			a = a+2;
		}
		j++;
		sleep(3);
	}
	else if(peut_jouer(mat, BLANC)==0){
    		pos.x = 805;
        	pos.y = 200;
		printf("\n\tVous ne pouvez pas jouer, vous passez votre tour. ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer.",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
		pos.x = 805;
        	pos.y = 250;
		message = TTF_RenderText_Solid(police, "Vous passez votre tour. ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
        	return 1;
    	}


    if(peut_jouer(mat,BLANC) == 0 && peut_jouer(mat,NOIR) == 0){
	pos.x = 805;
        pos.y = 600;
        if(joueur1.score>joueur2.score){
		printf("Aucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur);
		sprintf(chaine,"Le gagnant est %s.", joueur1.nom_joueur);

		message = TTF_RenderText_Solid(police, "Aucun joueur ne peut jouer, Fin du jeu !" ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

		SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		pos.x = 805;
        	pos.y = 650;

		message = TTF_RenderText_Solid(police, chaine ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

        }
        else if(joueur1.score<joueur2.score){
		printf("Aucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur);
		sprintf(chaine,"Le gagnant est %s.", joueur2.nom_joueur);

		message = TTF_RenderText_Solid(police, "Aucun joueur ne peut jouer, Fin du jeu !" ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);

		SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);

		pos.x = 805;
        	pos.y = 650;

		message = TTF_RenderText_Solid(police, chaine ,c_rouge);
            	m = SDL_CreateTextureFromSurface(renderer,message);
		SDL_FreeSurface(message);
        }
        else if(joueur1.score == joueur2.score){
	    printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le resultat est ex-aequo.\n");
            message = TTF_RenderText_Solid(police, "Fin du jeu ! Le resultat est ex-aequo.",c_rouge);
            m = SDL_CreateTextureFromSurface(renderer,message);
	    SDL_FreeSurface(message);
        }

        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);
        return -1;
    }
    return 1;
}


/** fonction permettant d'afficher les règles du jeu	**/
int aff_regle(SDL_Renderer* renderer, SDL_Window* fenetre){

	SDL_RenderClear(renderer);

	int posx, posy;
	SDL_Surface *s1 = NULL,*s2 = NULL,*s3 = NULL,*s4 = NULL,*s5 = NULL,*s6 = NULL, *s7 = NULL, *s8 = NULL, *s9 = NULL, *s10=NULL, *surf_retour = NULL;
	SDL_Texture *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9,*t10, *text_retour;

	SDL_Color c_bleu = {38, 196, 236}, c_vert = {22, 184, 78};

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/

	police = TTF_OpenFont("objet/Roboto-Black.ttf", 25); /** police de taille 30  **/


	s1 = TTF_RenderText_Solid(police, "L'Othello est un jeu de strategie.", c_bleu);
	s2 = TTF_RenderText_Solid(police, "Chaque joueur a une couleur de pion, et doit en avoir le plus a la fin du jeu.", c_bleu);
	s3 = TTF_RenderText_Solid(police, "Pour obtenir plus de pions, il doit 'manger' les pions de son adversaire.", c_bleu);
	s4 = TTF_RenderText_Solid(police, "Pour cela, il faut que deux de ses pions entourent l'un des pions de l'adversaire.", c_bleu);
	s5 = TTF_RenderText_Solid(police, "Si c'est le cas, le pion de l'adversaire se transforme en la couleur du joueur.", c_bleu);
	s6 = TTF_RenderText_Solid(police, "Et ainsi de suite pour l'adversaire.", c_bleu);
	s7 = TTF_RenderText_Solid(police, "Si un joueur ne peut pas jouer, il passe son tour et l'adversaire joue.", c_bleu);
	s8 = TTF_RenderText_Solid(police, "Si aucun des deux joueurs ne peut jouer la partie est terminee,", c_bleu);
	s9 = TTF_RenderText_Solid(police, "meme si le plateau n'est pas remplis.", c_bleu);
	s10 = TTF_RenderText_Solid(police, "Pour jouer, il faut choisir son niveau puis entrer le ou les prenoms dans le terminal.", c_bleu);

	SDL_Rect rect;

	/** on declare les premières positions pour le premier message  **/
    	rect.x = 250;
    	rect.y = 100;
    	rect.w = 200;
    	rect.h = 30;


	if(fenetre)
	{

		t1 = SDL_CreateTextureFromSurface(renderer, s1);
	
		rect.x = 40; 
		rect.y = 150;

		SDL_QueryTexture(t1, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t1, NULL, &rect);

		t2 = SDL_CreateTextureFromSurface(renderer, s2);

		rect.y = 200;

		SDL_QueryTexture(t2, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t2, NULL, &rect);

		t3 = SDL_CreateTextureFromSurface(renderer, s3);

		rect.y = 250;

		SDL_QueryTexture(t3, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t3, NULL, &rect);

		t4 = SDL_CreateTextureFromSurface(renderer, s4);

		rect.y = 300;

		SDL_QueryTexture(t4, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t4, NULL, &rect);

		t5 = SDL_CreateTextureFromSurface(renderer, s5);

		rect.y = 350;

		SDL_QueryTexture(t5, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t5, NULL, &rect);

		t6 = SDL_CreateTextureFromSurface(renderer, s6);

		rect.y = 400;

		SDL_QueryTexture(t6, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t6, NULL, &rect);

		t7 = SDL_CreateTextureFromSurface(renderer, s7);

		rect.y = 450;

		SDL_QueryTexture(t7, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t7, NULL, &rect);

		t8 = SDL_CreateTextureFromSurface(renderer, s8);

		rect.y = 500;

		SDL_QueryTexture(t8, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t8, NULL, &rect);

		t9 = SDL_CreateTextureFromSurface(renderer, s9);

		rect.y = 550;

		SDL_QueryTexture(t9, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t9, NULL, &rect);

		t10 = SDL_CreateTextureFromSurface(renderer, s10);

		rect.y = 600;

		SDL_QueryTexture(t10, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, t10, NULL, &rect);

		surf_retour = TTF_RenderText_Solid(police,"Retour au MENU", c_vert);
		text_retour = SDL_CreateTextureFromSurface(renderer, surf_retour);

		rect.y = 10;

		SDL_QueryTexture(text_retour, NULL, NULL, &(rect.w), &(rect.h));
		SDL_RenderCopy(renderer, text_retour, NULL, &rect);

		/** mise en place et appel du renderer pour l'affichage  **/
		SDL_RenderPresent(renderer);

        int cont = 1; 
		while(cont) { 
			SDL_Event event; 
			while(SDL_PollEvent(&event)) { 
				switch(event.type) { 
					case SDL_QUIT: cont = 0; 
					break; 
					case SDL_MOUSEBUTTONDOWN:
					    switch (event.button.button)
					    {
						case SDL_BUTTON_LEFT:
							posx = event.motion.x;
							posy = event.motion.y;
							if(clic(posx, posy, &rect)){
								aff_menu(renderer,fenetre, 1);
								cont = 0;
							}
						    break;
					    }
					    break;
				} 
			} 
		}
	 }
	 SDL_DestroyWindow(fenetre);
	 return 1;
}


/** fonction affichant la matrice de base avec initialisation des 4 carrés de départ  **/

int aff_mat(SDL_Renderer* renderer, SDL_Window* fenetre){
	
    SDL_Point ligne_depart,ligne_arrivee; /** Déclaration point de départ et point d'arrivée d'une ligne    **/

    if(renderer == NULL) /** Gestion des erreurs    **/
    {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        return 0;
    }

    if(fenetre){
    	SDL_Rect cases[32]; /** Déclaration du tableau contenant les cases  **/

    	SDL_SetRenderDrawColor( renderer, 22, 184, 78, 255 ); /** Couleur verte	**/

    	SDL_RenderClear(renderer); /** nettoyage de l'ecran **/

    	SDL_SetRenderDrawColor( renderer,22, 184, 78, 255 ); /** Couleur verte	**/

    	cases[0].x = cases[0].y = 0;
    	cases[0].w = cases[0].h = 100;

    	for(int i = 1; i <32; i++)
    	{
        	cases[i].x = cases[i-1].x + 200;
        	cases[i].y = cases[i-1].y;

        	if(i%4 == 0) /** retour à la ligne  **/
        	{
            	cases[i].x = (i%8 == 0) ? 0 : 100;
            	cases[i].y = cases[i-1].y + 100;
        	}
        	cases[i].w = cases[i].h = 100; /** taille d'une case (100 sur 100)  **/
    	}

    	if(SDL_RenderFillRects(renderer,cases,32) <0)  /** Remplissage des cases    **/
    	{
        	printf("Erreur lors des remplissages de rectangles: %s",SDL_GetError());
        	return 0;
    	}

    	SDL_SetRenderDrawColor(renderer,0,0,0,0);/** Couleur noire pour les lignes  **/

    	/** Lignes horizontales **/
    	ligne_depart.x = 0;
    	ligne_arrivee.x = 800;
    	ligne_depart.y = 0;
    	for(int i = 0; i<8; i++)
    	{
        	ligne_depart.y += 100;
        	ligne_arrivee.y = ligne_depart.y;
        	SDL_RenderDrawLine(renderer,ligne_depart.x, ligne_depart.y,ligne_arrivee.x,ligne_arrivee.y); /** appel des lignes horizontales  **/
    	}

    	/** Lignes verticales   **/
    	ligne_depart.x = 0;
    	ligne_depart.y = 0;
    	ligne_arrivee.y = 800;
    	for(int i = 0; i<8; i++)
    	{
        	ligne_depart.x += 100;
        	ligne_arrivee.x = ligne_depart.x;
        	SDL_RenderDrawLine(renderer,ligne_depart.x, ligne_depart.y,ligne_arrivee.x,ligne_arrivee.y);  /** appel des lignes verticales   **/
    	}


    	/** initialisation de la matrice 	**/

    	SDL_Surface *b = NULL, *n = NULL;
    	SDL_Texture *c1,*c2;

    	SDL_Rect pos;

    	n = IMG_Load("objet/cerclenoir.bmp");
    	b = IMG_Load("objet/cercleblanc.bmp");

    	c1 = SDL_CreateTextureFromSurface(renderer,b);
    	SDL_FreeSurface(b); /** puisqu'on a la texture, on peut libérer la surface **/
    	c2 = SDL_CreateTextureFromSurface(renderer,n);
    	SDL_FreeSurface(n);

    	pos.x = 405;
    	pos.y = 305;

    	SDL_QueryTexture(c2, NULL, NULL, &pos.w, &pos.h);
    	SDL_RenderCopy(renderer,c2,NULL,&pos);

    	pos.x = 405;
    	pos.y = 405;

    	SDL_QueryTexture(c1, NULL, NULL, &pos.w, &pos.h);
    	SDL_RenderCopy(renderer,c1,NULL,&pos);

    	pos.x = 305;
    	pos.y = 305;

    	SDL_QueryTexture(c1, NULL, NULL, &pos.w, &pos.h);
    	SDL_RenderCopy(renderer,c1,NULL,&pos);

    	pos.x = 305;
    	pos.y = 405;

    	SDL_QueryTexture(c2, NULL, NULL, &pos.w, &pos.h);
    	SDL_RenderCopy(renderer,c2,NULL,&pos);
		return 1;
    } else {
	fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	return 0;
    }

}





/** fonction affichant le menu pour choisir à quel niveau on veut jouer **/
int aff_menu_jouer(SDL_Renderer* renderer, SDL_Window* fenetre){


	SDL_RenderClear(renderer); /** nettoyage de l'écran et du renderer 	**/

    SDL_Surface *texte = NULL, *texte1 = NULL, *texte2 = NULL, *texte3 = NULL, *texte4 = NULL, *surf_retour = NULL;  /** création de variables surfaces pour afficher du texte ou des images **/
    SDL_Texture *texture, *texture1, *texture2, *texture3, *texture4, *text_retour;  /** creation de textures pour affichages du texte **/

	SDL_Rect pos,r1,r2,r3, r4, ret;  /** déclaration rectangle pos pour position du curseur **/

	SDL_Color c_vert = {22, 184, 78},c_bleu = {0, 0, 255}, c_jaune = {255, 94, 77}, c_orange = {239, 155, 15}, c_orange2 = {237, 127, 16}, c_rouge = {255, 0, 0};

	TTF_Font *police = NULL, *police2 = NULL;  /** declaration pointeurs vers différentes polices   **/

	police = TTF_OpenFont("objet/Roboto-Black.ttf", 30); /** police de taille 30  **/
	police2 = TTF_OpenFont("objet/Roboto-Black.ttf", 60); /** police de taille 60 **/

	if(police == NULL || police2 == NULL){
		printf("ERROR police \n");
	}
	/** déclaration des messages pour les surfaces **/

	texte = TTF_RenderUTF8_Solid(police, "Jouer en 1 contre 1",c_bleu);
	texte1 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau facile",c_orange);
	texte2 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau moyen",c_orange2);
	texte3 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau difficile",c_jaune);
	texte4 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau très difficle",c_rouge);

	/** appel des surfaces dans les textures    **/

    texture = SDL_CreateTextureFromSurface(renderer, texte);
	texture1 = SDL_CreateTextureFromSurface(renderer, texte1);
	texture2 = SDL_CreateTextureFromSurface(renderer, texte2);
	texture3 = SDL_CreateTextureFromSurface(renderer, texte3);
	texture4 = SDL_CreateTextureFromSurface(renderer, texte4);

	surf_retour = TTF_RenderText_Solid(police,"Retour au MENU", c_vert);
	text_retour = SDL_CreateTextureFromSurface(renderer, surf_retour);

	if(fenetre)
	{
	
		pos.x = 250;
		pos.y = 200;
		pos.w = 200;
		pos.h = 30;


        /** appel du premier message    **/

		SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer,texture,NULL,&pos);

        	/** ainsi de suite pour les autres messages **/

		r1.x = 250;
		r1.y = 300;

		SDL_QueryTexture(texture1, NULL, NULL, &r1.w, &r1.h);
		SDL_RenderCopy(renderer,texture1,NULL,&r1);

		r2.x = 250;
		r2.y = 400;

		SDL_QueryTexture(texture2, NULL, NULL, &r2.w, &r2.h);
		SDL_RenderCopy(renderer,texture2,NULL,&r2);

		r3.x = 250;
		r3.y = 500;

		SDL_QueryTexture(texture3, NULL, NULL, &r3.w, &r3.h);
		SDL_RenderCopy(renderer,texture3,NULL,&r3);

		r4.x = 250;
		r4.y = 600;

		SDL_QueryTexture(texture4, NULL, NULL, &r4.w, &r4.h);
		SDL_RenderCopy(renderer,texture4,NULL,&r4);

		ret.x = 40; 
		ret.y = 10;

		SDL_QueryTexture(text_retour, NULL, NULL, &(ret.w), &(ret.h));
		SDL_RenderCopy(renderer, text_retour, NULL, &ret);

		/** mise en place et appel du renderer pour l'affichage  **/
		SDL_RenderPresent(renderer);
        int cont = 1; 

		while(cont) { 
			SDL_Event event; 
			while(SDL_PollEvent(&event)) { 
				switch(event.type) { 
					case SDL_QUIT: 
						cont = 0; 
					break; 
					case SDL_MOUSEBUTTONDOWN:
					    switch (event.button.button)
					    {
						case SDL_BUTTON_LEFT:
							if(clic(event.motion.x, event.motion.y, &pos)){
								lancer_jeu1(renderer, fenetre);
							}else if(clic(event.motion.x, event.motion.y, &r1)){
								lancer_jeu2(renderer, fenetre, 1);
							}else if(clic(event.motion.x, event.motion.y, &r2)){
								lancer_jeu2(renderer, fenetre, 3);
							}else if(clic(event.motion.x, event.motion.y, &r3)){
								lancer_jeu2(renderer, fenetre, 5);
							}else if(clic(event.motion.x, event.motion.y, &r4)){
								lancer_jeu2(renderer, fenetre, 7);
							}else if(clic(event.motion.x, event.motion.y, &ret)){
								aff_menu(renderer, fenetre, 1);
								cont = 0;
							}						
						    break;
					    }
					    break;
				} 
			} 
		}
	}else{
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}
	 SDL_DestroyWindow(fenetre);
	 return 1;
}
