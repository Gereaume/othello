#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define N 8


/** fonction permettant de voir si on a cliqué sur une zone passée en paramètre    **/
int clic(int x, int y, struct SDL_Rect *rect){
	if((x >= rect->x) && (rect->x <= x+rect->w) && (y >= rect->y) && (rect->y <= (y+rect->h)))
		return 1;
	return 0;
}

/** fonction affichant le signe aux positions passées en paramètre si le coup est possible   **/
/*void aff_signe(int posx, int posy, SDL_Renderer *renderer, SDL_Surface * image){
	SDL_Rect positions;
	positions.x = posx;
	positions.y = posy;

	while(coupPoss(char mat[N][N], char mat2[N][N], char couleur, posx,posy)==0){*/
		/** affichage message "Vous ne pouvez pas jouer ici, recommencez"	**/
	/*}
	else{*/
		/**SDL_BlitSurface(image, NULL, fenetre, &position)**/
	/*}

}*/

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



int main(int argc, char** argv)
{

	int posx,posy;   /** déclaration variables position x et y pour le curseur  **/

	SDL_Window* fenetre = NULL;  /** pointeur création fenetre SDL **/

    SDL_Surface* surface = NULL,*fond = NULL, *texte = NULL, *texte1 = NULL, *texte2 = NULL, *texte3 = NULL, cercle = SDL_LoadBMP("cercle.bmp"), croix = SDL_LoadBMP("croix.bmp");  /** création de variables surfaces pour afficher du texte ou des images **/
    SDL_Texture *texture, *texture1, *texture2, *texture3, *c1,*c2;  /** creation de textures pour affichages du texte **/
	SDL_Rect pos;  /** déclaration rectangle pos pour position du curseur **/

    fond = SDL_LoadBMP("fond.bmp");  /** telechargement de l'image de fond  **/

    surface = SDL_LoadBMP("image.bmp"); /** telechargement icone de l'othello   **/

    SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello  **/

	TTF_Font *police = NULL, *police2 = NULL;  /** declaration pointeurs vers différentes polices   **/

	SDL_Color vert = {0, 255, 0}, blanc = {255,255,255}, noir = {0,0,0};  /** déclaration des couleurs  **/

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

	fenetre = SDL_CreateWindow("Interface graphique de l'othello" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 800 , 800 , 0);  /** la fenetre prend des dimensions et un titre  **/

    police = TTF_OpenFont("Roboto-Black.ttf", 30); /** police de taille 30  **/

	police2 = TTF_OpenFont("Roboto-Black.ttf", 60); /** police de taille 60 **/

	/** déclaration des message pour les surfaces **/

	texte1 = TTF_RenderText_Solid(police2, "L'OTHELLO ",vert);
	texte = TTF_RenderText_Solid(police, "Jouer ",vert);
	texte2 = TTF_RenderText_Solid(police, "Regles du jeu ",vert);
	texte3 = TTF_RenderText_Solid(police, "QUITTER ",vert);

	SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /** Création du renderer    **/

	/** appel des surfaces dans les textures    **/

    texture = SDL_CreateTextureFromSurface(renderer, texte1);
	texture1 = SDL_CreateTextureFromSurface(renderer, texte);
	texture2 = SDL_CreateTextureFromSurface(renderer, texte2);
	texture3 = SDL_CreateTextureFromSurface(renderer, texte3);

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


		int cont = 1;
		while(cont){ /** tant qu'on ne quitte pas la fenetre    **/

            /** declaration variable event qui traite les évènements de la souris   **/
			SDL_Event event;

    			while(SDL_PollEvent(&event)){  /** tant qu'on à un évènement de la souris 	**/

    				switch(event.type){
    					case SDL_MOUSEBUTTONUP:  /** relachement de la souris **/
    					posx=event.motion.x;
    					posy=event.motion.y;

                        if(clic(250,300,&pos)){
                            aff_mat(renderer);
                        }
                        case SDL_WINDOWEVENT:
                            if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) /** si clic sur la croix on ferme la fenetre **/
    						cont = 0;
    					break;
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


