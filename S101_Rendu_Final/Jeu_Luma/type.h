#ifndef TYPE_H
#define TYPE_H

/*!
 * \file type.h
 * \brief Definition permet de définir les structure des joueurs et fantomes
 * \author Alexis Barberis
 * \author Mohamed-Amine Boudhib
 * \author Lucas Lepape
 * \author Maxence Torchin
 * \author Jérémy Watripont
 * \version 1.0
 * \date 6 Janvier 2025
 */

#include <string>

/**
 * @brief Struct contient toutes les clé necessaire pour la structure engloutisseur
 */
struct engloutisseur{
    std::pair <size_t, size_t> coordonnees;
    unsigned immobilisation;
    std::string direction;
    std::pair <size_t, size_t> pointDApparition;
    unsigned dangerosite;
};

/**
 * @brief Struct contient toutes les clé necessaire pour la structure joueur
 */
struct joueur{
    std::pair <size_t, size_t> coordonnees;
    bool modeMange;
    bool vivant;
    std::string directionActive;
    std::string directionEnAttente;
    unsigned score = 0;

};

/**
 * @brief Struct contient toutes les clé necessaire pour la structure routeur
 */
struct routeur{
    std::pair <size_t, size_t> coordonnees;
    std::string directionJoueur;
};

#endif // TYPE_H
