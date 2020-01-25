#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct GenaratePjPnj{
	int pv;
	int pvMax;
	int pa;
	int paMax;
	int atq;
	int def;
	int xp;
	int xpMax;
	int lvl;
	
	int tamponDef;
	int tamponPsn;
	
	int aggro;
	
};
typedef struct GenaratePjPnj generate;

int attaque(int pv, int atq, int tdef, int def){
	
	if(tdef == 1){
		pv -= atq/def;
	}else{
		pv -= atq;
	}
	
}

int main(){
	//Variable
		int game = 1;
		int end = 0;
		int action;
	
	//Equipage
	
	generate deVigne = {100, 100, 100, 100, 5, 2, 0,10, 1, 0,0, 0};
	generate diPlaza = {100, 100, 100, 100, 20, 3, 0,10, 1, 0,0, 0};
	generate billy = {100, 100, 100, 100, 10, 4, 0,10, 1, 0,0, 0};
	generate ringOfKelly = {100, 100, 100, 100, 15, 3, 0,10, 1, 0,0, 0};
	
	//FIGHT
	
	while(game == 1){
		
		
		
		//Combat contre 1mob
		if(deVigne.lvl <= 5 && diPlaza.lvl <= 5 && billy.lvl <= 5 && ringOfKelly.lvl <= 0){
			
			//equipage
			deVigne.pv = deVigne.pvMax;
			deVigne.pa = deVigne.paMax;
			diPlaza.pv = diPlaza.pvMax;
			diPlaza.pa = diPlaza.paMax;
			billy.pv = billy.pvMax;
			billy.pa = billy.paMax;
			ringOfKelly.pv = ringOfKelly.pvMax;
			ringOfKelly.pa = ringOfKelly.paMax;
			
			//ennemie
			generate chasseurA = {100, 100, 100, 100, 16, 2, 5, 0, 1, 0, 0, 0};
			
			while(end == 0){
				
				//tour Billy
				
					//recup PA
					if(billy.pa < billy.paMax){
						billy.pa += 5;
						if(billy.pa > billy.paMax){
							billy.pa = billy.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					if(billy.tamponDef == 1){
						billy.tamponDef = 0;
					}
				
					//afficher PV PA
					printf("\nPV : %d\n", billy.pv);
					printf("PA : %d\n", billy.pa);
					
					//selection de l'action
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : insulte\n");
					scanf("%d", &action);
					
					//verif action
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : insulte\n");
						scanf("%d", &action);
					}
					
					//atq
					if(action == 1){
						chasseurA.pv = attaque(chasseurA.pv, billy.atq, chasseurA.tamponDef, chasseurA.def);
					}
					
					//def
					if(action == 2){
						billy.tamponDef = 1;
					}
					
					//comp
					if(action == 3){
						printf("Billy lance Insulte");
						billy.aggro = 1;
					}
					
				
				//tour Ring Of Kelly
				
					//afficher PV PA
					
					//recup PA
					
					//Réinit Tampon def
					
					//selection de l'action
					
					//verif action
					
					//atq
					
					//def
					
					//comp
					
				//Tour Chasseur
				
					//afficher PV PA
					
					//recup PA
					
					//Réinit Tampon def
					
					//selection de l'action
					
					//verif action
					
					//atq
					
					//def
					
					//comp
					
				//tour di Plaza
				
					//afficher PV PA
					
					//recup PA
					
					//Réinit Tampon def
					
					//selection de l'action
					
					//verif action
					
					//atq
					
					//def
					
					//comp
					
				//Tour DeVigne
				
					//afficher PV PA
					
					//recup PA
					
					//Réinit Tampon def
					
					//selection de l'action
					
					//verif action
					
					//atq
					
					//def
					
					//comp
					
				//verifier qui gagne, et le rajout des Xp au joueur
			}
			
		}
		
		//Combat contre 3mob
		
	
	
		//continuer ?
	}
	
	printf("Fin de la partie");
	
	return 0;
}