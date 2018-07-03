#include "bataille.hpp"
#include <string>
#include <iostream>
using namespace std;
//constructeur
bataille :: bataille(){
	nb_jeu = 0;
	nb_jo = 0;
	nb_max = 0;
	m = 0;
	cpt_nmax = 1;	//compteur de n coups
	cpt_m = 1;		//compteur de m coups
	pio = new pioche();
}

//destructeur
bataille :: ~bataille(){
	delete pio;
	nb_jeu = 0;
	nb_jo = 0;
	nb_max = 0;
	m = 0;
	cpt_nmax = 0;	//compteur de n coups
	cpt_m = 0;
	for (unsigned int i = 0; i < joueurs.size(); i++){
		delete joueurs[i];
	}
	for (unsigned int i = 0; i < jeux.size(); i++){
		delete jeux[i];
	}
}

void bataille :: ajouter_jeu(jeu_de_cartes *jdc){
	nb_jeu++;
	jeux.push_back(jdc);
}

void bataille :: ajouter_joueur(joueur *jo){
	nb_jo++;
	joueurs.push_back(jo);
}

int bataille :: nb_joueurs(){
	return nb_jo;
}

void bataille :: distribuer_cartes(){
	//creer le jeu de carte commun pour tous les jdc
	jeu_de_cartes *grand_jeu = new jeu_de_cartes("jdc1");	// on utilise 2eme constructeur pour faire jeu de cartes vide
	for (int i = 0; i < nb_jeu; i++){
		while(!jeux[i]->est_vide()){
			carte *temp = jeux[i]->retirer_carte();
			grand_jeu->ajouter_carte(temp);
		}
	}
	//melanger ce jeu de carte	
	grand_jeu->melanger();
	int nb_cartes_pioche = nb_jo + (20*nb_jeu % nb_jo);
	//mettre la partie des cartes dans une pioche
	
	for (int i = 0; i < nb_cartes_pioche; i++){
		carte *temp = grand_jeu->retirer_carte();
		pio->ajouter_carte(temp);

	}
	
	//distribuer le reste entre les joueurs
	int nb_carte_par_jo = (20*nb_jeu - nb_cartes_pioche)/nb_jo;
	for (int i = 0; i < nb_jo; i++){
      	for (int j = 0; j < nb_carte_par_jo; j++){
			carte *temp = grand_jeu->retirer_carte();
			joueurs[i]->ajouter_carte(temp); // ajouter la carte dans un tas de joueur
        	}
	}
	delete grand_jeu;
}

/*void bataille :: reconstituer_jeux(){

}*/

void bataille :: commencer_une_partie(int nmax, int m){
	nb_max = nmax;
	this->m = m;
	//reconstituer_jeux();
	distribuer_cartes();
}

bool bataille :: test_gagnant(){
	if (joueurs.size() == 1){
		return true;
	}
	return false;
}

string bataille :: gagnant(){
	return joueurs[0]->nom();	//si on a le gagnant, c`est le seul joueur dans le tableau des joueurs
}

int bataille :: test_fin_partie(){
        if (test_gagnant()){
                return 1;
        }
	  else if (cpt_nmax < nb_max){
                return 0;
        }
        return -1;
}

void bataille :: jouer_un_coup(){
	
	//--------------------------------------
	// affichage des cartes de chaque joueur
	//cout << "debut jouer un coup()" << endl;
	for (unsigned int i = 0; i < joueurs.size(); i++){
		cout << "nb cartes jo" << i+1 << ": " << joueurs[i]->nb_cartes() << endl;
		joueurs[i]->print_queue();
	}

	pio->taille();
	pio->print_pioche();
	//--------------------------------------

	joueur *joueur_max;
	carte* carte_max = NULL;
	vector<carte*> C;		// ensemble des cartes qui jouent
	vector<carte*> Cb;	// cartes qui se jouent si il y a plusieurs joueurs max
	vector<joueur*> B;	// le tableau des joueurs avec les cartes max
	int nb_jo_max = 1;	//nombre des joueurs qui s`affrontent si les deux ont les val max des cartes
	
	// test si il faut renverser la pioche:
 	if (cpt_m == m){
      	pio->renverser();   // renverser la pioche
      	cpt_m = 0;
  	}
	
	for (int i = 0; i < nb_jo; i++){    
		// test si le joueur a perdu (il n'a plus de cartes):
		if (joueurs[i]->nb_cartes() ==  0){
			joueurs.erase(joueurs.begin() + i);  // supprimer le joueur de la liste des joueurs
			nb_jo--;
			i--;
			if (test_gagnant()){
				return;
			}
			continue;
		} 
		// chaque joueur prend la carte au sommet de son tas
		// C - est l`ensemble de ces cartes
		if (carte_max == NULL){
			carte_max = joueurs[i]->carte_au_sommet();
			nb_jo_max = 1;
			joueur_max = joueurs[i];
			B.clear();	// vider le tableau des joueurs max	
			Cb.clear();	//vider tableau des cartes max
			B.push_back(joueurs[i]);	//on ajoute le joueur dans le tableau des joueurs avec les cartes max
			Cb.push_back(joueurs[i]->carte_au_sommet());	// on ajoute sa carte dans le tableau des cartes max
		}
		else if (joueurs[i]->carte_au_sommet()->valeur() > carte_max->valeur() ){
			carte_max = joueurs[i]->carte_au_sommet();	
			nb_jo_max = 1;
			joueur_max = joueurs[i];
			B.clear();	
			B.push_back(joueurs[i]);
			Cb.push_back(joueurs[i]->carte_au_sommet());
		}
		else if(joueurs[i]->carte_au_sommet()->valeur() == carte_max->valeur()){
			nb_jo_max++;
			B.push_back(joueurs[i]);
			Cb.push_back(joueurs[i]->carte_au_sommet());
		}
		C.push_back(joueurs[i]->retirer_carte());

	} // end for
	
	/*
	//affichage des cartes dans C:
	cout << "les cartes de C: " << endl;
	for (int i = 0; i< C.size(); i++){
		cout << *C[i] << endl;
	}
	cout << "---------------------"<< endl;
	*/
	//si on a seul joueur:
	if (nb_jo_max == 1){
		// remettre tous les cartes C au tas de joueur_max
		for (unsigned int i = 0; i < C.size(); i++){
			joueur_max->ajouter_carte(C[i]);
		}
	}
	//si plusieurs on a une bataille:
	else{
		// les cartes de C qui ne sont pas ds Cb sont mises en pioche
		for (unsigned int i = 0; i < C.size(); i++){
			if (Cb[0]->valeur() != C[i]->valeur()){
				pio->ajouter_carte(C[i]);
			}
		}

		//chaque joueur de B prend une seconde carte au sommet de son tas
		vector<carte*> C2;	
		for (unsigned int i = 0; i < B.size(); i++){
			// si joueur n`a plus de cartes
			if (B[i]->nb_cartes() == 0){	
				if (!pio->est_vide()){	//il prend dans la pioche si elle est pas vide
					C2.push_back(pio->retirer_carte());
				}
				else{				//sinon le joueur a perdu
					B.erase(B.begin() + i);
					i--;
					if (test_gagnant()){
						return;
					}
					continue;
				}
			}
			//sinon
			else {
				C2.push_back(B[i]->retirer_carte());
			}
		}

		/*
		//affichage des cartes dans C2:
		cout << "les cartes de C2: " << endl;
		for (int i = 0; i< C2.size(); i++){
			cout << *C2[i] << endl;
		}
		cout << "---------------------"<< endl;
		*/
		//chaque joueur de B prend une troisieme carte au sommet de son tas
		vector<carte*> C3;
		nb_jo_max = 1;
		carte_max = NULL;
		for (unsigned int i = 0; i < B.size(); i++){
			// si joueur n`a plus de cartes
			if (B[i]->nb_cartes() == 0){	
				if (!pio->est_vide()){	//il prend dans la pioche si elle est pas vide
					C3.push_back(pio->retirer_carte());
				}
				else{				//sinon le joueur a perdu
					B.erase(B.begin() + i);
					i--;
					if (test_gagnant()){
						return;
					}
					continue;
				}
			}
			//sinon
			else {
				if (carte_max == NULL){
					carte_max = B[i]->carte_au_sommet();
					joueur_max = B[i];
				}
				else if (B[i]->carte_au_sommet()->valeur() > carte_max->valeur() ){
					carte_max = B[i]->carte_au_sommet();
					nb_jo_max = 1;
					joueur_max = B[i];
				}

				else if (B[i]->carte_au_sommet()->valeur() == carte_max->valeur()){
					nb_jo_max++;
				}
				C3.push_back(B[i]->retirer_carte());
			}
		}//end for

		/*
		//affichage des cartes dans C3:
		cout << "les cartes de C3: " << endl;
		for (int i = 0; i< C3.size(); i++){
			cout << *C3[i] << endl;
		}
		cout << "---------------------"<< endl;
		*/

		//si on a un seul joueur avec la carte max
		if (nb_jo_max == 1){
			//C3.size() == C2.size() == Cb.size()
			for (unsigned int i = 0; i < C3.size(); i++){
				joueur_max->ajouter_carte(C3[i]);
				joueur_max->ajouter_carte(C2[i]);
				joueur_max->ajouter_carte(Cb[i]);
			}
		}
		//sinon on remet tous les cartes dans la pioche
		else {
			//C3.size() == C2.size() == Cb.size()
			for (unsigned int i = 0; i < C3.size(); i++){
				pio->ajouter_carte(C3[i]);
				pio->ajouter_carte(C2[i]);
				pio->ajouter_carte(Cb[i]);
			}
		}
	// vider C2, C3
	C2.clear();
	C3.clear();
	}//end else - branche bataille
	
	cpt_nmax++;		//on incremente les compteurs
  	cpt_m++;
	//vider C
	C.clear();
	//vider Cb
	Cb.clear();
	//vider B
	B.clear();

	/*
	//controle des compteurs
	cout << "cpt_nmax: " << cpt_nmax << endl;
	cout << "cpt_m: " << cpt_m << endl;
	*/
}




