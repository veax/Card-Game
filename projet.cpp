#include <iostream>
#include "carte.hpp"
#include "jeu_de_cartes.hpp"
#include "joueur.hpp"
#include "pioche.hpp"
#include "bataille.hpp"
#include <string>
using namespace std;

int main(void)
{	
	int nb_joueurs, nb_jeu_de_cartes, nmax, m; 	
	string nom_jo;

	do{
		cout << "entrer le nb_joueurs (minimum 2): " << endl;
		cin >> nb_joueurs;
	} while (nb_joueurs < 2);
	do{
		cout << "entrer le nb_jeu_de_cartes (minimum 1): " << endl;
		cin >> nb_jeu_de_cartes;
	} while (nb_jeu_de_cartes < 1);
	do{
		cout << "entrer le nmax (plus grand que 1)" << endl;
		cin >> nmax;
	} while(nmax < 2);
	do{
		cout << "entrer m (plus grand que 1)" << endl;
		cin >> m;
	} while(m < 2);
	
	bataille *b1 = new bataille();
	for (int i = 0; i < nb_joueurs; i++){
		cout << "Entrez le nom de joueur:" << endl;
		cin >> nom_jo;
		joueur *jo = new joueur(nom_jo);
		b1->ajouter_joueur(jo);
	}
	for (int i = 0; i < nb_jeu_de_cartes; i++){
		jeu_de_cartes *jeu = new jeu_de_cartes();
		b1->ajouter_jeu(jeu);
	}
	
	b1->commencer_une_partie(nmax,m);
	while (b1->test_fin_partie() == 0){
		b1->jouer_un_coup();
	}

	//final:
	
	if (b1->test_fin_partie() == -1){
        cout << "nb de coups max atteint" << endl;
	}
	else {
		  cout << "gagnant: " << b1->gagnant() << endl;
	}

	//desallocation
	delete b1;
	//desallocation des joueurs et des jeux est dans le destructeur de la bataille

  return 0;
}
