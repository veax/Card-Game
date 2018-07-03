#include "carte.hpp"

//////////////////////////////////////////////////////////////////////
static std::string
nom_couleur_carte[] = { "coeur", "piq", "car", "tref" };

std::ostream& operator<<(std::ostream& os, const couleur_carte& couleur)
{
  os << nom_couleur_carte[(t_code)couleur];
  return os;
}

std::list<couleur_carte> creer_liste_couleurs()
{
  std::list<couleur_carte> liste;
  liste.push_back(couleur_carte::Coeur);
  liste.push_back(couleur_carte::Pique);
  liste.push_back(couleur_carte::Carreau);
  liste.push_back(couleur_carte::Trefle);
  return liste;
}

//////////////////////////////////////////////////////////////////////
static std::string
nom_valeur_carte[] = { "10", "V", "D", "R", "A" };

std::ostream& operator<<(std::ostream& os, const valeur_carte& valeur)
{
  os << nom_valeur_carte[(t_code)valeur];
  return os;
}

std::list<valeur_carte> creer_liste_valeurs()
{
  std::list<valeur_carte> liste;
  liste.push_back(valeur_carte::Dix);
  liste.push_back(valeur_carte::Valet);
  liste.push_back(valeur_carte::Dame);
  liste.push_back(valeur_carte::Roi);
  liste.push_back(valeur_carte::As);
  return liste;
}

//////////////////////////////////////////////////////////////////////
carte::carte(const couleur_carte& couleur,
	     const valeur_carte& valeur,
	     const std::string& nom_jeu):
  couleur_(couleur),
  valeur_(valeur),
  nom_jeu_(nom_jeu)
{}

carte::~carte()
{}

couleur_carte carte::couleur() const
{
  return couleur_;
}

valeur_carte carte::valeur() const
{
  return valeur_;
}

const std::string& carte::nom_jeu() const
{
  return nom_jeu_;
}

std::ostream& operator<<(std::ostream& os, const carte& car)
{
  if (car.nom_jeu() != "")
    os << car.nom_jeu() << ".";
  os << car.valeur() << "." << car.couleur();
  return os;
}
