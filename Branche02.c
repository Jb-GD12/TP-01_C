#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Schéma des différentes fonctionnalités du rendu final

// Fonction d'attaque

int attaque (pv, atq, def){
	if (tamponDef = 1){
		pv -= atqJoueur/defEnnemi;
	}else{
		pv -= atqjoueur;
		
	}
}

// Fonction gain xp

int gainExp ( xpJoueur, xpMonstre, xpMax, lvl, atq, pvMax,paMax){
	xpJoueur += xpMonstre;
	while(xpJoueur >= xpMax){
		xpJoueur -= xpMax;
		lvl += 1;
		xpMax += 10;
		
		atq += 2;
		pvMax += 5;
		paMax += 5;
		
		
	}
}

