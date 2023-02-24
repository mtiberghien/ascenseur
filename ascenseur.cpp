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
    cout << "Avec " << this->passagers.size() << " passager" << (this->passagers.size()>1?"s":"") << endl;

}

void Ascenseur::ajoutePersonne(Personne* p, short etage)
{
    int index_etage = etage - this->etage_minimal;
    if(index_etage >=0 && index_etage < this->nombre_etages)
    {
        this->etages[index_etage]->ajoutePersonne(p);
        this->demande_immobile = etage;
    }
}

void Ascenseur::iteration()
{
    cout << "\033[2J\033[1;1H";
    Mouvements m = this->bouge();
    this->affiche();
    m.affiche();
}

Etage* Ascenseur::getEtage(short etage)
{
    return this->etages[this->etage_actuel - this->etage_minimal];
}

bool Ascenseur::AMontants()
{
    for(Personne* p: this->passagers)
    {
        if(p->getEtageDesire() > this->etage_actuel)
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
        if(p->getEtageDesire() < this->etage_actuel)
        {
            return true;
        }
    }

    return false;
}

bool Ascenseur::AAppelsMontants()
{
    for(int i = this->etage_actuel - this->etage_minimal + 1; i < this->etages.size(); i++)
    {
        if(this->etages[i]->comptePersonnes() > 0)
        {
            return true;
        }
    }

    return false;
}

bool Ascenseur::AAppelsDescendants()
{
    for(int i = this->etage_actuel - this->etage_minimal - 1; i >=0; i--)
    {
        if(this->etages[i]->comptePersonnes() > 0)
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
    vector<Personne*>::iterator begin = this->ascenseur->passagers.begin();
    vector<Personne*>::iterator end = this->ascenseur->passagers.end();
    for(it = begin; it != end; it++)
    {
        if((*it)->getEtageDesire() == this->ascenseur->etage_actuel)
        {
            nombre++;
            this->ascenseur->passagers.erase(it);
        }
    }
    return nombre;
}

int EtatAscenseur::gestionMonteeAscenseur()
{
    int nombre = 0;
    Etage* etage = this->ascenseur->getEtage(this->ascenseur->etage_actuel);
    vector<Personne*>::iterator it;
    vector<Personne*>::iterator begin = etage->getPersonnesBegin();
    vector<Personne*>::iterator end = etage->getPersonnesEnd();
    for(it = begin; it != end; it++)
    {
        if(this->ascenseur->passagers.size() < MAX_PERSONNES)
        {
            this->ascenseur->passagers.push_back(*it);
            etage->removePersonne(it);
            nombre ++;
        }
        else
        {
            break;
        }
    }

    return nombre;
}

Mouvements EtatImmobile::bouge()
{
    Mouvements m;
    m.nbDescentes = 0;
    m.nbMontees = this->gestionMonteeAscenseur();
    m.nbBloquees = this->ascenseur->getEtage(this->ascenseur->etage_actuel)->comptePersonnes();
    if(this->ascenseur->demande_immobile != this->ascenseur->etage_minimal - 1 && this->ascenseur->demande_immobile != this->ascenseur->etage_actuel)
    {
        this->ascenseur->setEtat(this->ascenseur->demande_immobile > this->ascenseur->etage_actuel ? (EtatAscenseur*) new EtatMontant(this->ascenseur) : (EtatAscenseur*) new EtatDescendant(this->ascenseur));
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
    m.nbMontees = this->gestionMonteeAscenseur();
    m.nbBloquees = this->ascenseur->getEtage(this->ascenseur->etage_actuel)->comptePersonnes();
    bool aMontants = this->ascenseur->AMontants() || this->ascenseur->AAppelsMontants();
    if(!aMontants)
    {
        bool aDescendants = this->ascenseur->ADescendants() || this->ascenseur->AAppelsDescendants();
        if(!aDescendants)
        {
            this->ascenseur->demande_immobile = this->ascenseur->etage_minimal - 1;
        }
        this->ascenseur->setEtat(aDescendants > 0? (EtatAscenseur*) new EtatDescendant(this->ascenseur) : (EtatAscenseur*) new EtatImmobile(this->ascenseur));
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
    m.nbMontees = this->gestionMonteeAscenseur();
    m.nbBloquees = this->ascenseur->getEtage(this->ascenseur->etage_actuel)->comptePersonnes();
    bool aDescendants = this->ascenseur->ADescendants() || this->ascenseur->AAppelsDescendants();
    if(!aDescendants)
    {
        bool aMontants = this->ascenseur->AMontants() || this->ascenseur->AAppelsMontants();
        if(!aMontants)
        {
            this->ascenseur->demande_immobile = this->ascenseur->etage_minimal - 1;
        }
        this->ascenseur->setEtat(aMontants > 0? (EtatAscenseur*) new EtatMontant(this->ascenseur) : (EtatAscenseur*) new EtatImmobile(this->ascenseur));
    }

    return m;  
}

void EtatDescendant::affiche()
{
    cout << "En descente" << endl;
}


