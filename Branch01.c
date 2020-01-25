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
	
	int tamponMort;
};
typedef struct GenaratePjPnj generate;

int attaque(int pv, int atq, int tdef, int def){
	
	if(tdef == 1){
		pv -= atq/def;
	}else{
		pv -= atq;
	}
	
}

int ran_a_b(){
	a = 0;
	b = 100;
	return rand()%(b-a) +a;
}

int main(){
	//Variable
		int game = 1;
		int end;
		int action;
		int tamponCriGuerre = -1;
	
	//Equipage
	
	generate deVigne = {100, 100, 100, 100, 5, 2, 0,10, 1, 0,0, 0, 0};
	generate diPlaza = {100, 100, 100, 100, 20, 3, 0,10, 1, 0,0, 0, 0};
	generate billy = {100, 100, 100, 100, 10, 4, 0,10, 1, 0,0, 0, 0};
	generate ringOfKelly = {100, 100, 100, 100, 15, 3, 0,10, 1, 0,0, 0, 0};
	
	//Seed
	srand (time (NULL));
	
	//FIGHT
	
	while(game == 1){
		
		
		int end = 0;
		
		//Combat contre chasseur
		if(deVigne.lvl < 2 && diPlaza.lvl < 2 && billy.lvl < 2 && ringOfKelly.lvl < 2){
			
			//equipage (en réinitialisant on évite de repartir au niveau 1)
			deVigne.pv = deVigne.pvMax;
			deVigne.pa = deVigne.paMax;
			deVigne.tamponMort = 0;
			diPlaza.pv = diPlaza.pvMax;
			diPlaza.pa = diPlaza.paMax;
			diPlaza.tamponMort = 0;
			billy.pv = billy.pvMax;
			billy.pa = billy.paMax;
			billy.tamponMort = 0;
			ringOfKelly.pv = ringOfKelly.pvMax;
			ringOfKelly.pa = ringOfKelly.paMax;
			ringOfKelly.tamponMort = 0;
			
			//ennemie
			generate chasseurA = {100, 100, 100, 100, 16, 2, 5, 0, 1, 0, 0, 0, 0};
			
			while(end == 0){
				
				//diminutionn ou/et Réinit tampon criGuerre
				if(tamponCriGuerre > 0){
					tamponCriGuerre -= 1;
				}else{
					if(tamponCriGuerre == 0){
						//attaque de toius le monde reinit
						billy.atq /= 2;
						deVigne.atq /= 2;
						diPlaza.atq /= 2;
						ringOfKelly.atq /= 2;
						//reinit tampon cri de guerre 
						tamponCriGuerre = -1;
					}
				}
					
				//tour Billy
				if(billy.pv > 0){
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
					
				}else{
					billy.tamponMort = 1;
				}	
				
					//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				//tour Ring Of Kelly
				if(ringOfKelly.pv > 0){
					//afficher PV PA
					
					printf("\nPV : %d\n", ringOfKelly.pv);
					printf("PA : %d\n", ringOfKelly.pa);
					
					//recup PA
					
					if(ringOfKelly.pa < ringOfKelly.paMax){
						ringOfKelly.pa += 5;
						if(ringOfKelly.pa > ringOfKelly.paMax){
							ringOfKelly.pa = ringOfKelly.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					
					if(ringOfKelly.tamponDef == 1){
						ringOfKelly.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : cri de guerre\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : cri de guerre\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						chasseurA.pv = attaque(chasseurA.pv, ringOfKelly.atq, chasseurA.tamponDef, chasseurA.def);
					}
					
					//def
					
					if(action == 2){
						ringOfKelly.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						printf("Ring Of Kelly lance cri de guerre !");
						billy.atq *= 2;
						deVigne.atq *= 2;
						diPlaza.atq *= 2;
						ringOfKelly.atq *= 2;
					}
					
				}else{
					ringOfKelly.tamponMort = 1;
				}
				
					//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
					
				//Tour Chasseur
				if(chasseurA.pv > 0){
					
					//afficher PV PA
					printf("\nPV : %d\n", chasseurA.pv);
					printf("PA : %d\n", chasseurA.pa);
					
					//recup PA
					if(chasseurA.pa < chasseurA.paMax){
						chasseurA.pa += 5;
						if(chasseurA.pa > chasseurA.paMax){
							chasseurA.pa = chasseurA.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					if(chasseurA.tamponDef == 1){
						chasseurA.tamponDef = 0;
					}
					
					//selection de l'action
					
					action = ran_a_b();
					
					//atq
					
					if(action < 45){
						action = ran_a_b();
						
						if( action < 25){
							billy.pv = attaque(billy.pv, chasseurA.atq, billy.tamponDef, billy.def);
						}
						
						if( action >=25 && action < 50){
							diPlaza.pv = attaque(diPlaza.pv, chasseurA.atq, diPlaza.tamponDef, diPlaza.def);
						}
						if( action >=50 && action < 75){
							ringOfKelly.pv = attaque(ringOfKelly.pv, chasseurA.atq, ringOfKelly.tamponDef, ringOfKelly.def);
						}
						
						if( action >= 75){
							deVigne.pv = attaque(deVigne.pv, chasseurA.atq, deVigne.tamponDef, deVigne.def);
						}
						
					}
					
					//def
					
					if(action >= 90){
						chasseurA.tamponDef = 1;
					}
					
					//comp
					
					if(action >= 45 && action < 90){
						printf("Di Plaza lance Mitrailleuse !");
						
						billy.pv -= chasseurA.atq;
						diPlaza.pv -= chasseurA.atq;
						ringOfKelly.pv -= chasseurA.atq;
						deVigne.pv -= chasseurA.atq;
					}
					
				}else{
					chasseurA.tamponMort = 1;
				}	
					
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
				//tour di Plaza
				if(diPlaza.pv > 0){
					//afficher PV PA
					
					printf("\nPV : %d\n", diPlaza.pv);
					printf("PA : %d\n", diPlaza.pa);
					
					//recup PA
					
					if(diPlaza.pa < diPlaza.paMax){
						diPlaza.pa += 5;
						if(diPlaza.pa > diPlaza.paMax){
							diPlaza.pa = diPlaza.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					
					if(diPlaza.tamponDef == 1){
						diPlaza.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (zone)\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (zone)\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						chasseurA.pv = attaque(chasseurA.pv, diPlaza.atq, chasseurA.tamponDef, chasseurA.def);
					}
					
					//def
					
					if(action == 2){
						diPlaza.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						printf("Di Plaza lance un tir de barrage !");
						chasseurA.pv -= diPlaza.atq;
					}
					
				}else{
					diPlaza.tamponMort = 1;
				}
				
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	
					
				//Tour DeVigne
				if(deVigne.pv > 0){
					//afficher PV PA
					
					printf("\nPV : %d\n", deVigne.pv);
					printf("PA : %d\n", deVigne.pa);
					
					//recup PA
					
					if(deVigne.pa < deVigne.paMax){
						deVigne.pa += 5;
						if(deVigne.pa > deVigne.paMax){
							deVigne.pa = deVigne.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					
					if(deVigne.tamponDef == 1){
						deVigne.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : bandage\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : bandage\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						chasseurA.pv = attaque(chasseurA.pv, deVigne.atq, chasseurA.tamponDef, chasseurA.def);
					}
					
					//def
					
					if(action == 2){
						deVigne.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						printf("\nTapez un chiffre pour choisir une des personnes suivantes :\n");
						printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
						scanf("%d", &action);
						
						while(action!= 1 && action!= 2 && action!= 3 && action!= 4){
							printf("action non reconnu.\n");
							printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
							scanf("%d", &action);
						}
						
						
						if(action == 1){
							printf("De Vigne pose un bandage sur Billy !");
							billy.pv += 15;
						}
						
						if(action == 2){
							printf("De Vigne pose un bandage sur Ring Of Kelly !");
							ringOfKelly.pv += 15;
						}
						
						if(action == 3){
							printf("De Vigne pose un bandage sur Di Plaza !");
							diPlaza.pv += 15;
						}
						
						if(action == 4){
							printf("De Vigne se pose un bandage !");
							deVigne.pv += 15;
						}
						
					}
					
					
				}else{
					deVigne.tamponMort = 1;
				}	

				//verifier qui gagne, et le rajout des Xp au joueur
				
				//si le joueur perd
				if(deVigne.tamponMort == 1 && deVigne.tamponMort == 1 && deVigne.tamponMort == 1 && deVigne.tamponMort == 1 &&){
					//combat perdu
					printf("\nVous avez perdu...\n");
					end = 1;
				}
				
				//si le joueur gagne
				if(chasseurA.tamponMort == 1){
					//combat perdu
					printf("\nVous avez avez gagne !\n");
					
					deVigne.xp += chasseurA.xp;
					diPlaza.xp += chasseurA.xp;
					ringOfKelly.xp += chasseurA.xp;
					billy.xp += chasseurA.xp;
					
					while(deVigne.xp > deVigne.xpMax){
						deVigne.xp -= deVigne.xpMax;
						deVigne.lvl += 1;
						deVigne.xpMax += 10;
						
						deVigne.atq += 2;
						deVigne.pv += 5;
						deVigne.pa += 5;
					}
					
					while(diPlaza.xp > diPlaza.xpMax){
						diPlaza.xp -= diPlaza.xpMax;
						diPlaza.lvl += 1;
						diPlaza.xpMax += 10;
						
						diPlaza.atq += 2;
						diPlaza.pv += 5;
						diPlaza.pa += 5;
					}
					
					while(ringOfKelly.xp > ringOfKelly.xpMax){
						ringOfKelly.xp -= ringOfKelly.xpMax;
						ringOfKelly.lvl += 1;
						ringOfKelly.xpMax += 10;
						
						ringOfKelly.atq += 2;
						ringOfKelly.pv += 5;
						ringOfKelly.pa += 5;
					}
					
					while(billy.xp > billy.xpMax){
						billy.xp -= billy.xpMax;
						billy.lvl += 1;
						billy.xpMax += 10;
						
						billy.atq += 2;
						billy.pv += 5;
						billy.pa += 5;
					}
					end = 1;
					
				}
			}
			
		}
		
		//Combat contre corvette
		if(2 <= deVigne.lvl < 3 && 2 <= diPlaza.lvl < 3 && 2 <= billy.lvl < 3 && 2 <= ringOfKelly.lvl < 3){
			
			//equipage (en réinitialisant on évite de repartir au niveau 1)
			deVigne.pv = deVigne.pvMax;
			deVigne.pa = deVigne.paMax;
			deVigne.tamponMort = 0;
			diPlaza.pv = diPlaza.pvMax;
			diPlaza.pa = diPlaza.paMax;
			diPlaza.tamponMort = 0;
			billy.pv = billy.pvMax;
			billy.pa = billy.paMax;
			billy.tamponMort = 0;
			ringOfKelly.pv = ringOfKelly.pvMax;
			ringOfKelly.pa = ringOfKelly.paMax;
			ringOfKelly.tamponMort = 0;
			
			//ennemie
			generate corvette = {100, 100, 100, 100, 20, 2, 10, 0, 1, 0, 0, 0, 0};
			
			while(end == 0){
				
				//diminutionn ou/et Réinit tampon criGuerre
				if(tamponCriGuerre > 0){
					tamponCriGuerre -= 1;
				}else{
					if(tamponCriGuerre == 0){
						//attaque de toius le monde reinit
						billy.atq /= 2;
						deVigne.atq /= 2;
						diPlaza.atq /= 2;
						ringOfKelly.atq /= 2;
						//reinit tampon cri de guerre 
						tamponCriGuerre = -1;
					}
				}
					
				//tour Billy
				if(billy.pv > 0){
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
						corvette.pv = attaque(corvette.pv, billy.atq, corvette.tamponDef, corvette.def);
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
					
				}else{
					billy.tamponMort = 1;
				}	
				
					//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				//tour Ring Of Kelly
				if(ringOfKelly.pv > 0){
					//afficher PV PA
					
					printf("\nPV : %d\n", ringOfKelly.pv);
					printf("PA : %d\n", ringOfKelly.pa);
					
					//recup PA
					
					if(ringOfKelly.pa < ringOfKelly.paMax){
						ringOfKelly.pa += 5;
						if(ringOfKelly.pa > ringOfKelly.paMax){
							ringOfKelly.pa = ringOfKelly.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					
					if(ringOfKelly.tamponDef == 1){
						ringOfKelly.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : cri de guerre\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : cri de guerre\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						corvette.pv = attaque(corvette.pv, ringOfKelly.atq, corvette.tamponDef, corvette.def);
					}
					
					//def
					
					if(action == 2){
						ringOfKelly.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						printf("Ring Of Kelly lance cri de guerre !");
						billy.atq *= 2;
						deVigne.atq *= 2;
						diPlaza.atq *= 2;
						ringOfKelly.atq *= 2;
					}
					
					
				}else{
					ringOfKelly.tamponMort = 1;
				}
				
					//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
					
				//Tour Chasseur
				if(corvette.pv > 0){
					
					//afficher PV PA
					printf("\nPV : %d\n", corvette.pv);
					printf("PA : %d\n", corvette.pa);
					
					//recup PA
					
					if(corvette.pa < corvette.paMax){
						corvette.pa += 5;
						if(corvette.pa > corvette.paMax){
							corvette.pa = corvette.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					
					if(corvette.tamponDef == 1){
						corvette.tamponDef = 0;
					}
					
					//selection de l'action
					
					action = ran_a_b();
					
					//atq
					
					if(action < 60){
						action = ran_a_b();
						
						if( action < 25){
							billy.pv = attaque(billy.pv, corvette.atq, billy.tamponDef, billy.def);
						}
						
						if( action >=25 && action < 50){
							diPlaza.pv = attaque(diPlaza.pv, corvette.atq, diPlaza.tamponDef, diPlaza.def);
						}
						if( action >=50 && action < 75){
							ringOfKelly.pv = attaque(ringOfKelly.pv, corvette.atq, ringOfKelly.tamponDef, ringOfKelly.def);
						}
						
						if( action >= 75){
							deVigne.pv = attaque(deVigne.pv, corvette.atq, deVigne.tamponDef, deVigne.def);
						}
						
					}
					
					//def
					
					if(action >= 90{
						corvette.pv += 25;
						corvette.pa -= 30;
					}
					
					//comp
					
					if(action >= 60 && action < 90){
						printf("Corvette lance Tir de barrage !");
						billy.pv -= corvette.atq;
						diPlaza.pv -= corvette.atq;
						ringOfKelly.pv -= corvette.atq;
						deVigne.pv -= corvette.atq;
					}
					
				}else{
					corvette.tamponMort = 1;
				}	
					
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
				//tour di Plaza
				if(diPlaza.pv > 0){
					//afficher PV PA
					
					printf("\nPV : %d\n", diPlaza.pv);
					printf("PA : %d\n", diPlaza.pa);
					
					//recup PA
					
					if(diPlaza.pa < diPlaza.paMax){
						diPlaza.pa += 5;
						if(diPlaza.pa > diPlaza.paMax){
							diPlaza.pa = diPlaza.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					
					if(diPlaza.tamponDef == 1){
						diPlaza.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (zone)\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (zone)\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						corvette.pv = attaque(corvette.pv, diPlaza.atq, corvette.tamponDef, corvette.def);
					}
					
					//def
					
					if(action == 2){
						diPlaza.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						printf("Di Plaza lance un tir de barrage !");
						corvette.pv -= diPlaza.atq;
					}
				
				}else{
					diPlaza.tamponMort = 1;
				}
				
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	
					
				//Tour DeVigne
				if(deVigne.pv > 0){
					//afficher PV PA
					
					printf("\nPV : %d\n", deVigne.pv);
					printf("PA : %d\n", deVigne.pa);
					
					//recup PA
					
					if(deVigne.pa < deVigne.paMax){
						deVigne.pa += 5;
						if(deVigne.pa > deVigne.paMax){
							deVigne.pa = deVigne.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//Réinit Tampon def
					
					if(deVigne.tamponDef == 1){
						deVigne.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : bandage\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : bandage\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						corvette.pv = attaque(corvette.pv, deVigne.atq, corvette.tamponDef, corvette.def);
					}
					
					//def
					
					if(action == 2){
						deVigne.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						printf("\nTapez un chiffre pour choisir une des personnes suivantes :\n");
						printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
						scanf("%d", &action);
						
						while(action!= 1 && action!= 2 && action!= 3 && action!= 4){
							printf("action non reconnu.\n");
							printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
							scanf("%d", &action);
						}
						
						
						if(action == 1){
							printf("De Vigne pose un bandage sur Billy !");
							billy.pv += 15;
						}
						
						if(action == 2){
							printf("De Vigne pose un bandage sur Ring Of Kelly !");
							ringOfKelly.pv += 15;
						}
						
						if(action == 3){
							printf("De Vigne pose un bandage sur Di Plaza !");
							diPlaza.pv += 15;
						}
						
						if(action == 4){
							printf("De Vigne se pose un bandage !");
							deVigne.pv += 15;
						}
						
					}
					
				}else{
					deVigne.tamponMort = 1;
				}	

				//verifier qui gagne, et le rajout des Xp au joueur
				
				//si le joueur perd
				if(deVigne.tamponMort == 1 && deVigne.tamponMort == 1 && deVigne.tamponMort == 1 && deVigne.tamponMort == 1 &&){
					//combat perdu
					printf("\nVous avez perdu...\n");
				}
				
				//si le joueur gagne
				if(corvette.tamponMort == 1){
					//combat perdu
					printf("\nVous avez avez gagne !\n");
					
					deVigne.xp += corvette.xp;
					diPlaza.xp += corvette.xp;
					ringOfKelly.xp += corvette.xp;
					billy.xp += corvette.xp;
					
					while(deVigne.xp > deVigne.xpMax){
						deVigne.xp -= deVigne.xpMax;
						deVigne.lvl += 1;
						deVigne.xpMax += 10;
						
						deVigne.atq += 2;
						deVigne.pv += 5;
						deVigne.pa += 5;
					}
					
					while(diPlaza.xp > diPlaza.xpMax){
						diPlaza.xp -= diPlaza.xpMax;
						diPlaza.lvl += 1;
						diPlaza.xpMax += 10;
						
						diPlaza.atq += 2;
						diPlaza.pv += 5;
						diPlaza.pa += 5;
					}
					
					while(ringOfKelly.xp > ringOfKelly.xpMax){
						ringOfKelly.xp -= ringOfKelly.xpMax;
						ringOfKelly.lvl += 1;
						ringOfKelly.xpMax += 10;
						
						ringOfKelly.atq += 2;
						ringOfKelly.pv += 5;
						ringOfKelly.pa += 5;
					}
					
					while(billy.xp > billy.xpMax){
						billy.xp -= billy.xpMax;
						billy.lvl += 1;
						billy.xpMax += 10;
						
						billy.atq += 2;
						billy.pv += 5;
						billy.pa += 5;
					}
					
				}
			}
			
		}

		//Combat contre chasseur et corvette
		
	
	
		//continuer ?
	}
	
	printf("Fin de la partie");
	
	return 0;
}