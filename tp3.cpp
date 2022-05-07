# include < stdio.h >
# include < stdlib.h >
# include < chaîne.h >
# définir  N  100


  typedef  struct  noed {
                int     num_sommet ; 
  	  int     borne_supérieur;  
  	  float   valeurs_variables[N] ;  
  	  entier fixeur_variables     [N] ;                           
	  struct  noed * gauche; 	
	  struct  noed * droite; 
	  
	}arborescence ;
typedef arborescence* arbre ;


int      nb_variable ; 
float    coeff_fon_objective[N] ;  
float    coeff_contrainte[N] ;  
float    tab_efficacite[N] ;  
float    tab_indice[N] ; 
int      borne_inférieur;  
int      resultat_final[N] ; 
arbre arbre_resultat ;  
int      choix ; 
int      voir_detaille ; 
int      num_som = 0 ; 


void  affiche_result_node (noeud arbre);
arbre init_arbre ();


/

int  is_entier ( float n){ 
	int      partie_entière ;
	float    parti_non_entiere ;
	parti_entiere = int (n);
	
	parti_non_entiere = float (n) - parti_entiere ;
	
	if ((parti_non_entiere <= 0.001   && parti_non_entiere >= - 0.001 ) ||
	   (parti_non_entière < 1   && parti_non_entière >= 0.99 ) ||
	   (parti_non_entière <= - 0.99   && parti_non_entière > - 1 )
	  ){
	      retour  1 ;	
	}
  retourne  0 ;
}


int  solution_non_entiere (arbre a){   
	int je ;
	
	pour (i= 1 ; i<= nb_variable ; i++){
		si (! est_entier (a-> valeurs_variables [i]) ){
		     
		     retourner je ; 	
		}
	}
	
	retourne  0 ; 
}




void  lire_nb_variable (){  
	chaîne de caractères   [N] ;
	faire {
	    printf ( "   Donner le nombre des variables : " );
	    scanf ( " %s " ,chaine);
	    nb_variable = atoi (chaine);
	    
	} tandis que (nb_variable <= 0 );
	
	
}






void  lire_fonction_objective (){   
     int   je ;
     printf ( " Donner la fonction objective : " );
     pour (i= 1 ; i<= nb_variable ; i++){
          	
          printf ( " \n      X%d =   " ,i);
          scanf ( " %f " ,&coeff_fon_objective[i]);
          	
     }	
	
}




void  lire_contrainte (){   
     int   je ;
     printf ( " Donner la contrainte : " );
          
               printf ( " \n      Donner le poids Max : " ,i);
          scanf ( " %f " ,&coeff_contrainte[nb_variable+ 1 ]);
          
     pour (i= 1 ; i<= nb_variable ; i++){
          faire {
               printf ( " \n      X%d =   " ,i);
               scanf ( " %f " ,&coeff_contrainte[i]);
	 si (coeff_contrainte[i] > coeff_contrainte[nb_variable+ 1 ]){
	     printf ( "             X%d doit être supérieur ou égal à %.2f   \n  " ,i,coeff_contrainte[nb_variable+ 1 ]);
	 }         	
          } tandis que (coeff_contrainte[i] > coeff_contrainte[nb_variable+ 1 ]);	

          	
     }	

               	
}




void  permuter ( float *a , float *b){   
	float   var_temporaire ;
	var_temporaire = *a;
	*a = *b ;
	*b = var_temporaire ;
	
}



void  initialiser_efficacite (){   
	int je ;
	pour (i= 1 ; i<= nb_variable ; i++){
	     tab_efficacite[i] = coeff_fon_objective[i] / coeff_contrainte[i] ;
	}
	
}




void  initialiser_indices (){   
	pour (i= 1 ; i<= nb_variable ; i++){
	    tab_indice[i] = i ;
	}
		
}


void  initialise_var_fixe (){ 
	int   je ;
	pour (i= 1 ; i<= nb_variable ; i++){
		
		arbre_resultat-> fixer_variables [i] = - 1 ;
	}
}


void  tri_efficacite (){	
	int   je, j ;
	

	pour (i= 1 ; i<= nb_variable ; i++){
		for (j= i+ 1 ;j<= nb_variable ; j++){
		   si (tab_efficacite[i] < tab_efficacite[j]){
		     
		     permuter (&tab_efficacite[i],&tab_efficacite[j]);
		     
		     permuter (&tab_indice[i],&tab_indice[j]);
	                 }
		}
	}

	
}

void  calcul_sol_realisable (){   
	flottant    volume_max ;
	int      je , indice ;
	
	volume_max = coeff_contrainte[nb_variable+ 1 ];
	
	pour (i= 1 ; i<= nb_variable ; i++){
	       indice = tab_indice[i] ;
	       si (coeff_contrainte[indice] <= volume_max){
	           volume_max = volume_max - coeff_contrainte[indice] ;
	           resultat_final[indice] = 1 ;   	
	       } sinon {
	           resultat_final[indice] = 0 ; 	
	       }	
	}
	
	
	borne_inférieur =   0 ;
	pour (i= 1 ; i<= nb_variable ;i++){
        	   borne_inferieur = borne_inferieur +
	           ( coeff_fon_objective[i] * resultat_final[i]); 			
	}
}

float  take_object (arbre le_node){
	int je , indice ;
	float vol_max = coeff_contrainte[nb_variable + 1 ];
	
	pour (i= 1 ;i<=nb_variable ; i++){
	     indice = tab_indice[i] ;
	     if (le_node-> fixer_variables [indice] == 1 ){
	          vol_max = vol_max - coeff_contrainte[indice] ;
	     }	
	}	
	retourne vol_max ;	
}

void  remplire_valeur (arbre le_node){
	int je ;
	pour (i= 1 ; i<= nb_variable ; i++){
		
		if (le_node-> fixer_variables [i] == 1 ){
			le_node-> valeurs_variables [i] = 1 ;
			
		} sinon {
			le_node-> valeurs_variables [i] = 0 ;	
		}
		
	}
}

void  iliminate_object (arbre le_node, float volume_max){
	int je ;
	indice entier ;
	pour (i= 1 ; i<= nb_variable ; i++){
		indice = tab_indice[i] ;	
		if (le_node-> fixer_variables [indice] == - 1 ){
			si (coeff_contrainte[indice] > volume_max){
			   le_node-> fixer_variables [indice] = 0 ;		
			}	
		}
	}
}
void  calcul_borne_superieur (arbre le_node ){ 

	flottant    volume_max ;
	int      je , indice ;

	
	volume_max = take_object (le_node);
	
	
	éliminer_objet (le_node, volume_max);
	
	
	remplir_valeur (le_node);


	
	
	pour (i= 1 ; i<= nb_variable ; i++){
		
	       indice = tab_indice[i] ;
	       
	       if (le_node-> fixer_variables [indice] == - 1 ){
	       	si (coeff_contrainte[indice] <= volume_max){
		    volume_max = volume_max - coeff_contrainte[indice] ;
	                  le_node-> valeurs_variables [indice] = 1 ;	       		
		} sinon {
	            		le_node-> valeurs_variables [indice]=
	              	 volume_max / coeff_contrainte[indice] ;
	            		casser ;	
	      	 }	
	       }
	       if (le_node-> fixer_variables [indice] == 0 ){
	       	le_node-> valeurs_variables [indice] = 0 ;	       	       	  	
	      }	

	}	
	
	
	
	
    le_node-> borne_superieur = 0 ;
	pour (i= 1 ; i<= nb_variable ;i++){
        	   le_node-> borne_superieur = le_node-> borne_superieur   +
	           ( coeff_fon_objective[i] * le_node-> valeurs_variables [i]);
              		
	}


}

void  change_result (arbre a){
	int   je ;
	
	pour (i= 1 ; i<= nb_variable ; i++){
		resultat_final[i] = a-> valeurs_variables [i] ;
	}
}





 
     
int  est_vide (arbre a){
	si (a == NULL )
	   retour   1 ;
	retourne  0 ;   
}


void  fixe_les_indice (arbre fils_gauche,arbre le_node, int fixe_or_no , int indice){
	int je ;
	pour (i= 1 ; i<= nb_variable ; i++){
		fils_gauche-> fixer_variables [i] = le_node-> fixer_variables [i] ;
	}
	fils_gauche-> fixer_variables [indice] = fixe_or_no ;

}

void  separation_evaluation (arbre le_node){   
	
	int   je ;
	int   indice_variable_non_int ;

	
			
	calcul_borne_superieur (le_node);
	
	
	le_node-> num_sommet = num_som ;
	num_som++ ;

	si (voir_détail){
	  
	  affiche_result_node (le_node);		
	}
	
	
	
	indice_variable_non_int = solution_non_entiere (le_node);
	
	si (indice_variable_non_int){
	     if (le_noeud-> borne_superieur > borne_inferieur){
	     	
	     	
	     	arbre fils_gauche = init_arbre () ;
       		fils_gauche=(arbre) malloc ( taille de (arborescence));
	     	fixe_les_indice (fils_gauche,le_node, 0 ,indice_variable_non_int);
	     	le_node-> gauche = fils_gauche ;
	     	
	     	
	     	
	     	arbre fils_droite = init_arbre () ;
       		fils_droite =(arbre) malloc ( taille de (arborescence));
       		fixe_les_indice (fils_droite,le_node, 1 ,indice_variable_non_int);
		le_node-> droite = fils_droite ;
		
		
		séparation_evaluation (fils_gauche);
		séparation_évaluation (fils_droite) ;    		
       		
	     } sinon {
	     	
		le_node-> droite =    NULL ;
		le_node-> gauche =    NULL ;
	     }	
		
	} sinon {
	     if (le_noeud-> borne_superieur > borne_inferieur){
	         
    	   	borne_inferieur = le_noeud-> borne_superieur ;
    	   	
    	   	change_result (le_node);	
	     }
			
		le_node-> droite =    NULL ;
		le_node-> gauche =    NULL ;		    
		
	}


}


arbre init_arbre (){ 
	retourne  NULL ;
}



void  affiche_fonction_objective (){
	int    je ;
	je =   1 ;
	printf ( "         La fonction objectif : \n " );
	printf ( "               MaxZ = %.2fX%d " , coeff_fon_objective[i],i);
	pour (i= 2 ; i<= nb_variable ; i++){
	     printf ( "   + %.2fX%d " , coeff_fon_objective[i],i);	
	}
	printf ( " \n " );	
	
}


vide  affiche_contrainte (){
     	int   je ;
	je =   1 ;		
	printf ( "         La contrainte : \n " );
	printf ( "               %.2fX%d " , coeff_contrainte[i],i);	
	pour (i= 2 ; i<= nb_variable ; i++){
	     printf ( " + %.2fX%d " , coeff_contrainte[i],i);	
	}	
	printf ( " <= %.2f " , coeff_contrainte[i]);
	printf ( " \n " );	
}



void  afficher_objet_trier (){
	int    je ;
	printf ( "         Trier les objets : \n " );
	printf ( "               " );
	pour (i= 1 ; i<= nb_variable ; i++){
	     printf ( " X%.0f     " ,tab_indice[i]);	
	}
	printf ( " \n " );
	
	
}

void  affiche_result_node (noeud arbre){
	int   je ;
    	printf ( "      S%d : " ,noeud-> num_sommet );
	pour (i= 1 ; i<= nb_variable ; i++){
		printf ( " \n                 X%d = %.2f   \n " ,i,noeud-> valeurs_variables [i]);
	}
	printf ( "       E = %d " ,noeud-> borne_superieur );
	printf ( " \n       La borne inférieure = %d \n " ,borne_inférieure);
}


annuler  affiche_result_solution (){
	int    je ;
	printf ( "         La solution : : \n " );
	pour (i= 1 ;i<= nb_variable ; i++){
	    printf ( "               X%d = %d    \n " ,i, resultat_final[i]);
	}
	printf ( "               Z = %d   \n  " ,borne_inferieur);
	printf ( " \n " );
}



void  affich_arbre (arbre a){
	si (! est_vide (a)){
		printf ( " S%d :: %d \n " ,a-> num_sommet ,a-> borne_superieur );
		printf ( " \n " );
		affich_arbre (a-> gauche );
		affich_arbre (a-> droite );
	}
}


void   affiche_result (){
   printf ( " \n\n ========================================== ============================ " );
   printf ( " \n\n ========================================== =========================== \n\n " );
              si (voir_détail){
              	système ( " pause " );
	}
	printf ( "   Le resultat :    \n " );
	
	
  	affiche_fonction_objectif ();
		
	
	affiche_contrainte ();
	
	
	afficher_objet_trier ();
	
	affiche_result_solution ();
	
	

	

}

    
int  recomancer (){
        char a choisi[N] ;
        faire {
            printf ( " \n     Voulez-vous recomancer ou quitter : " );
            printf ( " \n               1 : recomencer \n " );
            printf ( " \n               2 : quitter \n " );
           
            scanf ( " %s " ,&choisi);
            choix = atoi (choisi);	
        } tandis que (choix != 1   && choix != 2 );
        
        si (choix == 1 ){
        	retour  1 ;
        } sinon {
        	retourne  0 ;
        }	
	 
}
  
void  detaille_non (){
       détail char    [N] ;
       faire {
            printf ( "      -- Voulez-vous voir le détail de la solution ou pas : " );
            printf ( " \n              1 : voir les détails " );
            printf ( " \n              2 : ne pas voir les détails \n " );
            scanf ( " %s " ,détail);
            voir_detaille = atoi (détail);
       } tandis que (voir_detaille != 1 && voir_detaille != 2 );
       si (voir_detaille == 2 ){
            voir_detaille = 0 ;	
       }
}



int  principal (){
    système ( " couleur f0 " );  
    
        lire_nb_variable ();

    
        lire_fonction_objectif ();

    
        lire_contrainte ();
   	 
        initialiser_efficacite ();
    
    
        initialiser_indices ();
    
    
        tri_efficacite ();
    
    
       calcul_sol_réalisable ();
    
       arbre_resultat = init_arbre () ;
       arbre_resultat=(arbre) malloc ( taille de (arborescence));
     
    
       detaille_non (); 


       initialise_var_fixe ();

        
    
       separation_evaluation (arbre_resultat);
     

   
       affiche_result ();

    
    
    si ( recomancer ()){
         num_som = 0 ; 
         principal ();  	
    }	
    

    	
    retourne  0 ;
    
}
