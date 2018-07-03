#include "joueur.hpp"
using namespace std;

//constructeur
joueur :: joueur(string nom_jo){
	this->nom_jo = nom_jo;
	nbc = 0;
}

//desctructeur
joueur :: ~joueur(){
	nbc = 0;
}

int joueur :: nb_cartes(){
	return nbc;
}

string joueur :: nom(){
	return nom_jo;
}

carte* joueur :: carte_au_sommet(){
	return tas.front();
}

carte* joueur :: retirer_carte(){
	carte *temp =  tas.front();
	tas.pop();
	nbc--;	
	return temp;
}

void joueur :: ajouter_carte(carte *car){
	tas.push(car);
	nbc++;
}

// affichage au terminal
void joueur :: print_queue(){
	queue<carte*> temp;
	cout << "-------------------" << endl;
	while(!tas.empty()){
		cout << *(tas.front()) << endl;
		temp.push(tas.front());
		tas.pop();
	}
	while(!temp.empty()){
		tas.push(temp.front());
		temp.pop();
	}
	cout << "-------------------" << endl;
}




