/**
*\file sdljeu.c
*\brief Fichier contenant les fonctions d'affichage des différents menus et les fonctions qui lancent les différents niveaux du jeu 
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
//mingw32-make -f makefile

#include "Commun/mat_int/gestion_matrice.h"
#include "Commun/mat_int/gestion_othello.h"
#include "Commun/mat_int/joueur.h"
#include "Commun/mat_int/define.h"
#include "affichage.h"


/** fonction permettant de voir si on a cliqué sur une zone passée en paramètre    **/

int clic(int x, int y, struct SDL_Rect *rect){
	if((x >= rect->x) && (x < (rect->x + rect->w)) && (y >= rect->y) && (y < (rect->y + rect->h)))
		return 1;
	return 0;
}

/* fonction qui lance le jeu permettant de jouer en 1 contre 1	**/

int lancer_jeu1(SDL_Renderer* renderer, SDL_Window* fenetre){


	int posx,posy;   /** déclaration variables position x et y pour le curseur  **/
    int i = 1, mat[N][N];

	t_joueur joueur1;
	t_joueur joueur2;

	system("clear");
	printf("\nBIENVENUE AU JEU DE L'OTHELLO\n\n");
	sleep(1);

	joueur1.score = 2;					/** Initialisation des scores des joueurs	**/
	joueur2.score = 2;

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("Roboto-Black.ttf", 30); /** police de taille 30  **/


	SDL_Color c_noir = {0, 0, 0};
    SDL_Surface *retour = NULL;  /** création de variables surfaces pour afficher du texte ou des 	images **/
    SDL_Texture *retourr;  /** creation de textures pour affichages du texte **/

    SDL_Rect ret;
	ret.x = 900;
	ret.y = 10;

	/** déclarations variables pour score et prénoms pour affichage **/
    SDL_Surface *b = NULL, *n = NULL;

    /** si la fenetre est ouverte   **/
	retour = TTF_RenderText_Solid(police, "Retour au Menu",c_noir);
    retourr = SDL_CreateTextureFromSurface(renderer, retour);

	if(fenetre)
	{

        printf("\n\tJoueur n°1 entrez votre pseudo : ");
		scanf("%s%*c",joueur1.nom_joueur);
		printf("\n\tJoueur n°2 entrez votre pseudo : ");
		scanf("%s%*c",joueur2.nom_joueur);

		init_mat(mat); /** initialistation et affichage de la matrice dans le terminal	**/
		lire_mat(mat);

		SDL_RenderClear(renderer); /** nettoyage de l'écran	**/

		aff_mat(renderer, fenetre);

		SDL_QueryTexture(retourr, NULL, NULL, &ret.w, &ret.h); /** affichage du bouton retour 	**/
        SDL_RenderCopy(renderer,retourr,NULL,&ret);

    	int cont = 1;

        while(cont){

            SDL_Event event; /** création variable pour les évèenements de la souris	**/

            while(SDL_PollEvent(&event)){  /** tant qu'on à un évènement de la souris 	**/
                switch(event.type){
					case SDL_QUIT: cont = 0;
								   break;
                    case SDL_MOUSEBUTTONDOWN:  /** relachement de la souris **/

						posx=event.motion.x;
                        posy=event.motion.y;
		
						if(clic(posx,posy,&ret)){
                                cont = 0;
                                break;
                        }
                        if(i%2 !=0){

                            if(aff_cercleblanc(mat,joueur1,joueur2,posx,posy,renderer,b, fenetre)==1){
                                i++;
                            }
                            else if(aff_cercleblanc(mat,joueur1,joueur2,posx,posy,renderer,b, fenetre)==-1){ /** si on ne peut plus jouer on quitte 	**/
                                sleep(15);
                                cont = 0;
                                break;
                            }
                        }
						else{
                            if(aff_cerclenoir(mat,joueur1,joueur2,posx,posy,renderer,n, fenetre)==1){
                                i++;
                            }
                            else if(aff_cerclenoir(mat,joueur1,joueur2,posx,posy,renderer,n, fenetre)==-1){
                                sleep(15);
								cont = 0;
                                break;
                            }
                        }

                }
				SDL_RenderPresent(renderer); /** appel du renderer pour les affichages 	**/
            }
        }

	}else{
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	IMG_Quit();
    return 0;
}


/* fonction qui lance le jeu permettant de jouer contre l'ordi avec en paramètre le niveau de difficulté	**/
int lancer_jeu2(SDL_Renderer* renderer, SDL_Window* fenetre, int nb_coup_prevu){


	int posx,posy;   /** déclaration variables position x et y pour le curseur  **/
    int i = 1, mat[N][N];

	t_joueur joueur1;
	t_joueur joueur2;

	system("clear");
	printf("\nBIENVENUE AU JEU DE L'OTHELLO\n\n");
	sleep(1);

	joueur1.score = 2;					/** Initialisation des scores des joueurs	**/
	joueur2.score = 2;

	TTF_Font *police = NULL;  /** declaration pointeurs vers différentes polices   **/
	police = TTF_OpenFont("Roboto-Black.ttf", 30); /** police de taille 30  **/


	SDL_Color c_noir = {0, 0, 0};
    SDL_Surface *retour = NULL;  /** création de variables surfaces pour afficher du texte ou des 	images **/
    SDL_Texture *retourr;  /** creation de textures pour affichages du texte **/

    SDL_Rect ret;
	ret.x = 900;
	ret.y = 10;

	/** déclarations variables pour score et prénoms pour affichage **/
    SDL_Surface *b = NULL, *n = NULL;

    /** si la fenetre est ouverte   **/
	retour = TTF_RenderText_Solid(police, "Retour au Menu",c_noir);
    retourr = SDL_CreateTextureFromSurface(renderer, retour);

	if(fenetre)
	{

        joueur2.nom_joueur[0] = 'O';
        joueur2.nom_joueur[1] = 'r';
        joueur2.nom_joueur[2] = 'd';
        joueur2.nom_joueur[3] = 'i';
        joueur2.nom_joueur[4] = '\0';
            			
        printf("\n\tJoueur entrez votre pseudo : ");
		scanf("%s%*c",joueur1.nom_joueur);

		init_mat(mat); /** initialistation et affichage de la matrice dans le terminal	**/
		lire_mat(mat);

		SDL_RenderClear(renderer); /** nettoyage de l'écran	**/

		aff_mat(renderer, fenetre);

		SDL_QueryTexture(retourr, NULL, NULL, &ret.w, &ret.h); /** affichage du bouton retour 	**/
        SDL_RenderCopy(renderer,retourr,NULL,&ret);

    	int cont = 1;

        while(cont){

            SDL_Event event; /** création variable pour les évèenements de la souris	**/

            while(SDL_PollEvent(&event)){  /** tant qu'on à un évènement de la souris 	**/
                switch(event.type){
					case SDL_QUIT: cont = 0;
								   break;
                    case SDL_MOUSEBUTTONDOWN:  /** relachement de la souris **/

						posx=event.motion.x;
                        posy=event.motion.y;
		
						if(clic(posx,posy,&ret)){
                                cont = 0;
                                break;
                        }
                        if(i%2 !=0){

                            if(aff_cercleblanc(mat,joueur1,joueur2,posx,posy,renderer,b, fenetre)==1){
                                i++;
                            }
                            else if(aff_cercleblanc(mat,joueur1,joueur2,posx,posy,renderer,b, fenetre)==-1){ /** si on ne peut plus jouer on quitte 	**/
                                sleep(15);
                                cont = 0;
                                break;
                            }
                        }
						else{
                            if(aff_ordi(mat,joueur1,joueur2,renderer,n, fenetre,nb_coup_prevu, i)==1){
                                i++;
                            }
                            else if(aff_ordi(mat,joueur1,joueur2,renderer,n, fenetre,nb_coup_prevu, i)==-1){
                                sleep(15);
								cont = 0;
                                break;
                            }
                        }

                }
				SDL_RenderPresent(renderer); /** appel du renderer pour les affichages 	**/
            }
        }

	}else{
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	IMG_Quit();
    return 0;
}


/** fonction affichant le principal  **/
int aff_menu(SDL_Renderer* renderer, SDL_Window* fenetre, int j){

    SDL_Surface *texte = NULL, *texte1 = NULL, *texte2 = NULL, *texte3 = NULL;  /** création de variables surfaces pour afficher du texte ou des images **/
    SDL_Texture *texture, *texture1, *texture2, *texture3;  /** creation de textures pour affichages du texte **/
	SDL_Rect pos,r1,r2,r3;  /** déclaration rectangle pos pour position du curseur **/

	SDL_Color c_vert = {22, 184, 78};

	if(j==0){
		if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        	fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        	exit(EXIT_FAILURE);
    	}

		fenetre = SDL_CreateWindow("Interface graphique de l'othello" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1150 , 800 , 0);  /** la fenetre prend des dimensions et un titre  **/
		renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /** Création du renderer    **/
		SDL_Surface* surface = NULL;
		surface = SDL_LoadBMP("image.bmp"); /** telechargement icone de l'othello   **/
		SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello  **/


		/** Initialisation TTF : si ca ne marche pas, affichage message d'erreur **/
		SDL_SetRenderDrawColor(renderer, 206, 206, 206, 255);

		if(TTF_Init() == -1) {
			fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
	}

	TTF_Font *police = NULL, *police2 = NULL;  /** declaration pointeurs vers différentes polices   **/

	police = TTF_OpenFont("Roboto-Black.ttf", 30); /** police de taille 30  **/
	police2 = TTF_OpenFont("Roboto-Black.ttf", 60); /** police de taille 60 **/

	if(police == NULL || police2 == NULL){
		printf("ERROR police \n");
	}

	/** déclaration des messages pour les surfaces **/

	texte1 = TTF_RenderUTF8_Solid(police2, "L'OTHELLO",c_vert);
	texte = TTF_RenderUTF8_Solid(police, "Jouer",c_vert);
	texte2 = TTF_RenderUTF8_Solid(police, "Regles du jeu",c_vert);
	texte3 = TTF_RenderUTF8_Solid(police, "QUITTER",c_vert);

	/** appel des surfaces dans les textures    **/

    texture = SDL_CreateTextureFromSurface(renderer, texte1);
	texture1 = SDL_CreateTextureFromSurface(renderer, texte);
	texture2 = SDL_CreateTextureFromSurface(renderer, texte2);
	texture3 = SDL_CreateTextureFromSurface(renderer, texte3);


	if(fenetre)
	{

		pos.x = 400;
		pos.y = 100;
		pos.w = 200;
		pos.h = 30;
		SDL_RenderClear(renderer);


        	/** appel du premier message    **/

		SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer,texture,NULL,&pos);

        	/** ainsi de suite pour les autres messages **/

		r1.x = 400;
		r1.y = 300;

		SDL_QueryTexture(texture1, NULL, NULL, &r1.w, &r1.h);
		SDL_RenderCopy(renderer,texture1,NULL,&r1);

		r2.x = 400;
		r2.y = 400;

		SDL_QueryTexture(texture2, NULL, NULL, &r2.w, &r2.h);
		SDL_RenderCopy(renderer,texture2,NULL,&r2);

		r3.x = 400;
		r3.y = 500;

		SDL_QueryTexture(texture3, NULL, NULL, &r3.w, &r3.h);
		SDL_RenderCopy(renderer,texture3,NULL,&r3);


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
							if(clic(event.motion.x, event.motion.y, &r1)){
								aff_menu_jouer(renderer,fenetre);
								cont = 0;
							}else if(clic(event.motion.x, event.motion.y, &r2)){
								aff_regle(renderer, fenetre);
							}else if(clic(event.motion.x, event.motion.y, &r3)){
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
	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_CloseFont(police2); /* Doit être avant TTF_Quit() */
	TTF_Quit();
	SDL_Quit();

	return 1;
}
