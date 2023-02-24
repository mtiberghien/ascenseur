#pragma once

/**
 * @file ascenseur.hpp
 * @author Mathias Tiberghien
 * @brief Represénte l'ascensceur et ses différents états
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "commons.hpp"
#include "personne.hpp"
#include "etage.hpp"

// Nombre maximums de passagers dans l'ascenseur
#define MAX_PERSONNES 8


class Ascenseur;

struct Mouvements
{
    Mouvements():nbDescentes(0), nbMontees(0), nbBloquees(0){}
    ~Mouvements(){}
    int nbDescentes;
    int nbMontees;
    int nbBloquees;
    void affiche()
    {
        if(this->nbDescentes > 0)
        {
            cout << this->nbDescentes << (this->nbDescentes > 1 ?" personnes sont descendues" : " personne est descendue") << endl;
        }
        if(this->nbMontees > 0)
        {
            cout << this->nbMontees << (this->nbMontees > 1 ? " personnes sont montées" : " personne est montée") << endl;
        }
        if(this->nbBloquees > 0)
        {
            cout << "L'ascenseur est plein. " << this->nbBloquees << (this->nbBloquees >1 ? "personnes sont restées à quai":"personne est restée à quai") << endl;
        }
        
    }
};

/// @brief Classe abstraite représentant l'état de l'ascenseur
class EtatAscenseur
{
    public:
        EtatAscenseur(Ascenseur* ascenseur){this->ascenseur = ascenseur;}
        /// @brief Déplace l'ascenseur et met à jour l'état de celui-ci
        /// @return La structure dédcrivant les mouvements effectués pendant l'itération
        virtual Mouvements bouge() = 0;
        /// @brief Affiche dans la console les informations relatives à l'état de l'ascenseur
        virtual void affiche() = 0;
        /// @brief Gère les descentes à un étage
        /// @return Le nombre de personnes descendues
        int gestionDescenteAscenseur();
        /// @brief Gère les montées à un étage
        /// @return Le nombre de personnes montées
        int gestionMonteeAscenseur();
    protected:
        /// @brief Le contexte de l'état
        Ascenseur* ascenseur;
};

/// @brief Décrit l'état immobile de l'ascenseur
class EtatImmobile: public EtatAscenseur
{
    public:
        EtatImmobile(Ascenseur* ascenseur): EtatAscenseur(ascenseur){};
        ~EtatImmobile(){}
        Mouvements bouge() override;
        void affiche() override;
};

/// @brief Décrit l'état de l'ascenseur quand il monte
class EtatMontant: public EtatAscenseur
{
    public:
        EtatMontant(Ascenseur* ascenseur): EtatAscenseur(ascenseur){};
        Mouvements bouge() override;
        void affiche() override;
};

/// @brief Décrit l'état de l'ascenseur quand il descend
class EtatDescendant: public EtatAscenseur
{
    public:
        EtatDescendant(Ascenseur* ascenseur): EtatAscenseur(ascenseur){};
        Mouvements bouge() override;
        void affiche() override;
};

/// @brief Représente l'ascenseur. Stocke les étages et les personnes à chaque étage, ainsi que les passagers
class Ascenseur
{
    public:
        Ascenseur(short nombre_etages, short etage_minimal=0):etat(nullptr), etage_actuel(etage_minimal),
         etage_minimal(etage_minimal), nombre_etages(nombre_etages), demande_immobile(etage_minimal - 1){
            for(int i=etage_minimal;i< etage_minimal+nombre_etages;i++)
            {
                this->etages.push_back(new Etage(i));
            }
            this->setEtat(new EtatImmobile(this));
        };
        ~Ascenseur(){
            // Nettoie l'état
            this->setEtat(nullptr);
            // Nettoie les étages
            for(Etage* e : this->etages)
            {
                delete e;
            }
            this->etages.clear();
            // Nettoes les passagers restant
            for(Personne* p: this->passagers)
            {
                delete p;
            }
            this->passagers.clear();
        };
        /// @brief Permet d'ajouter une personne au système
        /// @param personne La personne a ajouter
        /// @param etage L'étage où se trouve la personne
        void ajoutePersonne(Personne* personne, short etage);
        /// @brief Affiche dans la console les informations sur l'ascenseur
        void affiche();
        /// @brief Effectue une itération
        void iteration();
        /// @brief Récupère l'étage minimum de l'ascenseur
        /// @return L'étage minimal
        short getEtageMinimal(){return this->etage_minimal;};
        /// @brief Récupère l'étage maximal de l'ascenseur
        /// @return L'étage maximal
        short getEtageMaximal(){return this->etage_minimal + this->nombre_etages-1;};
    private:
        /// @brief Effectue un mouvement et change éventuellement l'état
        /// @return Les déplacements qui ont eu lieu à une itération
        Mouvements bouge();
        /// @brief Affecte un nouvel état à l'ascenseur
        /// @param etat Nouvel état
        void setEtat(EtatAscenseur* etat);
        /// @brief Récupère l'étage d'un ascenseur en fonction de son numéro
        /// @param etage Numéro de l'étage
        /// @return Instance de l'étage correspondant à l'index ou nullptr
        Etage* getEtage(short etage);
        /// @brief Vérifie si l'ascenseur a des passagers qui montent
        /// @return true s'il y en a au moins un
        bool AMontants();
        /// @brief Vérifie si l'ascenseur a des passagers qui descendent
        /// @return true s'il y en a au moins un
        bool ADescendants();
        /// @brief Vérifie si l'ascenseur a des appels depuis les étages supérieurs
        /// @return true s'il y en a au moins un
        bool AAppelsMontants();
        /// @brief Vérifie si l'ascenseur a des appels depuis les étages inférieurs
        /// @return true s'il y en a au moins un
        bool AAppelsDescendants();
        /// @brief Stocke l'état de l'ascenseur
        EtatAscenseur* etat;
        /// @brief Stocke les passagers de l'ascenseur
        vector<Personne*> passagers;
        /// @brief Stocke les étages de l'ascenseur
        vector<Etage*> etages;
        /// @brief Stocke le numéro d'étage actuel de l'ascenseur
        short etage_actuel;
        /// @brief Stocke le numéro d'étage minimum de l'ascenseur
        short etage_minimal;
        /// @brief Stocke le nombre d'étages de l'ascenseur
        short nombre_etages;
        /// @brief Stocke l'étage demandé quand l'ascenseur est immobile
        short demande_immobile;
        friend class EtatAscenseur;
        friend class EtatImmobile;
        friend class EtatMontant;
        friend class EtatDescendant;
};