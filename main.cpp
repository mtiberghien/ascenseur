#include <iostream>
#include "ascenseur.hpp"
using namespace std;

short saisieEtage(short min_etage, short max_etage, bool etageDesire)
{
    short etage;
    
    do
    {
        cout << (etageDesire ? "A quel étage va la personne " : "A quel étage se trouve la personne") << "( " << min_etage << " à " << max_etage << ")? ";
        cin >> etage;
        if(etage < min_etage || etage > max_etage)
        {
            cout << "La plage saisie est invalide. Recommencez." << endl;
        }
    } while (etage < min_etage || etage > max_etage);
    
    return etage;
}

int main()
{
    cout << "Projet Ascenseur V1.0" << endl;
    cout << "Bievenue dans la simulation d'un ascenseur." << endl;
    cout << "Combien d'étages désirez-vous (4 minimum)? ";
    int nbEtages = 0;
    while(nbEtages<4)
    {
        cin >> nbEtages;
        if(nbEtages <4)
        {
            cout << "Il faut au moins 4 étages. Combien d'étages? ";
        }
    }
    Ascenseur a(nbEtages, 0);
    char choix;
    do
    {
        a.iteration();
        cout << "Voulez-vous ajouter une personne (o/n, q pour quitter)? ";
        cin >> choix;
        if(tolower(choix) == 'o')
        {
            short etage_depart = saisieEtage(a.getEtageMinimal(), a.getEtageMaximal(), false);
            short etage_desire = saisieEtage(a.getEtageMinimal(), a.getEtageMaximal(), true);
            Personne* p = new Personne(etage_desire);
            a.ajoutePersonne(p, etage_depart);
        }
    } while (tolower(choix) != 'q');

    cout << "Merci d'avoir utilisé l'application. À bientôt!!" << endl;
    
}