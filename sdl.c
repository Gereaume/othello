#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define N 8


/*
void aff_signe(int posx, int posy, SDL_Renderer *renderer, SDL_Surface * image){
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


    	SDL_SetRenderDrawColor(renderer,0,0,0,0);//Couleur noir

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

int aff(SDL_Window* fenetre){

    
    int posx = 0;  /** position en abscisse 	**/
    int posy = 0;  /** position en ordonnée	**/

    fenetre = SDL_CreateWindow("Interface graphique de l'othello" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 800 , 800 , 0);
	
    SDL_Surface *surface = NULL, *fond = NULL, *texte = NULL;  /** definition de variables de surface	**/
    SDL_Surface* cercle = SDL_LoadBMP("cercle.bmp"), croix = SDL_LoadBMP("croix.bmp");

    SDL_Color noir = {0,0,0},blanc = {255, 255, 255};

        /** Initialisation	**/
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    int i = 1;
    fond = SDL_LoadBMP("fond.bmp");
    surface = SDL_LoadBMP("image.bmp"); /** telechargement icone de l'othello	**/
    SDL_SetWindowIcon(fenetre, surface);  /** affichage icone de l'othello	**/



	
	if(fenetre)  /** si l'ouverture de la fenetre a réussi	**/
	{
		aff_mat(renderer);

		int cont = 1;
    		while(cont == 1) /** appel de la fonction coordonnes tant qu'on le clique pas sur la croix	**/
    		{	
    			SDL_Event event;
		
    			while(SDL_PollEvent(&event)){  /** tant qu'on à un évènement de la souris 	**/
 
    				switch(event.type){
    					case SDL_MOUSEBUTTONUP:  /** relachement de la souris **/
    					fprintf(stdout,"position : %d;%d\n",event.motion.x,event.motion.y);  /** affichage des coordonnés **/
    					posx=event.motion.x;
    					posy=event.motion.y;
					/*if(i%2 !=0)
    						aff_signe(posx,posy,renderer, croix); 
					else
						aff_signe(posx,posy,render,rond);*/
    					case SDL_WINDOWEVENT:
    						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // si clic sur la croix
    						cont = 0;
    					break;
					i++;
    					
    			}
			/*while(!ecrire_mat_clic(mat,posx,posy)){*/
				/** afficher message ne peut pas jouer ici **/
				/** recommencez **/
			/*}*/
			/** afficher croix ou cercle au bons coordonnées **/
			

		}
    	}
	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(fenetre); /** fermer la fenetre 	**/

    	}else{
    		fprintf(stderr,"erreur creation fenetre : %s\n",SDL_GetError());
    		return EXIT_FAILURE;
    	}

    SDL_Quit();
    
    return 0;
}