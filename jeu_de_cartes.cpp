#include "jeu_de_cartes.hpp"
using namespace std;

//constructeur
jeu_de_cartes :: jeu_de_cartes(){
	  list<couleur_carte> lc = creer_liste_couleurs();
	  list<valeur_carte> lv = creer_liste_valeurs();

	  // itc : itérateur de parcours de la liste des couleurs
	  auto itc = lc.cbegin();
	  while (itc != lc.cend())
	  {
	    // itv : itérateur de parcours de la liste des valeurs
	    auto itv = lv.cbegin();
	    while (itv != lv.cend())
	    {
		carte *car = new carte(*itc,*itv,"");
		jdc.push_back(car);
		++itv;
	    }
	    ++itc;
	  }
	nb_cartes = 20;
}

//2eme constructeur
jeu_de_cartes :: jeu_de_cartes(string nomj){
	nb_cartes = 0;
	nom_jeu = nomj; 
}


//destructeur
jeu_de_cartes :: ~jeu_de_cartes(){
	nb_cartes = 0;
	
	for (auto v : jdc){	//desallocation des pointeurs vers les cartes
		delete v;
	}
	
}


bool jeu_de_cartes :: est_vide(){
	if (nb_cartes == 0){
		return true;
	}
	return false;
}

carte* jeu_de_cartes :: retirer_carte(){
	carte *temp = jdc.front();	// renvoie premiere carte d`une liste
	jdc.pop_front();		// on supprime premiere carte
	nb_cartes--;		//ajouter assert si jdc.size() == 0
	return temp;
}

void jeu_de_cartes :: ajouter_carte(carte *car){
	jdc.push_back(car);
	nb_cartes++;
}

string jeu_de_cartes :: nom(){
	return nom_jeu;
}

void jeu_de_cartes :: melanger(){
	list<carte*> melange;
	list<carte*>::iterator it = jdc.begin();
	int randn;
	srand (time(NULL));
	while (!jdc.empty()){
		if (jdc.size() > 1){
			randn = rand() % jdc.size();	//retourne nb aleatoire entre 0 et taille - 1
			advance(it, randn);
			melange.push_back(*it);
			it = jdc.erase(it);	//on supprime val aleatoire d`une liste
			it = jdc.begin();
		}
		else {
			melange.push_back(*it);
			it = jdc.erase(it);
		}
		
	}
	jdc = melange;
	melange.clear();	//supprimer tous les valeurs de la liste melange
}

/*
void jeu_de_cartes :: printList(){
	cout << "-------------------"<< endl;
	list<carte*>::iterator it;
	for (it = jdc.begin(); it != jdc.end(); it++){
		cout << *it << endl;
	}
	cout << "-------------------"<< endl;
}
*/


