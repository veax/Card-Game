#ifndef CARTE_HPP
#define CARTE_HPP

#include <iostream>
#include <list>
#include <string>

typedef unsigned char t_code;

// couleur des cartes
enum class couleur_carte : t_code { Coeur, Pique, Carreau, Trefle };
std::ostream& operator<<(std::ostream& os, const couleur_carte& couleur);
std::list<couleur_carte> creer_liste_couleurs();

// valeur des cartes
enum class valeur_carte : t_code { Dix, Valet, Dame, Roi, As };
std::ostream& operator<<(std::ostream& os, const valeur_carte& valeur);
std::list<valeur_carte> creer_liste_valeurs();

// carte définie par sa couleur, sa valeur et le nom de son jeu d'origine
class carte {
public:
  // constructeur
  carte(const couleur_carte& couleur,
	const valeur_carte& valeur,
	const std::string& nom_jeu);

  // destructeur
  ~carte();

  // accesseurs
  couleur_carte couleur() const;
  valeur_carte valeur() const;
  const std::string& nom_jeu() const;

private:
  couleur_carte couleur_;  // couleur
  valeur_carte valeur_;    // valeur
  std::string nom_jeu_;    // nom du jeu

  // protection contre la recopie
  carte& operator=(carte& car) = delete;
  carte(const carte& car) = delete;
};

// opérateur d'écriture sur un flot de sortie
std::ostream& operator<<(std::ostream& os, const carte& car);

#endif
