if(couleur == BLANC){	/* Si c'est ordi */

		/* S'il joue dans le coin */
		if((lig == 0 && col == 0) || (lig == N-1 && col == N-1) || (lig == 0 && col == N-1) || (lig == N-1 && col == 0)){
			/* On retourne la valeur max */
			return (N*N);
		}
		
		/* S'il joue sur le bord */
		else if(lig == 0 || lig == N-1 || col == 0 || col == N-1){


			/* Si la ligne vaut 0 (ligne du haut), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			if(lig == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en haut à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Si la ligne vaut N-1 (ligne du bas), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(lig == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Si la colonne vaut 0 (colonne de gauche), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Si la colonne vaut N-1 (colonne de droite), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à droite */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return (N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return (N*N/2);
					}
				}
			}

			/* Sinon, il n'y a aucune suite continue jusqu'a un coin de la meme couleur, 
			donc c'est juste un bord normal, avec risque de se le faire reprendre */
			else{
				return (N*N/6);
			}

		}

		/* Sinon on renvoie le nb de pions en plus */
		else{
			return nb_pions_en_plus+1;
		}

	}
	else{	/* Sinon c'est joueur */

		/* S'il joue dans le coin */
		if((lig == 0 && col == 0) || (lig == N-1 && col == N-1) || (lig == 0 && col == N-1) || (lig == N-1 && col == 0)){
			/* On retourne la valeur max */
			return -(N*N);
		}
		
		/* S'il joue sur le bord */
		else if(lig == 0 || lig == N-1 || col == 0 || col == N-1){


			/* Si la ligne vaut 0 (ligne du haut), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			if(lig == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en haut à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Si la ligne vaut N-1 (ligne du bas), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(lig == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
				for(j=col;j>=0;j--){
					if(mat[lig][j] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(j=col;j<=N-1;j++){
						if(mat[lig][j] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Si la colonne vaut 0 (colonne de gauche), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == 0){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à gauche */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à gauche */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Si la colonne vaut N-1 (colonne de droite), on regarde s'il existe une suite continue dans sa couleur jusqu'a un coin */
			else if(col == N-1){

				verif_bord = 1;

				/* On regarde tout d'abord en partant de la valeur de la colonne jusqu'au coin en haut à droite */
				for(i=lig;i>=0;i--){
					if(mat[i][col] != couleur){
						verif_bord = 0;
					}
				}
				/* Si c'est continue, on retourne une grande valeur */
				if(verif_bord == 1){
					return -(N*N/2);
				}
				/* Sinon on regarde dans l'autre sens */
				else{
					verif_bord = 1;
					/* On regarde maintenant en partant de la valeur de la colonne jusqu'au coin en bas à droite */
					for(i=lig;i<=N-1;i++){
						if(mat[i][col] != couleur){
							verif_bord = 0;
						}
					}
					/* Si c'est continue, on retourne une grande valeur */
					if(verif_bord == 1){
						return -(N*N/2);
					}
				}
			}

			/* Sinon, il n'y a aucune suite continue jusqu'a un coin de la meme couleur, 
			donc c'est juste un bord normal, avec risque de se le faire reprendre */
			else{
				return -(N*N/6);
			}

		}

		/* Sinon on renvoie le nb de pions en plus */
		else{
			return -nb_pions_en_plus;
		}
		
	}