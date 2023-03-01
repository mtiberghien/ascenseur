#include "ascenseur.hpp"

void Ascenseur::setEtat(EtatAscenseur* etat)
{
    if(this->etat != nullptr)
    {
        delete this->etat;
    }
    this->etat = etat;
}

Mouvements Ascenseur::bouge()
{
    Mouvements m;
    if(this->etat != nullptr)
    {
        m = this->etat->bouge();      
    }

    return m;
}

void Ascenseur::affiche()
{
    cout << "L'ascenseur est à l'étage: " << this->etage_actuel << endl;
    if(this->etat != nullptr)
    {
        this->etat->affiche();
    }
    int nbPassagers = this->get_nbPersonnesAscenseur();
    cout << "Avec " << nbPassagers << " passager" << (nbPassagers>1?"s":"") << endl;

}

void Ascenseur::ajoutePersonne(Personne* p)
{
    this->passagers.push_back(p);
}

void Ascenseur::iteration()
{
    cout << "\033[2J\033[1;1H";
    Mouvements m = this->bouge();
    this->affiche();
    m.affiche();
}

bool Ascenseur::AMontants()
{
    for(Personne* p: this->passagers)
    {
        if(p->getEtageAppel() > this->etage_actuel)
        {
            return true;
        }
    }

    return false;
}

bool Ascenseur::ADescendants()
{
    for(Personne* p: this->passagers)
    {
        if(p->getEtageAppel() < this->etage_actuel)
        {
            return true;
        }
    }

    return false;
}

int EtatAscenseur::gestionDescenteAscenseur()
{
    vector<Personne*>::iterator it;
    int nombre = 0;
    int i=0;
    for(auto it = this->ascenseur->passagers.begin(); it != this->ascenseur->passagers.end();)
    {
        Personne* p = *it;
        if(p->getEstDansAscenseur() && p->getEtageDesire() == this->ascenseur->etage_actuel)
        {
            auto new_it = next(it);
            nombre++;
            delete p;
            this->ascenseur->passagers.erase(it);
            it = new_it;
        }
        else
        {
            it++;
        }
    }

    return nombre;
}

void EtatAscenseur::gestionMonteeAscenseur(Mouvements& mouvements)
{
    mouvements.nbMontees = 0;
    mouvements.nbBloquees = 0;
    int nbAscenseur = this->ascenseur->get_nbPersonnesAscenseur();
    for(Personne* p : this->ascenseur->passagers)
    {
        if(!p->getEstDansAscenseur() && p->getEtageInitial() == this->ascenseur->etage_actuel)
        {
            if(nbAscenseur < MAX_PERSONNES)
            {
                p->setEstDansAscenseur(true);
                mouvements.nbMontees++;
                nbAscenseur++;
            }
            else
            {
                mouvements.nbBloquees ++;
            }
        }
    }
}

Mouvements EtatImmobile::bouge()
{
    Mouvements m;
    m.nbDescentes = 0;
    this->gestionMonteeAscenseur(m);
    bool AMontants = this->ascenseur->AMontants();
    if(AMontants)
    {
        this->ascenseur->setEtat(new EtatMontant(this->ascenseur));
    }
    else
    {
        bool ADescendants = this->ascenseur->ADescendants();
        if(ADescendants)
        {
            this->ascenseur->setEtat(new EtatDescendant(this->ascenseur));
        }
    }
    return m;
}

void EtatImmobile::affiche()
{
    cout << "À l'arrêt" << endl;
}

Mouvements EtatMontant::bouge()
{
    this->ascenseur->etage_actuel++;
    Mouvements m;
    m.nbDescentes = this->gestionDescenteAscenseur();
    this->gestionMonteeAscenseur(m);
    bool aMontants = this->ascenseur->AMontants();
    if(!aMontants)
    {
        this->ascenseur->setEtat(this->ascenseur->passagers.size() > 0? (EtatAscenseur*) new EtatDescendant(this->ascenseur) : (EtatAscenseur*) new EtatImmobile(this->ascenseur));
    }

    return m;

}

void EtatMontant::affiche()
{
    cout << "En montée" << endl;
}

Mouvements EtatDescendant::bouge()
{
    this->ascenseur->etage_actuel--;
    Mouvements m;
    m.nbDescentes = this->gestionDescenteAscenseur();
    this->gestionMonteeAscenseur(m);
    bool aDescendants = this->ascenseur->ADescendants();
    if(!aDescendants)
    {
        this->ascenseur->setEtat(this->ascenseur->passagers.size() > 0? (EtatAscenseur*) new EtatMontant(this->ascenseur) : (EtatAscenseur*) new EtatImmobile(this->ascenseur));
    }

    return m;  
}

void EtatDescendant::affiche()
{
    cout << "En descente" << endl;
}



