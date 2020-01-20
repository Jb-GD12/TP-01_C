#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main (){
	//Variable
		
		//Int
		
			//Player
				int lifePtPlayer;
				int manaPtPlayer;
				int tamponDefP;
				int compteurPsnP;
				int action;
			
			//Mob
				int lifePtMob;
				int manaPtMob;
				int tamponDefM;
				int compteurPsnM;
				int probaActM;
			
			//commun
				int tour;
				int boolVictoire;
				int probaCtq;
				int ctqDommage;
				int dommage;
		
		
		
		//Fonction random
			srand = time();
			int a = 0;
			int b = 100;
			int rand_a_b(int a, int b){
				return rand()%(b-a) +a;
			}
		
	//Début
		boolVictoire = 0;
		
		tamponDefP = 0;
		tamponDefM = 0;
		
		compteurPsnP = 0;
		compteurPsnM = 0;
		
		lifePtMob = 100;
		lifePtPlayer = 100;
		
		manaPtMob = 100;
		manaPtPlayer = 100; 
		
		tour = 0;
		
		while(boolVictoire == 0){
			
			ctqDommage = 0;
			
			tour += 1;
			tour = tour % 2;
			
			if(tour == 1){
				printf("A votre tour.\n");
				
				//gain de 1PM/tour
				if(manaPtPlayer < 100){
					manaPtPlayer += 1;
					printf("\ngain de 1PM\n");
				}
				
				//vérification de statut du joueur et, s'il est empoisonné, signalement d'une perte de point de vie.
				if(compteurPsnP > 0){
					compteurPsnP -= 1;
					lifePtPlayer -= 8;
					printf("\nVous etes empoisonne.\n");
					printf("Vous perdez 8 PV\n");
					
					if(lifePtPlayer <= 0){
						boolVictoire = 1;
						printf("\nVous sombrez dans les ténèbres, vous avez perdu...\n");
					}
				}
				
				if(tamponDefP == 1){
					tamponDefP = 0;
				}
				
				//Afficher les PV et PM du joueur
				printf("\nPV : %d\n", lifePtPlayer);
				printf("PM : %d\n", manaPtPlayer);
				
				//Affihage des possibilité en fonction des PM du joueur
				if(manaPtPlayer > 4){
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n3 : sort\n");
					scanf("%d", &action);
					
					while(action!= 1 && action!= 2 && action!= 3){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n3 : sort\n");
						scanf("%d", &action);
					}
				}else{
					//si le joueur ne peut pas lancer de sort cra PM trop bas
					printf("\nTapez un chiffre pour choisir une des actions suivantes :\n");
					printf("1 : attaquer\n2 : defendre\n");
					scanf("%d", &action);
					
					while(action!= 1 && action!= 2){
						printf("action non reconnu.\n");
						printf("1 : attaquer\n2 : defendre\n");
						scanf("%d", &action);
					}
				}
				
				//fonction Atq
				if(action == 1){
					//proba de critique 1/5 (à changer ?)
					probaCtq = rand_a_b(a, b);
					if(probaCtq < 20){
						ctqDommage = 5;
					}
					//Dégat donné en fonction du statut def du mob + ctq si il y a.
					if(tamponDefM == 1){
						lifePtMob -= (10 + ctqDommage) / 4;
						dommage = (10 + ctqDommage) / 4;
						printf("le slime prend %d de degat\n", dommage);
						tamponDefM = 0;
					}else{
						lifePtMob -= (10 + ctqDommage);
						dommage = (10 + ctqDommage);
						printf("le slime prend %d de degat\n", dommage);
					}
					if(lifePtMob <= 0){
						boolVictoire = 1;
						printf("\nBravo ! Vous avez gagne !\n");
					}
				}
				
				//Fonction Def
				if(action == 2){
					tamponDefP = 1;
					printf("Vous vous defendez.\n");
				}
				
				//Fonction Spell
				if(action == 3){
					
					//ajustement des sorts jetable en fonction des PM.
					if(manaPtPlayer >= 10){
						printf("Tapez un chiffre pour choisir un des sorts suivants :\n");
						printf("1 : soin PM : 5\n2 : poison PM : 10\n3 : antidote PM : 5\n");
						scanf("%d", &action);
						
						while(action!= 1 && action!= 2 && action!= 3){
							printf("sort non reconnu.\n");
							printf("1 : soin PM : 5\n2 : poison PM : 10\n3 : antidote PM : 5\n");
							scanf("%d", &action);
						}
					}else{
						printf("Tapez un chiffre pour choisir un des sorts suivants :\n");
						printf("1 : soin PM : 5\n3 : antidote PM : 5\n");
						scanf("%d", action);
						
						while(action!='s' && action!='a'){
							printf("\nsort non reconnu.\n");
							printf("1 : soin\n3 : antidote\n");
							scanf("%d", &action);
						}
					}
					
					//Sous-fonction heal
					if(action == 1){
						printf("Vous lancez Soin !\n");
						lifePtPlayer += 15;
						//vérification pour que les pts de vie ne dépassent pas 100.
						if(lifePtPlayer > 100){
							lifePtPlayer = 100;
						}
						
						//probabilté de soigné le statut du joueur s'il est empoisonné.
						probaCtq = rand_a_b(a, b);
						if(probaCtq < 5 && compteurPsnP > 0){
							compteurPsnP = 0;
							printf("Sort critique !\nVous n'etes plus empoisonne !\n");
						}
						printf("Vous gagnez 15PV");
						manaPtPlayer -= 5;
					}
					
					//Sous-fonction psn
					if(action == 2){
						//vérification du statut du mob. s'il est déjà empoisonné, le sort ne fonctionne pas.
						if(compteurPsnM == 0){
							printf("\nVous lancez Poison !\n");
							compteurPsnM = 4;
							printf("Le slime est empoisonne !\n");
							//Cout du sort de Poison : 10PM.
							manaPtPlayer -= 10;
						}else{
							printf("Le slime est deja empoisonne...\n");
						}
						
					}
					
					//Sous fonction Antidote
					if(action == 3){
						printf("\nVous lancez Antidote !\n");
						if(compteurPsnP > 0){
							compteurPsnP = 0;
							printf("Vous n'etes plus empoisonne");
							manaPtPlayer -= 5;
						}else{
							printf("\nLe sort n'a aucun effet...\n");
						}
					}
					
				}
				
				
			}
			else{
				printf("tour du slime.\n");
				
				if(tamponDefM == 1){
					tamponDefM = 0;
				}
				
				//gain de 1PM/tour
				if(manaPtMob < 100){
					manaPtMob += 1;
					printf("gain de 1PM\n");
				}
				
				//vérification de statut du mob et, s'il est empoisonné, signalement d'une perte de point de vie.
				if(compteurPsnM > 0){
					compteurPsnM -= 1;
					lifePtMob -= 8;
					printf("\nLe slime est empoisonne.\n");
					printf("Il perd 8 PV\n");
					if(lifePtMob <= 0){
						boolVictoire = 1;
						printf("\nLe slime meurt d'empoisonnement. Vous avez gagne !\n");
					}
				}
				
				probaActM = rand_a_b(a, b);
				
				//fonction atq
				if(probaActM < 59){
					
					printf("\nLe slime attaque !\n");
					
					//atq critique. proba 1/10
					probaCtq = rand_a_b(a, b);
					if(probaCtq <= 10){
						ctqDommage = 5;
						printf("Attaque critique !\n");
					}
					
					//vérifictaion de l'état défense du joueur.
					if(tamponDefP == 1){
						lifePtPlayer -= (10 + ctqDommage)/4;
						dommage = (10 + ctqDommage)/4;
						printf("Vous prenez %d de degat.\n", dommage);
						tamponDefP = 0;
					}	
					else{
						lifePtPlayer -= (10 + ctqDommage);
						dommage = (10 + ctqDommage);
						printf("Vous prenez %d de degat.\n", dommage);
					}
					if(lifePtPlayer <= 0){
						boolVictoire = 1;
						printf("\nMince... Vous avez perdu...\n");
					}
				}
				
				//Fontion def
				if(60 < probaActM && probaActM < 85){
					tamponDefM = 1;
					printf("Le slime se defend\n");
				}
				
				//Fonction spell
				if(probaActM > 85){
					
					probaActM = rand_a_b(0, 100);
					
					//Sous-fonction heal
					if(probaActM < 85){
						if(manaPtMob >= 5){
							
							//vérification pour que les pts de vie ne dépassent pas 100.
							lifePtMob += 10;
							if(lifePtMob > 100){
								lifePtMob = 100;
							}
							printf("Le slime lance un sort de soin\n");
							
							//probabilté de soigné le statut du mob s'il est empoisonné.
							probaCtq = rand_a_b(0,100);
							if(probaCtq < 5 && compteurPsnM > 0){
								compteurPsnM = 0;
								printf("Sort critique !\nLe slime n'est plus empoisonne !\n");
							}
							
							//Cout du sort de soin, 5PM.
							manaPtMob -= 5;
						}
						else{
							printf("\nLe slime vous observe.\n");
						}
					}
					//Sort poison ou antidote.
					else{
						//vérification du nb de mana 
						if(manaPtMob >= 15){
							//Sort poison.
							if(compteurPsnP = 0){
								printf("\nLe slime lance Poison !\n");
								if(compteurPsnP = 0){
									
									compteurPsnP = 6;
									printf("Vous etes empoisonne !\n");
									
									//Cout du sort de Poison : 10PM.
									manaPtMob -= 15;
								}
								else{
									printf("Vous etes deja empoisonee...\n");
								}
							}
							//sort Antidote.
							else{
								if(compteurPsnM > 0){
									compteurPsnM = 0;
									manaPtMob -= 5;
									printf("\nLe slime lance Antidote !\nLe slime n'est plus empoisonne.\n");
								}else{
									printf("\nLe slime vous observe.\n");
								}
							}
						}else{
							printf("\nLe slime vous observe.\n");
						}
						
					}
					
				}
				
			}
			
			printf("\n------------------------------------------------------\n");
			
		}
		
		printf("\nFin du jeu\n");
		
}	