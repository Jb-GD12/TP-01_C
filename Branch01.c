#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct GenaratePjPnj{
	int pv;
	int pm;
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

int main(){
	
	
	//Equipage
	
	generate deVigne = {100, 100, 5, 2, 0,10, 1, 0,0, 0};
	generate diPlaza = {100, 100, 20, 3, 0,10, 1, 0,0, 0};
	generate Billy = {100, 100, 10, 4, 0,10, 1, 0,0, 0};
	generate RingOfKelly = {100, 100, 15, 3, 0,10, 1, 0,0, 0};
	
	//FIGHT
	
	
	
	return 0;
}