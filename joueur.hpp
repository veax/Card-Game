#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include "carte.hpp"
#include <string>
#include <queue>
using namespace std;

class joueur {
public:
	//constructeur
	joueur(string nom_jo);
	//desctructeur
	~joueur();

	int nb_cartes();
	string nom();
	carte* carte_au_sommet();
	carte* retirer_carte();
	void ajouter_carte(carte *car);
	void print_queue();
private:
	string nom_jo;	// nom de joueur
	int nbc;	//nb de cartes dans le tas de joueur
	// sd: file (queue):
	queue<carte*> tas;
};

#endif
