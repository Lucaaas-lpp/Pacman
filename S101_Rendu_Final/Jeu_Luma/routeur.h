#ifndef ROUTEUR_H
#define ROUTEUR_H
/*!
 * \file routeur.h
 * \brief Definition permet de gerer les routeurs
 * \author Alexis Barberis
 * \author Mohamed-Amine Boudhib
 * \author Lucas Lepape
 * \author Maxence Torchin
 * \author Jérémy Watripont
 * \version 1.0
 * \date 6 Janvier 2025
 */
#include "type.h"

/*!
 * \file routeur.h
 * \brief Definition permet de gerer les routeurs
 * \author Alexis Barberis
 * \author Mohamed-Amine Boudhib
 * \author Lucas Lepape
 * \author Maxence Torchin
 * \author Jérémy Watripont
 * \version 1.0
 * \date 6 Janvier 2025
 */

/*!
 * \brief Permet de modifie la direction que garde le routeur en fonction du passage du joueur
 * \param[out] unJoueur pour lire sa direction
 * \param[in] routeur pour modifier le deplacement garder en mémoire
 * @fn void joueurDirection(const joueur & unJoueur, routeur & unRouteur);
 */
void joueurDirection(const joueur & unJoueur, routeur & unRouteur);

/*!
 * \brief Permet de lire l'information dans le routeur pour suivre le joueur
 * \param[out] unEngloutisseur pour modifier son deplacement
 * \param[in] unRouteur lire sa direction
 * @fn changeDirection(engloutisseur & unEngloutisseur, const routeur & unRouteur);
 */
void changeDirection(engloutisseur & unEngloutisseur, const routeur & unRouteur);

bool respectIndicationRouteur(engloutisseur & unEngloutisseur);

#endif // ROUTEUR_H
