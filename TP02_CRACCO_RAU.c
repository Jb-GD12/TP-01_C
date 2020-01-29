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
	
	int aggro;
};
typedef struct GenaratePjPnj generate;

int attaque(int pv, int atq, int tdef, int def){
	
	if(tdef == 1){
		pv -= atq/def;
	}else{
		pv -= atq;
	}
	return pv;
}

int ran_a_b(){
	int a = 0;
	int b = 100;
	return rand()%(b-a) +a;
}

int main(){
	//Variable
		int game = 1;
		int end;
		int action;
		int probaAttaque;
		int tamponCriGuerre = -1;
		int choix;
	
	//Equipage
	
	generate deVigne = {100, 100, 100, 100, 5, 2, 0,10, 1, 0, 0};
	generate diPlaza = {100, 100, 100, 100, 20, 3, 0,10, 1, 0, 0};
	generate billy = {100, 100, 100, 100, 10, 4, 0,10, 1, 0, 0};
	generate ringOfKelly = {100, 100, 100, 100, 15, 3, 0,10, 1, 0, 0};
	
	//Seed
	srand (time (NULL));
	
	//Intro
	
	printf ("Vous etes le capitaine de la corvette l'Oeil.\nMenez votre equipage afin de vaincre les vaisseaux ennemis !\nBonne chance.\n");
	printf("\n COMPOSITION DE L'EQUIPAGE :\n");
	printf("\n MAUREEN RING OF KELLY\nPoste : Second\nCoup special : cri de guerre\nDouble l'attaque des allies pendant 2 tours.\n");
	printf("\n LEO DI PLAZA\nPoste : Artilleur\nCoup special : Tir de barrage\nAttaque de zone perforante.\n");
	printf("\n LUCAS DE VIGNE\nPoste : Infirmier\nCoup special : Bandage\nSoigne un membre de l'equipage.\n");
	printf("\n BILLY\nPoste : Premiere classe\nCoup special : Insulte\nPrend l'aggro de l'ennemi.\n");
	
	printf("\n*************************************************************************************************\n");
	
	//FIGHT
	
	while(game == 1){
		
		int end = 0;
		
		//Combat contre chasseur
		if(deVigne.lvl == 1 && diPlaza.lvl == 1 && billy.lvl == 1 && ringOfKelly.lvl == 1){
			
			end = 0;
			
			//equipage (en réinitialisant on évite de repartir au niveau 1)
			deVigne.pv = deVigne.pvMax;
			deVigne.pa = deVigne.paMax;
			
			diPlaza.pv = diPlaza.pvMax;
			diPlaza.pa = diPlaza.paMax;
			
			billy.pv = billy.pvMax;
			billy.pa = billy.paMax;
			billy.aggro = 0;
			
			ringOfKelly.pv = ringOfKelly.pvMax;
			ringOfKelly.pa = ringOfKelly.paMax;
			
			tamponCriGuerre = -1;
			
			//ennemie
			generate chasseurA = {150, 150, 100, 100, 16, 2, 5, 0, 1, 0, 0};
			
			printf("\nUn chasseur vous attaque !\n");
			printf("\nPV : %d/%d\n",chasseurA.pv,chasseurA.pvMax);
			printf("\nPA : %d/%d\n",chasseurA.pa,chasseurA.paMax);
			
			while(end == 0){
				
				//diminutionn ou/et Réinit tampon criGuerre
				
				if(tamponCriGuerre > 0){
					tamponCriGuerre -= 1;
				}else{
					if(tamponCriGuerre == 0){
						//attaque de tous le monde reinit
						billy.atq /= 2;
						deVigne.atq /= 2;
						diPlaza.atq /= 2;
						ringOfKelly.atq /= 2;
						//reinit tampon cri de guerre 
						tamponCriGuerre = -1;
					}
				}
				
				printf("\n*************************************************************************************************\n");
				
				//tour Billy
				
				if(billy.pv > 0 && end == 0 ){
					
					printf("\nBILLY\n");
					
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
					
					//Verif aggro
					
					if(billy.aggro > 0){
						billy.aggro -= 1;
					}
				
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", billy.pv,billy.pvMax);
					printf("PA : %d/%d\n", billy.pa,billy.paMax);
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : insulte\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : insulte (5 PA)\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						chasseurA.pv = attaque(chasseurA.pv, billy.atq, chasseurA.tamponDef, chasseurA.def);
						printf("\nBilly attaque.\n");
						if(chasseurA.pv <= 0){
							end = 1;
						}
						
					}
					
					//def
					
					if(action == 2){
						
						billy.tamponDef = 1;
						printf("\nBilly se defend.\n");
						
					}
					
					//comp
					
					if(action == 3){
						
						if(billy.pa >= 5 && billy.aggro == 0){
							
							printf("\nBilly lance Insulte.\n");
							printf("\nBilly : \"Heu... Heu... Bande de MECHANTS !\"\n");
							billy.aggro = 4;
							
							billy.pa -= 5;
							
						}else {
							if(billy.aggro > 0){
								printf("\nL'ennemi est deja insulte\n");
							}
							
							if(billy.pa < 5){
								printf("\nBilly a trop pris la confiance, du coup Maureen lui fait claquer des pompes\n");
								printf("(en fait t'as pas assez de PA.)\n(C'est con.)\n");
							}
							
						}
						
					}
					
				}
				
				//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				printf("\n*************************************************************************************************\n");	

				//tour Ring Of Kelly
				
				if(ringOfKelly.pv > 0 && end == 0){
					
					printf("\nRING OF KELLY\n");
					
					//recup PA
					
					if(ringOfKelly.pa < ringOfKelly.paMax){
						
						ringOfKelly.pa += 5;
						
						if(ringOfKelly.pa > ringOfKelly.paMax){
							
							ringOfKelly.pa = ringOfKelly.paMax;
							
						}
						
						printf("\ngain de 5PA\n");
						
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", ringOfKelly.pv,ringOfKelly.pvMax);
					printf("PA : %d/%d\n", ringOfKelly.pa,ringOfKelly.paMax);
					
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
						printf("\nRing of Kelly attaque.\n");
						
						if(chasseurA.pv <= 0){
							
							end = 1;
							
						}
						
					}
					
					//def
					
					if(action == 2){
						
						ringOfKelly.tamponDef = 1;
						printf("\nRing Of Kelly se defend.\n");
						
					}
					
					//comp
					
					if(action == 3){
						
						if(ringOfKelly.pa >= 40 && tamponCriGuerre == -1){
							
							printf("Ring Of Kelly lance cri de guerre !");
							printf("\nRing of Kelly : \"P... Pour... POUR LA WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGH !!!!\n");
							billy.atq *= 2;
							deVigne.atq *= 2;
							diPlaza.atq *= 2;
							ringOfKelly.atq *= 2;
							
							tamponCriGuerre = 2;
							
							ringOfKelly.pa -= 40;
							
						}else{
							if(tamponCriGuerre > 0){
								printf("\nMaureen n'a pas assez de voix pour stimuler les troupes...\n");
							}
							
							if(ringOfKelly.pa < 5){
								printf("\nMaureen n'a pas assez de voix pour stimuler les troupes...\n");
							}
							
						}
						
					}
					
				}
				
					//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
					
				printf("\n*************************************************************************************************\n");
				
				printf("\nCHASSEUR\n");
				
				//Tour Chasseur
				if(chasseurA.pv > 0 && end == 0){
					
					//recup 
					
					if(chasseurA.pa < chasseurA.paMax){
						
						chasseurA.pa += 5;
						
						if(chasseurA.pa > chasseurA.paMax){
							
							chasseurA.pa = chasseurA.paMax;
							
						}
						
						printf("\ngain de 5PA\n");
						
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", chasseurA.pv,chasseurA.pvMax);
					printf("PA : %d/%d\n", chasseurA.pa,chasseurA.paMax);
					
					//Réinit Tampon def
					
					if(chasseurA.tamponDef == 1){
						
						chasseurA.tamponDef = 0;
						
					}
					
					//selection de l'action
					
					action = ran_a_b();
					
					//atq
					
					if(action < 45){
						
						if(billy.aggro > 0){
							
							printf("\nLe chasseur attaque Billy.\n");
							billy.pv = attaque(billy.pv, chasseurA.atq, billy.tamponDef, billy.def);
							
						}else{
							
							probaAttaque = ran_a_b();
							
							if( probaAttaque < 25){
								printf("\nLe chasseur attaque Billy.\n");
								billy.pv = attaque(billy.pv, chasseurA.atq, billy.tamponDef, billy.def);
							}
							
							if( probaAttaque >=25 && action < 50){
								printf("\nLe chasseur attaque Di Plaza.\n");
								diPlaza.pv = attaque(diPlaza.pv, chasseurA.atq, diPlaza.tamponDef, diPlaza.def);
							}
							if( probaAttaque >=50 && action < 75){
								printf("\nLe chasseur attaque Ring Of Kelly.\n");
								ringOfKelly.pv = attaque(ringOfKelly.pv, chasseurA.atq, ringOfKelly.tamponDef, ringOfKelly.def);
							}
							
							if( probaAttaque >= 75){
								printf("\nLe chasseur attaque De Vigne.\n");
								deVigne.pv = attaque(deVigne.pv, chasseurA.atq, deVigne.tamponDef, deVigne.def);
							}
							
						}
						
					}
					
					//def
					
					if(action >= 80){
						
						printf("\nLe chasseur amorce une mannoeuvre d'evitement.\n");
						chasseurA.tamponDef = 1;
						
					}
					
					//comp
					
					if(action > 46 && action < 79){
						
						if(chasseurA.pa > 30){
							
							printf("\nLe chasseur lance Mitrailleuse sur l'equipage !\n");
							
							billy.pv -= chasseurA.atq;
							diPlaza.pv -= chasseurA.atq;
							ringOfKelly.pv -= chasseurA.atq;
							deVigne.pv -= chasseurA.atq;
							
							chasseurA.pa -= 30;
							
						}else{
							
							printf("\nLe chasseur observe votre navire");
							
						}
						
					}
					
				}	
					
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				printf("\n*************************************************************************************************\n");
				
				//tour di Plaza
				
				if(diPlaza.pv > 0 && end == 0){
					
					printf("\nDI PLAZA\n");
					
					if(diPlaza.pa < diPlaza.paMax){
						diPlaza.pa += 5;
						if(diPlaza.pa > diPlaza.paMax){
							diPlaza.pa = diPlaza.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					
					//afficher PV PA
					printf("\nPV : %d/%d\n", diPlaza.pv,diPlaza.pvMax);
					printf("PA : %d/%d\n", diPlaza.pa,diPlaza.paMax);
					
					//Réinit Tampon def
					if(diPlaza.tamponDef == 1){
						diPlaza.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (40 PA)\n");
					scanf("%d", &action);
					
					//verif action
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (40 PA)\n");
						scanf("%d", &action);
					}
					
					//atq
					if(action == 1){
						printf("\nDi Plaza attaque.*\n");
						chasseurA.pv = attaque(chasseurA.pv, diPlaza.atq, chasseurA.tamponDef, chasseurA.def);
						
						if(chasseurA.pv <= 0){
							end = 1;
						}
					}
					
					//def
					if(action == 2){
						printf("\nDi Plaza se defend.\n");
						diPlaza.tamponDef = 1;
					}
					
					//comp
					if(action == 3){
						if(diPlaza.pa >= 40){
						printf("Di Plaza lance un tir de barrage !");
						chasseurA.pv -= diPlaza.atq;
						}else{
							printf("\nLes canons sont enrayes, DiPlaza ne peut pas les utiliser...\n");
						}
					}
					
				}
				
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	

				printf("\n*************************************************************************************************\n");
				
				//Tour DeVigne
				if(deVigne.pv > 0 && end == 0){
					
					printf("\nDE VIGNE\n");
					
					//recup PA
					
					if(deVigne.pa < deVigne.paMax){
						deVigne.pa += 5;
						if(deVigne.pa > deVigne.paMax){
							deVigne.pa = deVigne.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", deVigne.pv,deVigne.pvMax);
					printf("PA : %d/%d\n", deVigne.pa,deVigne.paMax);
					
					
					
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
						printf("1 : attaquer\n2 : defendre\n3 : bandage (10 PA)\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						printf("\nDe Vigne attaque.\n");
						chasseurA.pv = attaque(chasseurA.pv, deVigne.atq, chasseurA.tamponDef, chasseurA.def);
						
						if(chasseurA.pv <= 0){
							end = 1;
						}
					}
					
					//def
					
					if(action == 2){
						printf("\nDe Vigne se defend.\n");
						deVigne.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						if(deVigne.pa >= 10){
							printf("\nTapez un chiffre pour choisir une des personnes suivantes :\n");
							printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
							scanf("%d", &action);
							
							while(action!= 1 && action!= 2 && action!= 3 && action!= 4){
								printf("action non reconnu.\n");
								printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
								scanf("%d", &action);
							}
							
							
							if(action == 1){
								if(billy.pv > 0){
									printf("De Vigne pose un bandage sur Billy !");
									billy.pv += 15;
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 2){
								if(ringOfKelly.pv > 0){
									printf("De Vigne pose un bandage sur Ring Of Kelly !");
									ringOfKelly.pv += 15;
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 3){
								if(diPlaza.pv > 0){
									printf("De Vigne pose un bandage sur Di Plaza !");
									diPlaza.pv += 15;
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 4){
								printf("De Vigne se pose un bandage !");
								deVigne.pv += 15;
							}
							deVigne.pa -= 10;
							
						}else{
							printf("Suite a une secousse, DeVigne tombe dans les escalier.");
						}
						
					}
					
				}
				
				
				//verifier qui gagne, et le rajout des Xp au joueur
				
				//si le joueur perd
				if(deVigne.pv <= 0 && diPlaza.pv <= 0 && ringOfKelly.pv <= 0 && billy.pv <= 0 ){
					//combat perdu
					printf("\nVous avez perdu...\n");
					end = 1;
				}
				
			}
			
			//si le joueur gagne
			if(chasseurA.pv <= 0){
				//combat reussi
				printf("\nVous avez avez gagne !\n");
				end = 1;
				
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
					printf("\nDe Vigne monte de niveau.\n");
				}
				
				while(diPlaza.xp > diPlaza.xpMax){
					diPlaza.xp -= diPlaza.xpMax;
					diPlaza.lvl += 1;
					diPlaza.xpMax += 10;
					
					diPlaza.atq += 2;
					diPlaza.pv += 5;
					diPlaza.pa += 5;
					printf("\nDi Plaza monte de niveau.\n");
				}
				
				while(ringOfKelly.xp > ringOfKelly.xpMax){
					ringOfKelly.xp -= ringOfKelly.xpMax;
					ringOfKelly.lvl += 1;
					ringOfKelly.xpMax += 10;
					
					ringOfKelly.atq += 2;
					ringOfKelly.pv += 5;
					ringOfKelly.pa += 5;
					printf("\nRing Of Kelly monte de niveau.\n");
				}
				
				while(billy.xp > billy.xpMax){
					billy.xp -= billy.xpMax;
					billy.lvl += 1;
					billy.xpMax += 10;
					
					billy.atq += 2;
					billy.pv += 5;
					billy.pa += 5;
					printf("\nBilly monte de niveau.\n");
				}
				
			}
			
		}
		
		//--------------------------------------------------------------------------------------------------------------------------------
		
		//Combat contre corvette
		if(deVigne.lvl == 2 && diPlaza.lvl == 2 && billy.lvl == 2 && ringOfKelly.lvl == 2 && end == 1){
			
			end = 1;
			
			//equipage (en réinitialisant on évite de repartir au niveau 1)
			deVigne.pv = deVigne.pvMax;
			deVigne.pa = deVigne.paMax;
			
			diPlaza.pv = diPlaza.pvMax;
			diPlaza.pa = diPlaza.paMax;
			
			billy.pv = billy.pvMax;
			billy.pa = billy.paMax;
			billy.aggro = 0;
			
			ringOfKelly.pv = ringOfKelly.pvMax;
			ringOfKelly.pa = ringOfKelly.paMax;
			
			tamponCriGuerre = -1;
			
			//ennemie
			generate corvette = {200, 200, 100, 100, 20, 2, 10, 0, 1, 0, 0};
			
			printf("\n*************************************************************************************************\n");
			printf("\nUne corvette ennemi vous attaque !.\n");
			printf("\nPV : %d/%d\n",corvette.pv,corvette.pvMax);
			printf("\nPA : %d/%d\n",corvette.pa,corvette.paMax);

			while(end == 0){
				
				//diminutionn ou/et Réinit tampon criGuerre
				if(tamponCriGuerre > 0){
					tamponCriGuerre -= 1;
				}else{
					if(tamponCriGuerre == 0){
						//attaque de tous le monde reinit
						billy.atq /= 2;
						deVigne.atq /= 2;
						diPlaza.atq /= 2;
						ringOfKelly.atq /= 2;
						
						//reinit tampon cri de guerre 
						tamponCriGuerre = -1;
					}
				}
					
				printf("\nBILLY\n");
				
				//tour Billy
				
				if(billy.pv > 0 && end == 0){
					
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
					
					//Verif aggro
					if(billy.aggro > 0){
						billy.aggro -= 1;
					}
					
				
					//afficher PV PA
					printf("\nPV : %d/%d\n", billy.pv,billy.pvMax);
					printf("PA : %d/%d\n", billy.pa,billy.paMax);
					
					//selection de l'action
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : insulte (5 PA)\n");
					scanf("%d", &action);
					
					//verif action
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : insulte\n");
						scanf("%d", &action);
					}
					
					//atq
					if(action == 1){
						printf("Billy attaque.");
						corvette.pv = attaque(corvette.pv, billy.atq, corvette.tamponDef, corvette.def);
						
						if(corvette.pv <= 0){
							end = 1;
						}
					}
					
					//def
					if(action == 2){
						printf("\nBilly se defend.\n");
						billy.tamponDef = 1;
					}
					
					//comp
					if(action == 3){
						
						if(billy.pa >= 5 && billy.aggro == 0){
							
							printf("\nBilly lance Insulte.\n");
							printf("\nBilly : \"Heu... Heu... Bande de MECHANTS !\"\n");
							billy.aggro = 4;
							
							billy.pa -= 5;
							
						}else {
							if(billy.aggro > 0){
								printf("\nL'ennemi est deja insulte\n");
							}
							
							if(billy.pa < 5){
								printf("\nBilly a trop pris la confiance, du coup Maureen lui fait claquer des pompes\n");
								printf("(en fait t'as pas assez de PA.)\n(C'est con.)\n");
							}
							
						}
							
					}
					
					
				}	
				
				//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				printf("\nRING OF KELLY\n");
				//tour Ring Of Kelly
				if(ringOfKelly.pv > 0 && end == 0){
					
					//recup PA
					
					if(ringOfKelly.pa < ringOfKelly.paMax){
						ringOfKelly.pa += 5;
						if(ringOfKelly.pa > ringOfKelly.paMax){
							ringOfKelly.pa = ringOfKelly.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", ringOfKelly.pv,ringOfKelly.pvMax);
					printf("PA : %d/%d\n", ringOfKelly.pa,ringOfKelly.paMax);
					
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
						printf("1 : attaquer\n2 : defendre\n3 : cri de guerre (40 pa)\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						printf("\nRing of Kelly attaque.\n");
						corvette.pv = attaque(corvette.pv, ringOfKelly.atq, corvette.tamponDef, corvette.def);
						
						if(corvette.pv <= 0){
							end = 1;
						}
					}
					
					//def
					
					if(action == 2){
						printf("\nRing of Kelly se defend.\n");
						ringOfKelly.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						
						if(ringOfKelly.pa >= 40 && tamponCriGuerre == -1){
							
							printf("Ring Of Kelly lance cri de guerre !");
							printf("\nRing of Kelly : \"P... Pour... POUR LA WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGH !!!!\n");
							billy.atq *= 2;
							deVigne.atq *= 2;
							diPlaza.atq *= 2;
							ringOfKelly.atq *= 2;
							
							tamponCriGuerre = 2;
							
							ringOfKelly.pa -= 40;
							
						}else{
							if(tamponCriGuerre > 0){
								printf("\nMaureen n'a pas assez de voix pour stimuler les troupes...");
							}
							
							if(ringOfKelly.pa < 5){
								printf("\nMaureen n'a pas assez de voix pour stimuler les troupes...");
							}
							
						}
						
					}
					
				}
				
					//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				printf("\nCORVETTE\n");				
				//Tour Corvette
				if(corvette.pv > 0 && end == 0){
					
					//afficher PV PA
					printf("\nPV : %d/%d\n", corvette.pv,corvette.pvMax);
					printf("PA : %d/%d\n", corvette.pa,corvette.paMax);
					
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
						
						if(billy.aggro > 0){
							
							printf("\nLa corvette attaque Billy.\n");
							billy.pv = attaque(billy.pv, corvette.atq, billy.tamponDef, billy.def);
							
						}else{
							
							probaAttaque = ran_a_b();
							
							if( probaAttaque < 25){
								printf("\nLa corvette attaque Billy.\n");
								billy.pv = attaque(billy.pv, corvette.atq, billy.tamponDef, billy.def);
							}
							
							if( probaAttaque >=25 && probaAttaque < 50){
								printf("\nLa corvette attaque Di Plaza.\n");
								diPlaza.pv = attaque(diPlaza.pv, corvette.atq, diPlaza.tamponDef, diPlaza.def);
							}
							if( probaAttaque >=50 && probaAttaque < 75){
								printf("\nLa corvette attaque >Ring Of Kelly.\n");
								ringOfKelly.pv = attaque(ringOfKelly.pv, corvette.atq, ringOfKelly.tamponDef, ringOfKelly.def);
							}
							
							if( probaAttaque >= 75){
								printf("\nLa corvette attaque De Vigne.\n");
								deVigne.pv = attaque(deVigne.pv, corvette.atq, deVigne.tamponDef, deVigne.def);
							}
							
						}
						
					}
					
					//rep
					
					if(action >= 90){
						printf("\nL'équipage de la corvette répare le navire !\n");
						corvette.pv += 25;
						corvette.pa -= 30;
					}
					
					//comp
					
					if(action >= 60 && action < 90){
						printf(" \nCorvette lance Tir de barrage !\n");
						billy.pv -= corvette.atq;
						diPlaza.pv -= corvette.atq;
						ringOfKelly.pv -= corvette.atq;
						deVigne.pv -= corvette.atq;
					}
					
				}	
					
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				printf("\nDI PLAZA\n");
				
				//tour di Plaza
				if(diPlaza.pv > 0 && end == 0){
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", diPlaza.pv,diPlaza.pvMax);
					printf("PA : %d/%d\n", diPlaza.pa,diPlaza.paMax);
					
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
						printf("\nDi Plaza attaque.\n");
						corvette.pv = attaque(corvette.pv, diPlaza.atq, corvette.tamponDef, corvette.def);
						if(corvette.pv <= 0){
							end = 1;
						}
					}
					
					//def
					
					if(action == 2){
						printf("\nDi Plaza se defend.\n");
						diPlaza.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						if(diPlaza.pa >= 40){
						printf("Di Plaza lance un tir de barrage !");
						corvette.pv -= diPlaza.atq;
						}else{
							printf("\nLes canons sont enrayes, DiPlaza ne peut pas les utiliser...\n");
						}
					}
				
				}
				
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	
				
				printf("\nDE VIGNE\n");
				
				//Tour DeVigne
				if(deVigne.pv > 0 && end == 0){
					
					//recup PA
					
					if(deVigne.pa < deVigne.paMax){
						deVigne.pa += 5;
						if(deVigne.pa > deVigne.paMax){
							deVigne.pa = deVigne.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", deVigne.pv,deVigne.pvMax);
					printf("PA : %d/%d\n", deVigne.pa,deVigne.paMax);
					
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
						printf("\nDe Vigne attaque.\n");
						corvette.pv = attaque(corvette.pv, deVigne.atq, corvette.tamponDef, corvette.def);
						
						if(corvette.pv <= 0){
							end = 1;
						}
					}
					
					//def
					
					if(action == 2){
						printf("\nDe Vigne se defend.\n");
						deVigne.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						if(deVigne.pa >= 10){
							printf("\nTapez un chiffre pour choisir une des personnes suivantes :\n");
							printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
							scanf("%d", &action);
							
							while(action!= 1 && action!= 2 && action!= 3 && action!= 4){
								printf("action non reconnu.\n");
								printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
								scanf("%d", &action);
							}
							
							
							if(action == 1){
								if(billy.pv > 0){
									printf("De Vigne pose un bandage sur Billy !");
									billy.pv += 15;
									
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 2){
								if(ringOfKelly.pv > 0){
									printf("De Vigne pose un bandage sur Ring Of Kelly !");
									ringOfKelly.pv += 15;
									
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 3){
								if(diPlaza.pv > 0){
									printf("De Vigne pose un bandage sur Di Plaza !");
									diPlaza.pv += 15;
									
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 4){
								printf("De Vigne se pose un bandage !");
								deVigne.pv += 15;
							}
							deVigne.pa -= 10;
							
						}else{
							printf("Suite a une secousse, DeVigne tombe dans les escalier.");
						}
						
					}
					
				}	

				//verifier qui gagne, et le rajout des Xp au joueur
				
				//si le joueur perd
				if(deVigne.pv <= 0 && diPlaza.pv <= 0 && ringOfKelly.pv <= 0 && billy.pv <= 0){
					//combat perdu
					printf("\nVous avez perdu...\n");
				}
					
				
			}
			
			//si le joueur gagne
			if(corvette.pv <= 0){
				//combat gagne
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
					printf("\nDe Vigne monte de niveau.\n");
				}
				
				while(diPlaza.xp > diPlaza.xpMax){
					diPlaza.xp -= diPlaza.xpMax;
					diPlaza.lvl += 1;
					diPlaza.xpMax += 10;
					
					diPlaza.atq += 2;
					diPlaza.pv += 5;
					diPlaza.pa += 5;
					printf("\nDi Plaza monte de niveau.\n");
				}
				
				while(ringOfKelly.xp > ringOfKelly.xpMax){
					ringOfKelly.xp -= ringOfKelly.xpMax;
					ringOfKelly.lvl += 1;
					ringOfKelly.xpMax += 10;
					
					ringOfKelly.atq += 2;
					ringOfKelly.pv += 5;
					ringOfKelly.pa += 5;
					printf("\nRing Of Kelly monte de niveau.\n");
				}
				
				while(billy.xp > billy.xpMax){
					billy.xp -= billy.xpMax;
					billy.lvl += 1;
					billy.xpMax += 10;
					
					billy.atq += 2;
					billy.pv += 5;
					billy.pa += 5;
					printf("\nBilly monte de niveau.\n");
				}
			}
		}

		//--------------------------------------------------------------------------------------------------------------------------------

		//Combat contre chasseur et corvette
		if(deVigne.lvl >= 3 && diPlaza.lvl  >= 3 && billy.lvl  >= 3 && ringOfKelly.lvl  >= 3 && end == 1){
			
			end = 0;
			
			//equipage (en réinitialisant on évite de repartir au niveau 1)
				deVigne.pv = deVigne.pvMax;
				deVigne.pa = deVigne.paMax;
				
				diPlaza.pv = diPlaza.pvMax;
				diPlaza.pa = diPlaza.paMax;
				
				billy.pv = billy.pvMax;
				billy.pa = billy.paMax;
				billy.aggro = 0;
				
				ringOfKelly.pv = ringOfKelly.pvMax;
				ringOfKelly.pa = ringOfKelly.paMax;
				
				tamponCriGuerre = -1;
				
			
			//ennemie
				generate corvette = {200, 200, 100, 100, 20, 4, 10, 0, 1, 0, 0};
				generate chasseurA = {150, 150, 100, 100, 16, 2, 5, 0, 1, 0, 0};
				
				printf(\n*************************************************************************************************\n);
				printf("\nUn chasseur vous attaque !\n");
				printf("\nPV : %d/%d\n",chasseurA.pv,chasseurA.pvMax);
				printf("\nPA : %d/%d\n",chasseurA.pa,chasseurA.paMax);
				
				printf("\nUne corvette vous attaque !\n");
				printf("\nPV : %d/%d\n",corvette.pv,corvette.pvMax);
				printf("\nPA : %d/%d\n",corvette.pa,corvette.paMax);
			
			while(end == 0){
				
				//diminutionn ou/et Réinit tampon criGuerre
				
				if(tamponCriGuerre > 0){
					tamponCriGuerre -= 1;
				}else{
					if(tamponCriGuerre == 0){
						//attaque de tous le monde reinit
						billy.atq /= 2;
						deVigne.atq /= 2;
						diPlaza.atq /= 2;
						ringOfKelly.atq /= 2;
						//reinit tampon cri de guerre 
						tamponCriGuerre = -1;
					}
				}
				
				printf("\n*************************************************************************************************\n");
				
				//tour Billy
				
				if(billy.pv > 0 && end == 0){
					
					printf("\nBILLY\n");
					
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
					
					//Verif aggro
					
					if(billy.aggro > 0){
						billy.aggro -= 1;
					}
				
					//afficher PV PA
					printf("\nPV : %d/%d\n", billy.pv,billy.pvMax);
					printf("PA : %d/%d\n", billy.pa,billy.paMax);
					
					//selection de l'action
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : insulte (5 PA)\n");
					scanf("%d", &action);
					
					//verif action
					
					while(action!= 1 && action!= 2 && action!= 3){
						
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : insulte\n");
						scanf("%d", &action);
						
					}
					
					//atq
					
					if(action == 1){
						printf("\nQui attaquer ?\n");
						printf("1 : chasseur\n2 : corvette\n");
						scanf("%d", &choix);
						
						//verif action
						while(choix!= 1 && choix!= 2){
							
							printf("action non reconnu.\n");
							printf("1 : chasseur\n2 : corvette\n");
							scanf("%d", &choix);
							
						}
						
						if(choix == 1){
							chasseurA.pv = attaque(chasseurA.pv, billy.atq, chasseurA.tamponDef, chasseurA.def);
							printf("\nBilly attaque le chasseur.\n");
							
						}
						if(choix == 2){
							corvette.pv = attaque(corvette.pv, billy.atq, corvette.tamponDef, corvette.def);
							printf("\nBilly attaque la corvette.\n");
							
						}
						
						if(chasseurA.pv <= 0 && corvette.pv <= 0){
							end = 1;
						}
						
					}
					
					//def
					
					if(action == 2){
						
						billy.tamponDef = 1;
						printf("\nBilly se defend.\n");
						
					}
					
					//comp
					
					if(action == 3){
						if(billy.pa >= 5 && billy.aggro == 0){
							
							printf("\nBilly lance Insulte.\n");
							printf("\nBilly : \"Heu... Heu... Bande de MECHANTS !\"\n");
							billy.aggro = 4;
							
							billy.pa -= 5;
							
						}else {
							if(billy.aggro > 0){
								printf("\nL'ennemi est deja insulte\n");
							}
							
							if(billy.pa < 5){
								printf("\nBilly a trop pris la confiance, du coup Maureen lui fait claquer des pompes\n");
								printf("(en fait t'as pas assez de PA.)\n(C'est con.)\n");
							}
							
						}
							
					}
					
				}
				
				//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				printf("\n*************************************************************************************************\n");	

				//tour Ring Of Kelly
				
				if(ringOfKelly.pv > 0 && end == 0){
					
					printf("\nRING OF KELLY\n");
					
					//recup PA
					
					if(ringOfKelly.pa < ringOfKelly.paMax){
						
						ringOfKelly.pa += 5;
						
						if(ringOfKelly.pa > ringOfKelly.paMax){
							
							ringOfKelly.pa = ringOfKelly.paMax;
							
						}
						
						printf("\ngain de 5PA\n");
						
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", ringOfKelly.pv,ringOfKelly.pvMax);
					printf("PA : %d/%d\n", ringOfKelly.pa,ringOfKelly.paMax);
					
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
						printf("\nQui attaquer ?\n");
						printf("1 : chasseur\n2 : corvette\n");
						scanf("%d", &choix);
						
						//verif action
						
						while(choix!= 1 && choix!= 2){
							
							printf("cible non reconnu.\n");
							printf("1 : chasseur\n2 : corvette\n");
							scanf("%d", &choix);
							
						}
						if(choix == 1){
							chasseurA.pv = attaque(chasseurA.pv, ringOfKelly.atq, chasseurA.tamponDef, chasseurA.def);
							printf("\nRing of Kelly attaque le chasseur.\n");
							
						}
						if(choix == 2){
							corvette.pv = attaque(corvette.pv, ringOfKelly.atq, corvette.tamponDef, corvette.def);
							printf("\nRing of Kelly attaque la corvette.\n");
							
						}
						
						if(chasseurA.pv <= 0 && corvette.pv <= 0){
							end = 1;
						}
						
					}
					
					//def
					
					if(action == 2){
						
						ringOfKelly.tamponDef = 1;
						printf("\nRing Of Kelly se defend.\n");
						
					}
					
					//comp
					
					if(action == 3){
						
						if(ringOfKelly.pa >= 40 && tamponCriGuerre == -1){
							
							printf("Ring Of Kelly lance cri de guerre !");
							printf("\nRing of Kelly : \"P... Pour... POUR LA WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGH !!!!\n");
							billy.atq *= 2;
							deVigne.atq *= 2;
							diPlaza.atq *= 2;
							ringOfKelly.atq *= 2;
							
							tamponCriGuerre = 2;
							
							ringOfKelly.pa -= 40;
							
						}else{
							if(tamponCriGuerre > 0){
								printf("\nMaureen n'a pas assez de voix pour stimuler les troupes...");
							}
							
							if(ringOfKelly.pa < 5){
								printf("\nMaureen n'a pas assez de voix pour stimuler les troupes...");
							}
							
						}
						
					}
					
				}
				
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
					
				printf("\n*************************************************************************************************\n");
				
				
				
				//Tour Chasseur
				if(chasseurA.pv > 0 && end == 0){
					
					printf("\nCHASSEUR\n");
					
					//recup 
					
					if(chasseurA.pa < chasseurA.paMax){
						
						chasseurA.pa += 5;
						
						if(chasseurA.pa > chasseurA.paMax){
							
							chasseurA.pa = chasseurA.paMax;
							
						}
						
						printf("\ngain de 5PA\n");
						
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", chasseurA.pv,chasseurA.pvMax);
					printf("PA : %d/%d\n", chasseurA.pa,chasseurA.paMax);
					
					//Réinit Tampon def
					
					if(chasseurA.tamponDef == 1){
						
						chasseurA.tamponDef = 0;
						
					}
					
					//selection de l'action
					
					action = ran_a_b();
					
					//atq
					
					if(action < 45){
						
						if(billy.aggro > 0){
							
							printf("\nLe chasseur attaque Billy.\n");
							billy.pv = attaque(billy.pv, chasseurA.atq, billy.tamponDef, billy.def);
							
						}else{
							
							probaAttaque = ran_a_b();
							
							if( probaAttaque < 25){
								printf("\nLe chasseur attaque Billy.\n");
								billy.pv = attaque(billy.pv, chasseurA.atq, billy.tamponDef, billy.def);
							}
							
							if( probaAttaque >=25 && action < 50){
								printf("\nLe chasseur attaque Di Plaza.\n");
								diPlaza.pv = attaque(diPlaza.pv, chasseurA.atq, diPlaza.tamponDef, diPlaza.def);
							}
							if( probaAttaque >=50 && action < 75){
								printf("\nLe chasseur attaque Ring Of Kelly.\n");
								ringOfKelly.pv = attaque(ringOfKelly.pv, chasseurA.atq, ringOfKelly.tamponDef, ringOfKelly.def);
							}
							
							if( probaAttaque >= 75){
								printf("\nLe chasseur attaque De Vigne.\n");
								deVigne.pv = attaque(deVigne.pv, chasseurA.atq, deVigne.tamponDef, deVigne.def);
							}
							
						}
						
						if(billy.pv <= 0 && ringOfKelly.pv <= 0 && deVigne.pv <= 0 && diPlaza.pv <= 0){
							end = 1;
						}
						
					}
					
					//def
					
					if(action >= 90){
						
						printf("\nLe chasseur amorce une mannoeuvre d'evitement.\n");
						chasseurA.tamponDef = 1;
						
					}
					
					//comp
					
					if(action > 46 && action < 89){
						
						if(chasseurA.pa > 30){
							
							printf("\nLe chasseur lance Mitrailleuse sur l'equipage !\n");
							
							billy.pv -= chasseurA.atq;
							diPlaza.pv -= chasseurA.atq;
							ringOfKelly.pv -= chasseurA.atq;
							deVigne.pv -= chasseurA.atq;
							
							chasseurA.pa -= 30;
							
							if(billy.pv <= 0 && ringOfKelly.pv <= 0 && deVigne.pv <= 0 && diPlaza.pv <= 0){
								end = 1;
							}
							
						}else{
							
							printf("\nLe chasseur observe votre navire");
							
						}
						
					}
					
				}	
					
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				printf("\n*************************************************************************************************\n");
				
				//tour di Plaza
				
				if(diPlaza.pv > 0 && end == 0){
					
					printf("\nDI PLAZA\n");
					
					//recup PA
					if(diPlaza.pa < diPlaza.paMax){
						diPlaza.pa += 5;
						if(diPlaza.pa > diPlaza.paMax){
							diPlaza.pa = diPlaza.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					
					//afficher PV PA
					printf("\nPV : %d/%d\n", diPlaza.pv,diPlaza.pvMax);
					printf("PA : %d/%d\n", diPlaza.pa,diPlaza.paMax);
					
					//Réinit Tampon def
					if(diPlaza.tamponDef == 1){
						diPlaza.tamponDef = 0;
					}
					
					//selection de l'action
					
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (40 PA)\\n");
					scanf("%d", &action);
					
					//verif action
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : tir de barrage (40 PA)\n");
						scanf("%d", &action);
					}
					
					//atq
					if(action == 1){
						printf("\nQui attaquer ?\n");
						printf("1 : chasseur\n2 : corvette\n");
						scanf("%d", &choix);
						
						//verif action
						
						while(choix!= 1 && choix!= 2){
							
							printf("cible non reconnu.\n");
							printf("1 : chasseur\n2 : corvette\n");
							scanf("%d", &choix);
							
						}
						if(choix == 1){
							chasseurA.pv = attaque(chasseurA.pv, diPlaza.atq, chasseurA.tamponDef, chasseurA.def);
							printf("\nDi Plaza attaque le chasseur.\n");
							
						}
						if(choix == 2){
							corvette.pv = attaque(corvette.pv, diPlaza.atq, corvette.tamponDef, corvette.def);
							printf("\nDi Plaza attaque la corvette.\n");
							
						}
						
						if(chasseurA.pv <= 0 && corvette.pv <= 0){
							end = 1;
						}
					}
					
					//def
					if(action == 2){
						printf("\nDi Plaza se defend.\n");
						diPlaza.tamponDef = 1;
					}
					
					//comp
					if(action == 3){
						if(diPlaza.pa >= 40){
						printf("Di Plaza lance un tir de barrage !");
						chasseurA.pv -= diPlaza.atq;
						corvette.pv -= diPlaza.atq;
						}else{
							printf("\nLes canons sont enrayes, DiPlaza ne peut pas les utiliser...\n");
						}
					}
					
				}
				
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	

				printf("\n*************************************************************************************************\n");
				
				printf("\nDE VIGNE\n");
				
				//Tour DeVigne
				if(deVigne.pv > 0 && end == 0){
					
					//recup PA
					
					if(deVigne.pa < deVigne.paMax){
						deVigne.pa += 5;
						if(deVigne.pa > deVigne.paMax){
							deVigne.pa = deVigne.paMax;
						}
						printf("\ngain de 5PA\n");
					}
					
					//afficher PV PA
					
					printf("\nPV : %d/%d\n", deVigne.pv,deVigne.pvMax);
					printf("PA : %d/%d\n", deVigne.pa,deVigne.paMax);
					
					
					
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
						printf("1 : attaquer\n2 : defendre\n3 : bandage (10 PA)\n");
						scanf("%d", &action);
					}
					
					//atq
					
					if(action == 1){
						printf("\nQui attaquer ?\n");
						printf("1 : chasseur\n2 : corvette\n");
						scanf("%d", &choix);
						
						//verif action
						
						while(choix!= 1 && choix!= 2){
							
							printf("cible non reconnu.\n");
							printf("1 : chasseur\n2 : corvette\n");
							scanf("%d", &choix);
							
						}
						if(choix == 1){
							chasseurA.pv = attaque(chasseurA.pv, deVigne.atq, chasseurA.tamponDef, chasseurA.def);
							printf("\nDe Vigne attaque le chasseur.\n");
							
						}
						if(choix == 2){
							corvette.pv = attaque(corvette.pv, deVigne.atq, corvette.tamponDef, corvette.def);
							printf("\nDe Vigne attaque la corvette.\n");
							
						}
						
						if(chasseurA.pv <= 0 && corvette.pv <= 0){
							end = 1;
						}
					}
					
					//def
					
					if(action == 2){
						printf("\nDe Vigne se defend.\n");
						deVigne.tamponDef = 1;
					}
					
					//comp
					
					if(action == 3){
						if(deVigne.pa >= 10){
							printf("\nTapez un chiffre pour choisir une des personnes suivantes :\n");
							printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
							scanf("%d", &action);
							
							while(action!= 1 && action!= 2 && action!= 3 && action!= 4){
								printf("action non reconnu.\n");
								printf("1 : Billy\n2 : Ring Of Kelly\n3 : Di Plazza\n4 : De Vigne\n");
								scanf("%d", &action);
							}
							
							
							if(action == 1){
								if(billy.pv > 0){
									printf("De Vigne pose un bandage sur Billy !");
									billy.pv += 15;
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 2){
								if(ringOfKelly.pv > 0){
									printf("De Vigne pose un bandage sur Ring Of Kelly !");
									ringOfKelly.pv += 15;
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 3){
								if(diPlaza.pv > 0){
									printf("De Vigne pose un bandage sur Di Plaza !");
									diPlaza.pv += 15;
								}else{
									printf("\nDeVigne ne peut que soigner. Pas ressuciter\n");
								}
							}
							
							if(action == 4){
								printf("De Vigne se pose un bandage !");
								deVigne.pv += 15;
							}
							deVigne.pa -= 10;
							
						}else{
							printf("Suite a une secousse, DeVigne tombe dans les escalier.");
						}
						
					}
					
				}
				
					//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				printf("\nCORVETTE\n");				
				//Tour Corvette
				if(corvette.pv > 0 && end == 0){
					
					//afficher PV PA
					printf("\nPV : %d/%d\n", corvette.pv,corvette.pvMax);
					printf("PA : %d/%d\n", corvette.pa,corvette.paMax);
					
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
						
						if(billy.aggro > 0){
							
							printf("\nLa corvette attaque Billy.\n");
							billy.pv = attaque(billy.pv, corvette.atq, billy.tamponDef, billy.def);
							
						}else{
							
							probaAttaque = ran_a_b();
							
							if( probaAttaque < 25){
								printf("\nLa corvette attaque Billy.\n");
								billy.pv = attaque(billy.pv, corvette.atq, billy.tamponDef, billy.def);
							}
							
							if( probaAttaque >=25 && probaAttaque < 50){
								printf("\nLa corvette attaque Di Plaza.\n");
								diPlaza.pv = attaque(diPlaza.pv, corvette.atq, diPlaza.tamponDef, diPlaza.def);
							}
							if( probaAttaque >=50 && probaAttaque < 75){
								printf("\nLa corvette attaque >Ring Of Kelly.\n");
								ringOfKelly.pv = attaque(ringOfKelly.pv, corvette.atq, ringOfKelly.tamponDef, ringOfKelly.def);
							}
							
							if( probaAttaque >= 75){
								printf("\nLa corvette attaque De Vigne.\n");
								deVigne.pv = attaque(deVigne.pv, corvette.atq, deVigne.tamponDef, deVigne.def);
							}
							
						}
						
						if(billy.pv <= 0 && ringOfKelly.pv <= 0 && deVigne.pv <= 0 && diPlaza.pv <= 0){
							end = 1;
						}
						
					}
					
					//rep
					
					if(action >= 90){
						printf("\nL'équipage de la corvette répare le navire !\n");
						corvette.pv += 25;
						corvette.pa -= 30;
					}
					
					//comp
					
					if(action >= 60 && action < 90){
						if(corvette.pa >= 30){
							printf(" \nCorvette lance Tir de barrage !\n");
							billy.pv -= corvette.atq;
							diPlaza.pv -= corvette.atq;
							ringOfKelly.pv -= corvette.atq;
							deVigne.pv -= corvette.atq;
							
							corvette.pa -= 30;
							
							if(billy.pv <= 0 && ringOfKelly.pv <= 0 && deVigne.pv <= 0 && diPlaza.pv <= 0){
								end = 1;
							}
						}else{
							printf("La corvette vous observe");
						}
					}
					
				}
			
			}
			
			
			if(billy.pv <= 0 && ringOfKelly.pv <= 0 && deVigne.pv <= 0 && diPlaza.pv <= 0){
				printf("vous avez perdu...");
			}
			
			
			if(chasseurA.pa <= 0 && corvette.pa <= 0){
				printf("\nVous avez avez gagne !\n");
				
				deVigne.xp += corvette.xp + chasseurA.xp;
				diPlaza.xp += corvette.xp + chasseurA.xp;
				ringOfKelly.xp += corvette.xp + chasseurA.xp;
				billy.xp += corvette.xp + chasseurA.xp;
				
				while(deVigne.xp >= deVigne.xpMax){
					deVigne.xp -= deVigne.xpMax;
					deVigne.lvl += 1;
					deVigne.xpMax += 10;
					
					deVigne.atq += 2;
					deVigne.pv += 5;
					deVigne.pa += 10;
					printf("\nDe Vigne monte de niveau.\n");
				}
				
				while(diPlaza.xp >= diPlaza.xpMax){
					diPlaza.xp -= diPlaza.xpMax;
					diPlaza.lvl += 1;
					diPlaza.xpMax += 10;
					
					diPlaza.atq += 4;
					diPlaza.pv += 5;
					diPlaza.pa += 5;
					printf("\nDi Plaza monte de niveau.\n");
				}
				
				while(ringOfKelly.xp >= ringOfKelly.xpMax){
					ringOfKelly.xp -= ringOfKelly.xpMax;
					ringOfKelly.lvl += 1;
					ringOfKelly.xpMax += 10;
					
					ringOfKelly.atq += 2;
					ringOfKelly.pv += 5;
					ringOfKelly.pa += 5;
					printf("\nRing Of Kelly monte de niveau.\n");
				}
				
				while(billy.xp >= billy.xpMax){
					billy.xp -= billy.xpMax;
					billy.lvl += 1;
					billy.xpMax += 10;
					
					billy.atq += 2;
					billy.pv += 10;
					billy.pa += 5;
					printf("\nBilly monte de niveau.\n");
				}
			}
			
		}
		
		//--------------------------------------------------------------------------------------------------------------------------------

		//continuer ?
		printf("\nVoulez vous conituner ?\n");
		printf("\n 1 : oui // 2 : non\n");
		scanf("%d", &game);
		
	}
	
	printf("Fin de la partie");
	
	return 0;
}