#ifndef JOUEUR_H
#define JOUEUR_H

/*!
 * \file joueur.h
 * \brief Definition permet de modifie le joueur, son état et ses déplacement
 * \author Alexis Barberis
 * \author Mohamed-Amine Boudhib
 * \author Lucas Lepape
 * \author Maxence Torchin
 * \author Jérémy Watripont
 * \version 1.0
 * \date 6 Janvier 2025
 */

#include "type.h"
#include <vector>

/*!
 * \brief Permet de faire bouger le joueur en prenant en compte les collisions
 * \param[out] modeDirectionEnAttente the matrix to be initialized
 * \param[out] score le nombre de point de
 * \param[in, out] carte permet de connaitre les elements sur la map
 * \param[in, out] unJoueur connaitre sa position et la modifie
 * @fn void mouvementJoueur(joueur & unJoueur, std::vector<std::vector<char>> & carte,unsigned & score,bool & modeDirectionEnAttente);
 */
void mouvementJoueur(joueur & unJoueur, std::vector<std::vector<char>> & carte,unsigned & score,bool & modeDirectionEnAttente);

/*!
 * \brief Permet de modifier les informations de score, de mode et de vie
 * \param[in, out] leJoueur1 avoir les informations necessaire : vie, score, mode
 * \param[in, out] leJoueur2 avoir les informations necessaire  : vie, score, mode
 * @fn void miseAJourMortsJanus(joueur & leJoueur1, joueur & leJoueur2);
 */
void miseAJourMortsJanus(joueur & leJoueur1, joueur & leJoueur2);

#endif // JOUEUR_H
