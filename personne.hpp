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
        Personne(short etage_desire): etage_desire(etage_desire){}
        ~Personne(){}
        short getEtageDesire() const {return this->etage_desire;}
    private:
    short etage_desire;
};