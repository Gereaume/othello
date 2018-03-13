#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv)
{
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface* pSurface = NULL, *texte, *image;
	SDL_Rect position;

	// Le pointeur vers notre police
	TTF_Font *police = NULL;
	// Une variable de couleur noire
	SDL_Color couleurNoire = {0, 0, 0};

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


	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Hello World SDL2",SDL_WINDOWPOS_UNDEFINED,
												  SDL_WINDOWPOS_UNDEFINED,
												  640,
												  480,
												  SDL_WINDOW_SHOWN);

	if( (police = TTF_OpenFont("ChowFun.ttf", 20)) == NULL){
		fprintf(stderr, "erreur chargement font\n");
		exit(EXIT_FAILURE);
	}
	texte = TTF_RenderUTF8_Blended(police, "Vive la programmation !", couleurNoire);

	// load sample.png into image
	SDL_RWops *rwop=SDL_RWFromFile("affiche2018.png", "rb");
	image=IMG_LoadPNG_RW(rwop);
	if(!image) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}


	if( pWindow )
	{
		//On récupère la surface de la fenetre
		pSurface = SDL_GetWindowSurface( pWindow );

		position.x = 10;
		position.y = 10;
		
		SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255));
		SDL_BlitSurface(texte, NULL, pSurface, &position); /* Blit du texte */

		position.y = 50;
		SDL_BlitSurface(image,NULL,pSurface,&position); /* Blit de l'image */

		//On met à jour la surface de la fenetre
		SDL_UpdateWindowSurface( pWindow );

		int running = 1; 
		while(running) { 
			SDL_Event e; 
			while(SDL_PollEvent(&e)) { 
				switch(e.type) { 
					case SDL_QUIT: running = 0; 
					break; 
				} 
			} 
		}
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
    SDL_Quit();

    return 0;
}


