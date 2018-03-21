
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "score.h"
#include "joueur.h"
#include "coup_possible_retourner.h"
#include "gestion_matrice.h"

#define N 8


/** fonction permettant de voir si on a cliqué sur une zone passée en paramètre    **/

int clic(int x, int y, struct SDL_Rect *rect){
	if((x >= rect->x) && (rect->x <= x+rect->w) && (y >= rect->y) && (rect->y <= (y+rect->h)))
		return 1;
	return 0;
}

/** fonction affichant le signe aux positions passées en paramètre si le coup est possible, sinon affiche le message d'erreur   **/
/*void aff_signe(int posx, int posy, SDL_Renderer *renderer, SDL_Texture * text){
	SDL_Rect position;
	position.x = posx;
	position.y = posy;
	SDL_Surface *message = NULL;
	SDL_Texture *m;

    if(text == cercle){
        if(coup_possible(mat, blanc, posx, posy) == 0 && coup_possible(mat, noir,posx,posy) == 0){
            position.x = 900;
            position.y = 300;
            if(joueur1.score>joueur2.score){
                message = TTF_RenderText_Solid(police2, "Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur ,rouge);
                m = SDL_CreateTextureFromSurface(renderer,message);
            }
            else if(joueur1.score<joueur2.score){
                message = TTF_RenderText_Solid(police2, "Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur ,rouge);
                m = SDL_CreateTextureFromSurface(renderer,message);
            }
            else{
                message = TTF_RenderText_Solid(police2, "Fin du jeu ! Le résultat est ex_aequo.",rouge);
                m = SDL_CreateTextureFromSurface(renderer,message);
            }

            SDL_QueryTexture(m, NULL, NULL, &position.w, &position.h);
            SDL_RenderCopy(renderer,m,NULL,&position);
            return -1;
        }
        else if(coup_possible(mat, blanc, posx,posy)==0){
            position.x = 900;
            position.y = 300;
            message = TTF_RenderText_Solid(police2, "Vous ne pouvez pas jouer ici, choisissez une autre case ! ",rouge);
            m = SDL_CreateTextureFromSurface(renderer,message);
            SDL_QueryTexture(m, NULL, NULL, &position.w, &position.h);
            SDL_RenderCopy(renderer,m,NULL,&position);
            return 0;
        }
    }
    else{
        if(coup_possible(mat, blanc, posx, posy) == 0 && coup_possible(mat, noir,posx,posy) == 0){
            position.x = 900;
            position.y = 300;
            if(joueur1.score>joueur2.score){
                message = TTF_RenderText_Solid(police2, "Fin du jeu ! Le gagnant est %s.", joueur1.nom_joueur ,rouge);
                m = SDL_CreateTextureFromSurface(renderer,message);
            }
            else if(joueur1.score<joueur2.score){
                message = TTF_RenderText_Solid(police2, "Fin du jeu ! Le gagnant est %s.", joueur2.nom_joueur ,rouge);
                m = SDL_CreateTextureFromSurface(renderer,message);
            }
            else{
                message = TTF_RenderText_Solid(police2, "Fin du jeu ! Le résultat est ex_aequo.",rouge);
                m = SDL_CreateTextureFromSurface(renderer,message);
            }

            SDL_QueryTexture(m, NULL, NULL, &position.w, &position.h);
            SDL_RenderCopy(renderer,m,NULL,&position);
            return -1;
        }
        else{
            if(coup_possible(mat, noir, posx,posy)==0){
                position.x = 900;
                position.y = 300;
                message = TTF_RenderText_Solid(police2, "Vous ne pouvez pas jouer ici, choisissez une autre case ! ",rouge);
                m = SDL_CreateTextureFromSurface(renderer,message);
                SDL_QueryTexture(m, NULL, NULL, &position.w, &position.h);
                SDL_RenderCopy(renderer,m,NULL,&position);
                return 0;
        }
    }
    SDL_QueryTexture(text, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,text,NULL,&position);
    return 1;

}*/

/** fonction initialisation la matrice avec les 4 premiers signes au centre **/
/*
int init(SDL_Renderer *renderer){
    aff_signe(500,400,renderer,c1);
    aff_signe(500,500,renderer,c1);
    aff_signe(400,400,renderer,c2);
    aff_signe(400,500,renderer,c2);
}
*/

/** fonction affichant la matrice 8x8 vide  **/

int aff_mat(SDL_Renderer* renderer){

	SDL_Point ligne_depart,ligne_arrivee; /** Déclaration point de départ et point d'arrivée d'une ligne    **/

    if(renderer == NULL) /** Gestion des erreurs    **/
    {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        return 0;
    }

    SDL_Rect cases[32]; /** Déclaration du tableau contenant les cases  **/

	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); /** Couleur verte	**/

    SDL_RenderClear(renderer); /** nettoyage de l'ecran **/

    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); /** Couleur verte	**/

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
    for(int i = 0; i<7; i++)
    {
        ligne_depart.y += 100;
        ligne_arrivee.y = ligne_depart.y;
        SDL_RenderDrawLine(renderer,ligne_depart.x, ligne_depart.y,ligne_arrivee.x,ligne_arrivee.y); /** appel des lignes horizontales  **/
    }

    /** Lignes verticales   **/
    ligne_depart.x = 0;
    ligne_depart.y = 0;
    ligne_arrivee.y = 800;
    for(int i = 0; i<7; i++)
    {
        ligne_depart.x += 100;
        ligne_arrivee.x = ligne_depart.x;
        SDL_RenderDrawLine(renderer,ligne_depart.x, ligne_depart.y,ligne_arrivee.x,ligne_arrivee.y);  /** appel des lignes verticales   **/
    }

    return 1;
}

/** fonction affichant le menu  **/
int aff_menu(SDL_Renderer* renderer, SDL_Window* fenetre){

    SDL_Surface* surface = NULL,*fond = NULL, *texte = NULL, *texte1 = NULL, *texte2 = NULL, *texte3 = NULL;  /** création de variables surfaces pour afficher du texte ou des images **/
    SDL_Texture *texture, *texture1, *texture2, *texture3, *fd;  /** creation de textures pour affichages du texte **/
	SDL_Rect pos;  /** déclaration rectangle pos pour position du curseur **/

	/** telechargement des différentes images  **/
    fond = IMG_Load("fond.bmp");  /** telechargement de l'image de fond  **/

    surface = SDL_LoadBMP("image.bmp"); /** telechargement icone de l'othello   **/

    SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello  **/

	TTF_Font *police = NULL, *police2 = NULL;  /** declaration pointeurs vers différentes polices   **/

	SDL_Color vert = {0, 255, 0}, blanc = {255,255,255}, noir = {0,0,0}, rouge = {255,0,0};  /** déclaration des couleurs  **/

    /** Initialisation simple : si ca ne marche pas, affichage du message d'erreur  **/

    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

	/** Initialisation TTF : si ca ne marche pas, affichage message d'erreur **/

	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

    police = TTF_OpenFont("Roboto-Black.ttf", 30); /** police de taille 30  **/
	police2 = TTF_OpenFont("Roboto-Black.ttf", 60); /** police de taille 60 **/

	/** déclaration des message pour les surfaces **/

	texte1 = TTF_RenderText_Solid(police2, "L'OTHELLO ",vert);
	texte = TTF_RenderText_Solid(police, "Jouer ",vert);
	texte2 = TTF_RenderText_Solid(police, "Regles du jeu ",vert);
	texte3 = TTF_RenderText_Solid(police, "QUITTER ",vert);

	/** appel des surfaces dans les textures    **/

    texture = SDL_CreateTextureFromSurface(renderer, texte1);
	texture1 = SDL_CreateTextureFromSurface(renderer, texte);
	texture2 = SDL_CreateTextureFromSurface(renderer, texte2);
	texture3 = SDL_CreateTextureFromSurface(renderer, texte3);

    fd = SDL_CreateTextureFromSurface(renderer,fond);
    SDL_FreeSurface(fond);

	/** verification de la police   **/
	if(!police || !police2) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    /** si la fenetre est ouverte   **/
	if(fenetre)
	{
        /** on declare les premières positions pour le premier message  **/
		pos.x = 250;
		pos.y = 100;
		pos.w = 200;
		pos.h = 30;
		/** on nettoie l'écran  **/

		SDL_RenderClear(renderer);

		/** appel du fond   **/

        SDL_QueryTexture(fd, NULL, NULL, &posfond.w, &posfond.h);
		SDL_RenderCopy(renderer,fd,NULL,&pos);

        /** appel du premier message    **/

		SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer,texture,NULL,&pos);

        /** ainsi de suite pour les autres messages **/

		pos.x = 250;
		pos.y = 300;

		SDL_QueryTexture(texture1, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer,texture1,NULL,&pos);

		pos.x = 250;
		pos.y = 400;

		SDL_QueryTexture(texture2, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer,texture2,NULL,&pos);

		pos.x = 250;
		pos.y = 500;

		SDL_QueryTexture(texture3, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer,texture3,NULL,&pos);

		/** mise en place et appel du renderer pour l'affichage  **/
		SDL_RenderPresent(renderer);
	}
}

int main(int argc, char** argv)
{

	int posx,posy;   /** déclaration variables position x et y pour le curseur  **/
    int i = 1;
	SDL_Window* fenetre = NULL;  /** pointeur création fenetre SDL **/

    SDL_Surface*regle = NULL, *cercle = NULL, *croix = NULL, *retour;  /** création de variables surfaces pour afficher du texte ou des images **/
    SDL_Texture *fd, *r, *retourr;  /** creation de textures pour affichages du texte **/
	SDL_Rect pos;  /** déclaration rectangle pos pour position du curseur **/
	SDL_Rect posfond = {800,800,800,800};
    SDL_Rect reg = {600,600,600,40};
    SDL_Rect ret = {820,10,100,30};
	/** déclarations variables pour score et prénoms pour affichage **/
    SDL_Surface * s1 = NULL, *s2 = NULL;
    SDL_Texture *sc1, *sc2;
    SDL_Rect scor1 = {810,10,200,30};
    SDL_Rect scor2 = {810,220,200,30};

    retour = TTF_RenderText_Solid(police, "Retour au Menu ",vert);
    retourr = SDL_CreateTextureFromSurface(renderer, retour);

	/** telechargement des différentes images  **/

    croix = IMG_Load("croix.bmp");
    cercle = IMG_Load("cercle.bmp");

    SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello  **/

	TTF_Font *police = NULL, *police2 = NULL;  /** declaration pointeurs vers différentes polices   **/

	SDL_Color vert = {0, 255, 0}, blanc = {255,255,255}, noir = {0,0,0}, rouge = {255,0,0};  /** déclaration des couleurs  **/

    /** Initialisation simple : si ca ne marche pas, affichage du message d'erreur  **/

    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

	/** Initialisation TTF : si ca ne marche pas, affichage message d'erreur **/

	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	fenetre = SDL_CreateWindow("Interface graphique de l'othello" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1000 , 1000 , 0);  /** la fenetre prend des dimensions et un titre  **/

    police = TTF_OpenFont("Roboto-Black.ttf", 30); /** police de taille 30  **/

	police2 = TTF_OpenFont("Roboto-Black.ttf", 60); /** police de taille 60 **/

	SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /** Création du renderer    **/


    c1 = SDL_CreateTextureFromSurface(renderer,cercle);
    SDL_FreeSurface(cercle); /** puisqu'on a la texture, on peut libérer la surface **/
    c2 = SDL_CreateTextureFromSurface(renderer,croix);
    SDL_FreeSurface(croix);
    fd = SDL_CreateTextureFromSurface(renderer,fond);
    SDL_FreeSurface(fond);



    aff_menu(renderer,fenetre);
    int cont = 1;
    while(cont){ /** tant qu'on ne quitte pas la fenetre    **/
        int cont2=1;
        while(cont2){
            /** declaration variable event qui traite les évènements de la souris   **/
			SDL_Event souris;
            int res=0;
            while(SDL_PollEvent(&souris)){  /** tant qu'on à un évènement de la souris 	**/

                switch(souris.type){
                    case SDL_MOUSEBUTTONUP:  /** relachement de la souris **/
                        pos.x=souris.motion.x;
    					pos.y=souris.motion.y;

                    if(clic(250,300,&pos) == 1){
                        res = 1;
                        break;
                    }
                    else if(clic(250,400,&pos) == 1){
                        res = 2;
                        break;
                    }
                    else if(clic(250,500) == 1){
                        cont = 0;
                        break;
                    }
                    case SDL_WINDOWEVENT:
                        if ( souris.window.souris == SDL_WINDOWEVENT_CLOSE ) /** si clic sur la croix on ferme la fenetre **/
                            cont = 0;
                        break;
                }
            }
            if(res==1){
                //SDL_RenderClear(renderer);
                /*
                s1 = TTF_RenderText_Solid(police, "Score de %s = %1 ",joueur1.nom_joueur, joueur1.score,noir);
                s2 = TTF_RenderText_Solid(police,"Score de %s = %1 ",joueur2.nom_joueur, joueur2.score,noir);
                sc1 = SDL_CreateTextureFromSurface(renderer, s1);
                sc2 = SDL_CreateTextureFromSurface(renderer, s2);*/
                    SDL_Event event;
                    while(SDL_PollEvent(&event)){  /** tant qu'on à un évènement de la souris 	**/

                        switch(event.type){
                            case SDL_MOUSEBUTTONUP:  /** relachement de la souris **/
                                posx=event.motion.x;
                                posy=event.motion.y;

                                /*
                                SDL_QueryTexture(sc1, NULL, NULL, &scor1.w, &scor1.h);
                                SDL_RenderCopy(renderer,sc1,NULL,&scor1);
                                SDL_QueryTexture(sc2, NULL, NULL, &scor2.w, &scor2.h);
                                SDL_RenderCopy(renderer,sc2,NULL,(&scor2);
                                SDL_QueryTexture(retourr, NULL, NULL, &ret.w, &ret.h);
                                SDL_RenderCopy(renderer,retourr,NULL,&ret);
                                if(i%2 !=0){
                                    if(aff_signe(posx,posy,renderer,cercle)==1){
                                        SDL_QueryTexture(sc1, NULL, NULL, &scor1.w, &scor1.h);
                                        SDL_RenderCopy(renderer,sc1,NULL,&scor1);
                                        SDL_QueryTexture(sc2, NULL, NULL, &scor2.w, &scor2.h);
                                        SDL_RenderCopy(renderer,sc2,NULL,(&scor2);
                                        i++;
                                    }
                                    else if(aff_signe(posx,posy,renderer,cercle)==-1)){

                                    }
                                }else{
                                    if(aff_signe(posx,posy,renderer,croix)==1){
                                        SDL_QueryTexture(sc1, NULL, NULL, &scor1.w, &scor1.h);
                                        SDL_RenderCopy(renderer,sc1,NULL,&scor1);
                                        SDL_QueryTexture(sc2, NULL, NULL, &scor2.w, &scor2.h);
                                        SDL_RenderCopy(renderer,sc2,NULL,(&scor2);
                                        i++;
                                    }
                                    else if(aff_signe(posx,posy,renderer,cercle)==-1)){

                                    }
                                }*/
                            if(clic(10,820,&ret)){
                                aff_menu(renderer,fenetre);
                                cont = 0;
                            }
                            case SDL_WINDOWEVENT:
                                if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) /** si clic sur la croix on ferme la fenetre **/
                                    cont2 = 0;
                                break;
                        }
                        //SDL_RenderPresent(renderer);
                    }
                }
            }
            else if(res==2){
                /** on declare les premières positions pour le premier message  **/
                pos.x = 250;
                pos.y = 100;
                pos.w = 200;
                pos.h = 30;
                /** on nettoie l'écran  **/
                regle = TTF_RenderText_Solid(police, "blablabla ",vert);
                r = SDL_CreateTextureFromSurface(renderer, regle);
                SDL_RenderClear(renderer);

                /** appel du fond   **/

                SDL_QueryTexture(fd, NULL, NULL, &posfond.w, &posfond.h);
                SDL_RenderCopy(renderer,fd,NULL,&pos);

                /** appel des règles et du retour   **/

                SDL_QueryTexture(r, NULL, NULL, &pos.w, &pos.h);
                SDL_RenderCopy(renderer,r,NULL,&pos);

                SDL_QueryTexture(retourr, NULL, NULL, &ret.w, &ret.h);
                SDL_RenderCopy(renderer,retourr,NULL,&ret);

                /** mise en place et appel du renderer pour l'affichage  **/
                SDL_RenderPresent(renderer);

                if(clic(10,820,&ret)){
                    aff_menu(renderer,fenetre);
                    cont2 = 0;
                }
            }
    }
	}else{
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	/** Destruction de la fenetre   **/
	SDL_DestroyWindow(fenetre);

	/** on quitte la police et le TTF et enfin la SDL **/
	TTF_CloseFont(police);
	TTF_Quit();
    SDL_Quit();
    return 0;
}


