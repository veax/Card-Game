#ifndef BATAILLE_HPP
#define BATAILLE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "carte.hpp"
#include "jeu_de_cartes.hpp" 
#include "joueur.hpp" 
#include "pioche.hpp" 

class bataille {
public:
	//constructeur
	bataille();
	// destructeur
	~bataille();

	void ajouter_jeu(jeu_de_cartes *jdc);
	void ajouter_joueur(joueur *jo);
	int nb_joueurs();
	void distribuer_cartes();
	void reconstituer_jeux();
	void commencer_une_partie(int nmax, int m);
	void jouer_un_coup();
	int test_fin_partie();
	bool test_gagnant();
	string gagnant();

private:
	int nb_max; // nombre des coups maximales
	int cpt_nmax; //compteur de n coups
	int m;	// on renverse la pioche tous les m coups
	int cpt_m;	//compteur de m coups
	int nb_jo;	// nb des joueurs
	int nb_jeu;		// nb des jeu
	vector<joueur*> joueurs;	// le tableau des joueurs
	vector<jeu_de_cartes*> jeux;	//le tableau des jeux des cartes
	pioche *pio;	//une pioche
};

#endif
