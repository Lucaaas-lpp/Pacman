#ifndef ENNEMI_H
#define ENNEMI_H

/*!
 * \file ennemi.h
 * \brief Permet d'initilisé les ennemis et leurs déplacement
 * \author Alexis Barberis
 * \author Mohamed-Amine Boudhib
 * \author Lucas Lepape
 * \author Maxence Torchin
 * \author Jérémy Watripont
 * \version 1.0
 * \date 6 Janvier 2025
 */

#include "type.h"
#include <string>
#include <vector>

/*!
 * \brief Permet de
 * \param[out] coordonnees
 * \param[in, out] carte position sur la carte et mise a jour de celle-ci
 * \param[out] direction
 * @fn void InitGrid (CMat & Mat, const CMyParam & Params, CPosition & PosPlayer1, CPosition & PosPlayer2);
 */
bool deplacementSurMur(const std::pair <size_t, size_t> coordonnees, const std::vector<std::vector<char>> & carte, const std::string direction);

void changeDirectionAleatoire(engloutisseur unEngloutisseur);

/*!
 * \brief Permet de
 * \param[in] Engloutisseur
 * \param[in, out] carte position sur la carte, ame a manger et mise a jour de celle-ci
 * @fn void miseAJourImmobilisation(std::vector <engloutisseur> & ensembleEngloutisseur);
 */
engloutisseur mouvementEngloutisseur(engloutisseur unEngloutisseur, std::vector<std::vector<char>> & carte);

/*!
 * \brief Permet de
 * \param[in] ensembleEngloutisseur
 * @fn void miseAJourImmobilisation(std::vector <engloutisseur> & ensembleEngloutisseur);
 */
void miseAJourImmobilisation(std::vector <engloutisseur> & ensembleEngloutisseur);

unsigned miseAJourDangerosite(unsigned & compteurDangerosite, std::vector<engloutisseur> &ensembleEngloutisseur);

#endif // ENNEMI_H

