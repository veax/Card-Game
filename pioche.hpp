#ifndef PIOCHE_HPP
#define PIOCHE_HPP

#include "carte.hpp"
#include <string>
#include <stack>
using namespace std;

class pioche {
public:

	//constructeur
	pioche();
	//destructeur
	~pioche();
	bool est_vide();
	void ajouter_carte(carte *car);
	carte* retirer_carte();
	void renverser();

	
	void taille();
	void print_pioche();
private:
	int nbc;
	//sd: pile (stack):
	stack<carte*> pioche_;
};

#endif
