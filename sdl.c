#include <SDL2/SDL.h>

#include <stdio.h>

int main(int argc, char** argv)
{
    /** Initialisation	**/
	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    
    SDL_Window* fenetre = NULL;
    fenetre = SDL_CreateWindow("Interface graphique de l'Othello",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);
		
		
		
	SDL_Surface *surface = NULL, *fond = NULL;

	SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( fenetre, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    // Clear winow
    SDL_RenderClear( renderer );
    
	fond = SDL_LoadBMP("fond.bmp");
	surface = SDL_LoadBMP("image.bmp"); /** telechargement icone de l'othello **/
	int position = 0;
	SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello **/
	SDL_Rect r;
    r.x = 150;
    r.y = 150;
    r.w = 150;
    r.h = 150;
    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    // Render rect
    SDL_RenderFillRect( renderer, &r );
    // Render the rect to the screen
    SDL_RenderPresent(renderer);
		if(fenetre){
			char cont = 1;
			
			SDL_Event event;
			int posx = 0;
			int posy = 0;

    		while ( cont != 0) // Nous traitons les événements de la queue
    		{	
    			
    			while(SDL_PollEvent(&event)){
 
    				switch(event.type){
    					case SDL_MOUSEBUTTONUP:  /** relachement de la souris **/
    					fprintf(stdout,"position : %d;%d\n",event.motion.x,event.motion.y);  /** affichage des coordonnés **/
    					
    					case SDL_WINDOWEVENT:
    						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // si clic sur la croix
    							cont = 0;  /** fermeture de la fenetre **/
    						break;
  
    				}
    			}
    		}
    		SDL_DestroyWindow(fenetre);		
    	}
		else{
    		fprintf(stderr,"erreur creation fenetre : %s\n",SDL_GetError());
    	}



    SDL_Quit();

    return 0;
}