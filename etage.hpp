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
        /// @brief Compte le nombre de personnes à l'étage
        /// @return le nombre de personnes à cet étage
        int comptePersonnes(){return this->personnes.size();}
        /// @brief Retourne le numéro d'étage
        /// @return Le numéro d'étage
        int getId(){return this->id;}
        /// @brief Vide les personnes d'un étage
        void clear(){this->personnes.clear();};
        /// @brief Récupère une personne en fonction de son index
        /// @param i Index de la personne à retrouver
        /// @return La personne si l'index est valide, nullptr sinon
        Personne* getPersonne(int i)
        {
            if(i>=0 && i < this->personnes.size())
            {
                return this->personnes[i];
            }
            return nullptr;
        }
    private:
        /// @brief Le numéro d'étage
        int id;
        /// @brief La liste des personnes attendant l'ascenseur
        vector<Personne*> personnes;
};