#ifndef JEU_DE_CARTES_HPP
#define JEU_DE_CARTES_HPP

#include "carte.hpp"
#include <string>
using namespace std;

class jeu_de_cartes {
public:
	//constructeur
	jeu_de_cartes();

	//2eme constructeur
	jeu_de_cartes(string nomj);

	//destructeur
	~jeu_de_cartes();

	bool est_vide();
	carte* retirer_carte();
	void ajouter_carte(carte *car);
	string nom();
	void melanger();
	

	//void printList();

private:
	int nb_cartes;	//nombre des cartes dans le jeu
	string nom_jeu;	// le nom du jeu
	list<carte*> jdc;	//liste des cartes du jeu
};

#endif
