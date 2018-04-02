/**
*\file affichage.c
*\brief Fichier contenant les fonctions d'affichage des cercles et de la matrice, et les règles du jeu
*\author Julien Le Roux
*\version 2.0
*\date 01 avril 2018
**/

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Commun/mat_int/gestion_matrice.h"
#include "Commun/mat_int/gestion_othello.h"
#include "Commun/mat_int/joueur.h"
#include "Commun/mat_int/define.h"
#include "Commun/mat_int/min_max_ordi.h"

#include "sdljeu.h"


/** fonction qui affiche un cercle blanc aux coordonnées passées en paramètre	**/

int aff_cercleblanc(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* b, SDL_Window * fenetre){

	int x,y, nb_ret = 0, tab[54];

	SDL_Rect pos;

	pos.x = posx;
	pos.y = posy;
	x = posx/100;
	y = posy/100;

	SDL_Surface *message = NULL;
	SDL_Texture *m,*c1;

	b = IMG_Load("cercleblanc.bmp");

	c1 = SDL_CreateTextureFromSurface(renderer,b);
	SDL_FreeSurface(b); /** puisqu'on a la texture, on peut libérer la surface **/


	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("Roboto-Black.ttf", 15); /** police de taille 30  **/

	SDL_Color c_rouge = {255, 0, 0};/** déclaration des couleurs  **/
	/*if(fenetre){} */
    if(peut_jouer(mat,BLANC) == 0 && peut_jouer(mat,NOIR) == 0){
		pos.x = 820;
        pos.y = 300;
        if(joueur1.score>joueur2.score){
				printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur);
        }
        else if(joueur1.score<joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur);
        }
        else if(joueur1.score == joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le resultat est ex-aequo.\n");
            message = TTF_RenderText_Solid(police, "Fin du jeu ! Le resultat est ex-aequo.",c_rouge);
            m = SDL_CreateTextureFromSurface(renderer,message);
        }

        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);
        return -1;
    }
    else if(peut_jouer(mat, BLANC)== 1){

    	if(coup_possible(mat,BLANC, x,y) == 0){
			pos.x = 820;
        	pos.y = 300;
			printf("\n\tCe coup la n'est pas possible, recliquez autre part\n : ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer ici, choisissez une autre case ! ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
        	return 0;
    	}
    }else if(peut_jouer(mat, BLANC)== 0){
    		pos.x = 820;
        	pos.y = 300;
			printf("\n\tVous ne pouvez pas jouer, vous passez votre tour. ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer, vous passez votre tour. ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
        	return 1;
    }

	system("clear");							/** On nettoie le terminal au debut du tour	**/
		
	printf("\n\tNb de pions blanc %i", joueur2.score); 										/** On affiche le score actuel **/
	printf("\n\tNb de pions noir %i\n", joueur1.score);			
	printf("\n\t%s c'est ton tour (blanc)\n",joueur2.nom_joueur);							/** On indique que c'est le tour du joueur n°2 **/

	lire_mat(mat);
	ecrire_mat(mat,BLANC,x,y);		/** Une fois que l'endroit ou le joueur a décider de jouer est possible on l'ecrit dans la matrice **/
	nb_ret=retourner(mat,BLANC,x,y, tab);
	joueur2.score += (nb_ret+1);
	joueur1.score -= nb_ret;

	printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);
    printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);

    /** on divise par 100 puis on multiplie par 100 pour avec un nombre multiple de 100, et on ajoute 5 pour bien placer le cercle 	**/

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
    return 1;
}


/** fonction qui affiche un cercle noir aux coordonnées passées en paramètre	**/
int aff_cerclenoir(int mat[N][N],t_joueur joueur1,t_joueur joueur2, int posx, int posy, SDL_Renderer *renderer, SDL_Surface* n, SDL_Window * fenetre){


	int x,y,nb_ret = 0, tab[54];

	SDL_Rect pos;
	pos.x = posx;
	pos.y = posy;
	x = posx/100;
	y = posy/100;

	SDL_Surface *message = NULL;
	SDL_Texture *m, *c2;

	n = IMG_Load("cerclenoir.bmp");

	c2 = SDL_CreateTextureFromSurface(renderer,n);
	SDL_FreeSurface(n);

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("Roboto-Black.ttf", 15); /** police de taille 30  **/

	SDL_Color c_rouge = {255, 0, 0};/** déclaration des couleurs  **/

	/** if(fenetre){}	**/

    if(peut_jouer(mat,BLANC) == 0 && peut_jouer(mat,NOIR) == 0){
        pos.x = 820;
        pos.y = 300;
        if(joueur1.score>joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur);
        }
        else if(joueur1.score<joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur);
        }
        else if(joueur1.score == joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Le résultat est ex-aequo !\n");
            message = TTF_RenderText_Solid(police, "Fin du jeu ! Le résultat est ex_aequo.",c_rouge);
            m = SDL_CreateTextureFromSurface(renderer,message);
        }

        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);
        return -1;
    }
    else if(peut_jouer(mat, NOIR)== 1){

    	if(coup_possible(mat,NOIR, x,y) == 0){
			pos.x = 820;
        	pos.y = 300;
			printf("\n\tCe coup la n'est pas possible, recliquez autre part\n : ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer ici, choisissez une autre case ! ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
        	return 0;
    	}
    }else if(peut_jouer(mat, NOIR)== 0){
    		pos.x = 820;
        	pos.y = 300;
			printf("\n\tVous ne pouvez pas jouer, vous passez votre tour. ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer, vous passez votre tour. ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
        	return 1;
    }

	system("clear");							/** On nettoie le terminal au debut du tour	**/
		
	printf("\n\tNb de pions blanc %i",joueur2.score); 										/** On affiche le score actuel **/
	printf("\n\tNb de pions noir %i\n", joueur1.score);			
	printf("\n\t%s c'est ton tour (noir)\n",joueur1.nom_joueur);							/** On indique que c'est le tour du joueur n°1 **/
    	lire_mat(mat);

	ecrire_mat(mat,NOIR,x,y);		/** Une fois que l'endroit où le joueur a décider de jouer est possible on l'ecrit dans la matrice **/
	nb_ret = retourner(mat,NOIR,x,y, tab);
	joueur1.score += (nb_ret+1);
	joueur2.score -= nb_ret;
	printf("\n\tLe nb de pion(s) retourné(s) est de %i\n",nb_ret);

	pos.x /= 100;
	pos.y /= 100;
	pos.x = (pos.x*100) + 5;
	pos.y = (pos.y*100) + 5;

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
    return 1;
}


/** fonction affichant le signe un cercle noir pour l'ordinateur avec les coordonnées idéaux en fonction de sa vision du jeu via le min-max	**/

int aff_ordi(int mat[N][N],t_joueur joueur1,t_joueur joueur2, SDL_Renderer *renderer, SDL_Surface* n, SDL_Window * fenetre,int nb_coup_prevu, int i){


	int x,y,nb_ret = 0, tab[54];

	SDL_Rect pos;

	SDL_Surface *message = NULL;
	SDL_Texture *m, *c2;

	n = IMG_Load("cerclenoir.bmp");

	c2 = SDL_CreateTextureFromSurface(renderer,n);
	SDL_FreeSurface(n);

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("Roboto-Black.ttf", 15); /** police de taille 30  **/

	SDL_Color c_rouge = {255, 0, 0};/** déclaration des couleurs  **/

	/** if(fenetre){}	**/

    if(peut_jouer(mat,BLANC) == 0 && peut_jouer(mat,NOIR) == 0){
        pos.x = 820;
        pos.y = 300;
        if(joueur1.score>joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur);
        }
        else if(joueur1.score<joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur);
        }
        else if(joueur1.score == joueur2.score){
			printf("\n\tAucun joueur ne peut jouer, Le résultat est ex-aequo !\n");
            message = TTF_RenderText_Solid(police, "Fin du jeu ! Le résultat est ex_aequo.",c_rouge);
            m = SDL_CreateTextureFromSurface(renderer,message);
        }

        SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer,m,NULL,&pos);
        return -1;
    }
    else if(peut_jouer(mat, NOIR)==0){
    		pos.x = 820;
        	pos.y = 300;
			printf("\n\tVous ne pouvez pas jouer, vous passez votre tour. ");
        	message = TTF_RenderText_Solid(police, "Vous ne pouvez pas jouer, vous passez votre tour. ",c_rouge);
        	m = SDL_CreateTextureFromSurface(renderer,message);
        	SDL_QueryTexture(m, NULL, NULL, &pos.w, &pos.h);
        	SDL_RenderCopy(renderer,m,NULL,&pos);
        	return 1;
    }

	system("clear");							/** On nettoie le terminal au debut du tour	**/
	
	if(nb_coup_prevu > (N*N-4-i)){
		tour_ordi(mat, BLANC, (N*N-4-i), &x, &y);
	}
	else{
		tour_ordi(mat, BLANC, (nb_coup_prevu), &x, &y);
	}

	printf("\n\tNb de pions blanc %i",joueur2.score); 										/** On affiche le score actuel **/
	printf("\n\tNb de pions noir %i\n", joueur1.score);			
	printf("\n\t%s c'est ton tour\n",joueur1.nom_joueur);							/** On indique que c'est le tour du joueur n°1 **/
    lire_mat(mat);

	ecrire_mat(mat,NOIR,x,y);		/** Une fois que l'endroit où le joueur a décider de jouer est possible on l'ecrit dans la matrice **/
	nb_ret = retourner(mat,NOIR,x,y, tab);
	joueur1.score += (nb_ret+1);
	joueur2.score -= nb_ret;
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
    return 1;
}


/** fonction permettant d'afficher les règles du jeu	**/
int aff_regle(SDL_Renderer* renderer, SDL_Window* fenetre){

	SDL_RenderClear(renderer);

	int posx, posy;
	SDL_Surface *s1 = NULL,*s2 = NULL,*s3 = NULL,*s4 = NULL,*s5 = NULL,*s6 = NULL, *surf_retour = NULL;
	SDL_Texture *t1, *t2, *t3, *t4, *t5, *t6, *text_retour;

	SDL_Color c_bleu = {38, 196, 236}, c_vert = {22, 184, 78};

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	TTF_Font *police2 = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("Roboto-Black.ttf", 25); /** police de taille 30  **/
	police2 = TTF_OpenFont("Roboto-Black.ttf", 25); /** police de taille 30  **/

	s1 = TTF_RenderText_Solid(police, "L'Othello est un jeu de strategie.", c_bleu);
	s2 = TTF_RenderText_Solid(police, "Chaque joueur a une couleur de piece, et doit en avoir le plus a la fin du jeu.", c_bleu);
	s3 = TTF_RenderText_Solid(police, "Pour obtenir plus de pieces, il doit 'manger' les pieces de son adversaire.", c_bleu);
	s4 = TTF_RenderText_Solid(police, "Pour cela, il faut que deux de ses pieces entourent l'une des pieces de l'adversaire.", c_bleu);
	s5 = TTF_RenderText_Solid(police, "Si c'est le cas, la piece de l'adversaire se transforme en la couleur du joueur.", c_bleu);
	s6 = TTF_RenderText_Solid(police, "Et ainsi de suite pour l'adversaire.", c_bleu);

	/*fond = IMG_Load("image.bmp");*/

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

		surf_retour = TTF_RenderText_Solid(police2,"<- Retour au MENU ->", c_vert);
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

    	n = IMG_Load("cerclenoir.bmp");
    	b = IMG_Load("cercleblanc.bmp");

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

	police = TTF_OpenFont("Roboto-Black.ttf", 30); /** police de taille 30  **/
	police2 = TTF_OpenFont("Roboto-Black.ttf", 60); /** police de taille 60 **/

	if(police == NULL || police2 == NULL){
		printf("ERROR police \n");
	}
	/** déclaration des messages pour les surfaces **/

	texte = TTF_RenderUTF8_Solid(police, "Jouer en 1 contre 1",c_bleu);
	texte1 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau facile",c_orange);
	texte2 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau medium",c_orange2);
	texte3 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau difficile",c_jaune);
	texte4 = TTF_RenderUTF8_Solid(police, "Jouer avec l'IA en niveau impossible",c_rouge);

	/** appel des surfaces dans les textures    **/

    texture = SDL_CreateTextureFromSurface(renderer, texte);
	texture1 = SDL_CreateTextureFromSurface(renderer, texte1);
	texture2 = SDL_CreateTextureFromSurface(renderer, texte2);
	texture3 = SDL_CreateTextureFromSurface(renderer, texte3);
	texture4 = SDL_CreateTextureFromSurface(renderer, texte4);

	surf_retour = TTF_RenderText_Solid(police,"<- Retour au MENU ->", c_vert);
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
								lancer_jeu2(renderer, fenetre, 3);
							}else if(clic(event.motion.x, event.motion.y, &r2)){
								lancer_jeu2(renderer, fenetre, 5);
							}else if(clic(event.motion.x, event.motion.y, &r3)){
								lancer_jeu2(renderer, fenetre, 7);
							}else if(clic(event.motion.x, event.motion.y, &r4)){
								lancer_jeu2(renderer, fenetre, (N*N)-4);
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