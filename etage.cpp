#include "etage.hpp"

void Etage::ajoutePersonne(Personne * p)
{
    this->personnes.push_back(p);
}

void Etage::removePersonne(vector<Personne*>::iterator it)
{
    this->personnes.erase(it);
}