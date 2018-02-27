#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void Draw_Cercle(SDL_Renderer* renderer)
{
  int an = 0;
  float ra = 1;
  int x = 0;
  int y = 0;
  int ray = 250;

  while (an < 360){
    ra = (M_PI*(float)an/180.0);
    x =ray * cos(ra) + 50;
    y =ray * sin(ra) + 50;
    SDL_RenderDrawPoint(renderer, x, y);
    an++;
  }
  SDL_RenderPresent(renderer);
}


void coordonnees(int cont, int posx, int posy){
	
	SDL_Event event;  /** on prend les évènements de la souris	**/	
		
    while(SDL_PollEvent(&event)){  /** tant qu'on à un évènement de la souris 	**/
 
    			switch(event.type){
    				case SDL_MOUSEBUTTONUP:  /** relachement de la souris **/
    				fprintf(stdout,"position : %d;%d\n",event.motion.x,event.motion.y);  /** affichage des coordonnés **/
    				posx=event.motion.x;
    				posy=event.motion.y;
    					
    				case SDL_WINDOWEVENT:
    					if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // si clic sur la croix
    						cont = 0;  /** fermeture de la fenetre **/
    					break;
    					
    			}
    }


}


void aff_joueur1(int posx, int posy){

	while(coupPoss(char mat[N][N], char mat2[N][N], char couleur, posx,posy)==0){
		/** affichage message "Vous ne pouvez pas jouer ici, recommencez"	**/
	}
	else{
		/** afficher un cercle noir aux bonnes coordonnées	**/
	}
	
}



void aff_joueur2(int posx, int posy){

	while(coupPoss(char mat[N][N], char mat2[N][N], char couleur, posx,posy)==0){
		/** affichage message "Vous ne pouvez pas jouer ici, recommencez"	**/
	}
	else{
		/** afficher un cercle noir aux bonnes coordonnées	**/
	}
}








int aff_mat(SDL_Renderer* renderer){
		
		SDL_Point ligne_depart,ligne_arrivee; // Déclaration point de départ et point d'arrivée d'une ligne
		
    	if(renderer == NULL) // Gestion des erreurs
    	{
        	printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        	return 0;
    	}
    	SDL_Rect cases[32]; // Déclaration du tableau contenant les cases
    	
		SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); /**Couleur verte	**/
    	SDL_RenderClear(renderer);
		

    	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); /**Couleur verte	**/

		/** cases en blanc	**/
		
    	cases[0].x = cases[0].y = 0;
    	cases[0].w = cases[0].h = 100;


    	for(int i = 1; i <32; i++)
    	{
        	cases[i].x = cases[i-1].x + 200;
        	cases[i].y = cases[i-1].y;

        	if(i%4 == 0) //retour à la ligne
        	{
            	cases[i].x = (i%8 == 0) ? 0 : 100;
            	cases[i].y = cases[i-1].y + 100;
        	}
        	cases[i].w = cases[i].h = 100; //taille d'une case (100 sur 100)
    	}


    	if(SDL_RenderFillRects(renderer,cases,32) <0)  //Remplissage des cases
    	{
        	printf("Erreur lors des remplissages de rectangles: %s",SDL_GetError());
        	return 0;
    	}


    	SDL_SetRenderDrawColor(renderer,0,0,0,0);//Couleur blanc

		// Lignes horizontales
    	ligne_depart.x = 0;
    	ligne_arrivee.x = 800;
    	ligne_depart.y = 0;
    	for(int i = 0; i<7; i++)
    	{
        	ligne_depart.y += 100;
        	ligne_arrivee.y = ligne_depart.y;
        	SDL_RenderDrawLine(renderer,ligne_depart.x, ligne_depart.y,ligne_arrivee.x,ligne_arrivee.y); // appel des lignes horizontales
    	}

		// Lignes verticales
    	ligne_depart.x = 0;
    	ligne_depart.y = 0;
    	ligne_arrivee.y = 800;
    	for(int i = 0; i<7; i++)
    	{
        	ligne_depart.x += 100;
        	ligne_arrivee.x = ligne_depart.x;
        	SDL_RenderDrawLine(renderer,ligne_depart.x, ligne_depart.y,ligne_arrivee.x,ligne_arrivee.y);  // appel des lignes verticales
    	}
    	
    	return 1;

}


int main(int argc, char** argv)
{
    /** Initialisation	**/
	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    
    int posx = 0;  /** position en abscisse 	**/
	int posy = 0;  /** position en ordonnée		**/
	
    SDL_Window* fenetre = SDL_CreateWindow("Interface graphique de l'othello" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 800 , 800 , 0);
	
	SDL_Surface *surface = NULL, *fond = NULL;  /** definition de variables de surface	**/
	
	fond = SDL_LoadBMP("fond.bmp");
	surface = SDL_LoadBMP("image.bmp"); /** telechargement icone de l'othello	**/
	SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello	**/
	
	SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); /** Création du renderer	**/
	
	
    
	if(fenetre)  /** si l'ouverture de la fenetre a réussi	**/
	{
		aff_mat(renderer);
		
		SDL_RenderPresent(renderer);
		
    	int cont = 1;
		
    	while(cont != 0) /** appel de la fonction coordonnes tant qu'on le clique pas sur la croix	**/
    	{	
    			coordonnees(cont,posx,posy);
    	}
    	
    	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(fenetre);		/** fermer la fenetre 	**/

    }else{
    	fprintf(stderr,"erreur creation fenetre : %s\n",SDL_GetError());
    	return EXIT_FAILURE;
    }
    SDL_Quit();  /** quitter 	**/
    return 0;
}