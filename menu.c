#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "sdl.h"


int clic(int x, int y, struct SDL_Rect *rect){
	if((x >= rect->x) && (rect->x <= x+rect->w) && (y >= rect->y) && (rect->y <= (y+rect->h)))
		return 1;
	return 0;
}

int main(int argc, char** argv)
{
	int posx,posy;
        //Le pointeur vers la fenetre
	SDL_Window* fenetre = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
        SDL_Surface* surface = NULL, *texte = NULL, *texte1 = NULL, *texte2 = NULL, *texte3 = NULL;
        SDL_Texture *texture, *texture1, *texture2, *texture3;
	SDL_Rect pos;

	// Le pointeur vers notre police
	TTF_Font *police = NULL, *police2 = NULL;

	SDL_Color vert = {0, 255, 0}, blanc = {255,255,255}, noir = {0,0,0};

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    } 

	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	fenetre = SDL_CreateWindow("Interface graphique de l'othello" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 800 , 800 , 0);
        police = TTF_OpenFont("Roboto-Black.ttf", 30);
	police2 = TTF_OpenFont("Roboto-Black.ttf", 60);
	texte1 = TTF_RenderText_Solid(police2, "L'OTHELLO ",vert);
	texte = TTF_RenderText_Solid(police, "Jouer ",vert);
	texte2 = TTF_RenderText_Solid(police, "Regles du jeu ",vert);
	texte3 = TTF_RenderText_Solid(police, "QUITTER ",vert); 
	SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello	**/
	SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /** Création du renderer	**/
	


    	texture = SDL_CreateTextureFromSurface(renderer, texte1);
	texture1 = SDL_CreateTextureFromSurface(renderer, texte);
	texture2 = SDL_CreateTextureFromSurface(renderer, texte2);
	texture3 = SDL_CreateTextureFromSurface(renderer, texte3);
	
	if(!police) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        // handle error
        }

	if(fenetre)
	{
	
		pos.x = 250;
		pos.y = 100;
		pos.w = 200;
		pos.h = 30;
		SDL_RenderClear(renderer);
		

		SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer,texture,NULL,&pos);

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

		SDL_RenderPresent(renderer);


		int cont = 1; 
		while(cont){ 
			SDL_Event event;
		
    			while(SDL_PollEvent(&event)){  /** tant qu'on à un évènement de la souris 	**/
 
    				switch(event.type){
    					case SDL_MOUSEBUTTONUP:  /** relachement de la souris **/
    					posx=event.motion.x;
    					posy=event.motion.y;
					if(clic(250,300,&pos)){
						SDL_RenderClear(renderer);
						aff(fenetre);
    					}
    					case SDL_WINDOWEVENT:
    						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // si clic sur la croix
    						cont = 0;
    					break;
				}
    					
    			}
		}
	}else{
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(fenetre);

	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
    SDL_Quit();

    return 0;
}


