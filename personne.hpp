#pragma once

/**
 * @file personne.hpp
 * @author Mathias Tiberghien
 * @brief Classe personne
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief Représente une personne utilisant l'ascenseur et stocke l'étage de destination
 * 
 */
class Personne
{
    public:
        Personne(short etage_initial, short etage_desire): etage_initial(etage_initial), etage_desire(etage_desire), est_dans_ascensceur(false){}
        ~Personne(){}
        short getEtageDesire() const {return this->etage_desire;}
        short getEtageInitial() const {return this->etage_initial;}
        bool getEstDansAscenseur() const {return this->est_dans_ascensceur;}
        short getEtageAppel() const {return this->est_dans_ascensceur ? this->getEtageDesire() : this->getEtageInitial();}
        void setEstDansAscenseur(bool statut) {this->est_dans_ascensceur=statut;}
    private:
    short etage_desire;
    short etage_initial;
    bool est_dans_ascensceur;
};