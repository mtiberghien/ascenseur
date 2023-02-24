#pragma once

/**
 * @file etage.hpp
 * @author Mathias Tiberghien
 * @brief Représente l'étage d'un ascenseur qui contient un vecteur de personnes attendant l'ascenseur
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "commons.hpp"
#include "personne.hpp"

class Etage
{
    public:
        Etage(int id):id(id){}
        ~Etage(){
            for(Personne* p : this->personnes)
            {
                delete p;
            }
            this->personnes.clear();
        };
        /// @brief Permet d'ajouter une personne à l'étage
        /// @param p La personne à ajouter
        void ajoutePersonne(Personne * p);
        /// @brief Supprime une personne de la liste
        /// @param it Itérateur sur la liste de personnes
        void removePersonne(vector<Personne*>::iterator it);
        /// @brief Compte le nombre de personnes à l'étage
        /// @return le nombre de personnes à cet étage
        int comptePersonnes(){return this->personnes.size();}
        /// @brief Retourne le numéro d'étage
        /// @return Le numéro d'étage
        int getId(){return this->id;}
        /// @brief Récupère l'itérateur de dépbut de la collection de personnes
        /// @return L'itérateur begin du vecteur personnes
        vector<Personne*>::iterator getPersonnesBegin(){return this->personnes.begin();}
        /// @brief Récupère l'itérateur de fin de la collection de personnes
        /// @return L'itérateur end du vecteur personnes
        vector<Personne*>::iterator getPersonnesEnd(){return this->personnes.end();}
    private:
        /// @brief Le numéro d'étage
        int id;
        /// @brief La liste des personnes attendant l'ascenseur
        vector<Personne*> personnes;
};