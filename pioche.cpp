#include "pioche.hpp"
using namespace std;
//constructeur

pioche :: pioche(){
	nbc = 0;
}

//desctructeur
pioche :: ~pioche(){
	nbc = 0;
}

bool pioche :: est_vide(){
	if (nbc == 0){
		return true;
	}
	return false;
}

void pioche :: ajouter_carte(carte *car){
	pioche_.push(car);
	nbc++;
}

carte* pioche :: retirer_carte(){
	carte *temp =  pioche_.top();
	pioche_.pop();
	nbc--;	
	return temp;
}

void pioche :: renverser(){
	stack<carte*> temp;
	while(!pioche_.empty()){
		temp.push(pioche_.top());
		pioche_.pop();
	}
	pioche_ = temp;
}




void pioche :: taille(){
	stack<carte*> temp = pioche_;
	int i = 0;
	while(!temp.empty()){
		temp.pop();
		i++;
	}
	cout << "taille pioche: " << i << endl;
}


void pioche :: print_pioche(){
	stack<carte*> temp = pioche_;
	cout << "------------pioche: ------------" << endl;
	while(!temp.empty()){
		cout << *temp.top() << endl;
		temp.pop();
	}
	cout << "-------------------------------" << endl;
}

