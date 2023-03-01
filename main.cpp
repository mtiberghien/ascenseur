#include <iostream>
#include "ascenseur.hpp"
using namespace std;

short saisieEtage(bool etageDesire)
{
    short etage;
    
    cout << (etageDesire ? "A quel étage va la personne " : "A quel étage se trouve la personne") << "? ";
    cin >> etage;
    
    return etage;
}

int main()
{
    cout << "Projet Ascenseur V1.0" << endl;
    cout << "Bievenue dans la simulation d'un ascenseur." << endl;
    Ascenseur a;
    char choix;
    do
    {
        a.iteration();
        cout << "Voulez-vous ajouter une personne (o/n, q pour quitter)? ";
        cin >> choix;
        if(tolower(choix) == 'o')
        {
            short etage_depart = saisieEtage(false);
            short etage_desire = saisieEtage(true);
            Personne* p = new Personne(etage_depart, etage_desire);
            a.ajoutePersonne(p);
        }
    } while (tolower(choix) != 'q');

    cout << "Merci d'avoir utilisé l'application. À bientôt!!" << endl;
    
}