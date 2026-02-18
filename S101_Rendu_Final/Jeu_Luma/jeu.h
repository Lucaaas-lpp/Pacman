#ifndef JEU_H
#define JEU_H
/*!
 * \file jeu.h
 * \brief Definition permet d'utiliser tout les éléments du jeu et les fonctionnalitées
 * \author Alexis Barberis
 * \author Mohamed-Amine Boudhib
 * \author Lucas Lepape
 * \author Maxence Torchin
 * \author Jérémy Watripont
 * \version 1.0
 * \date 6 Janvier 2025
 */

#include <string>
#include <map>
#include <vector>
#include "mingl/mingl.h"
#include "type.h"
#include "parametre.h"

/**
 * @brief initParams1 : touches du joueur
 */
std::map<std::string,char> initParams();

/*!
 * \brief Permet de deplacer les joueur en prenant en compte les collisions
 * \param[in, out] unJoueur pour le déplacer
 * \param[in, out] deuxJoueur pour le déplacer
 * \param[in, out] carte position sur la carte, ame a manger et mise a jour de celle-ci
 * \param[in out] modeDirectionEnAttente qui permet de rendre les déplacement plus fluides
 * \param[in, out] compteurAme nombre d'ame manger par le joueur
 * @fn mouvementJanus(joueur & unJoueur, joueur & deuxJoueur, std::vector<std::vector<char>> & carte,bool & modeDirectionEnAttente, unsigned & compteurAme);
 */
void mouvementJanus(joueur & unJoueur, joueur & deuxJoueur, std::vector<std::vector<char>> & carte,bool & modeDirectionEnAttente, unsigned & compteurAme);

/*!
 * \brief Permet de savoir quelles touches est choisi par le joueur
 * \param[in] window pour savoir quelles touches est appuyer
 * \param[in, out] unJoueur modifier sa prochaine direction
 * \param[in] params connaitre les touches du joueur
 * @fn void appuiTouches(MinGL & window, joueur & unJoueur, std::map<std::string,char> & params);
 */
void appuiTouches(MinGL & window, joueur & unJoueur, std::map<std::string,char> & params);

/*!
 * \brief Permet de lancer le mode Aventure
 */
void jeuAventure();

/*!
 * \brief Permet de modifier les éléments de la carte dans le jeu Aventure
 * \param[out] window permet d'afficher les forme de MinGl
 * \param[in] carte savoir ce qu'il y a, a des coordonnees precise
 * \param[out] unjoueur recuperer les information necessaire
 * \param[out] score pour l'incrementer
 * \param[out] unEngloutisseur pour connaitre les coordonnees
 * @fn afficherCarte(MinGL & window, const std::vector<std::vector<char>> & carte, joueur & unjoueur, unsigned & score, engloutisseur & unEngloutisseur);
 */
void afficherCarte(MinGL & window, const std::vector<std::vector<char>> & carte, joueur & unjoueur, unsigned & score, engloutisseur & unEngloutisseur, std::vector <routeur> ensembleRouteurs );

/*!
 * \brief Permet au joueur de dash
 * \param[in, out] unJoueur pour le déplacé
 * \param[in, out] deuxJoueur pour le déplacé
 * \param[in] carte pour modifie la taille du déplacement pour le dash
 * \param[out] compteurAme savoir combien il reste d'âme dans la carte
 * @fn void dash(joueur & unJoueur, joueur & deuxJoueur, std::vector<std::vector<char>> & carte, unsigned & compteurAme);
 */
void dash(joueur & unJoueur, joueur & deuxJoueur, std::vector<std::vector<char>> & carte, unsigned & compteurAme);

/*!
 * \brief Permet de garder la touche presser en prochaine direction
 * \param[out] window savoir quelle touche est presser
 * \param[in] unJoueur modifier sa prochaine direction
 * \param[out] deuxJoueur pour savoir si le deplacement l'impactera
 * \param[out] params connaitre les touches du joueur
 * \param[out] carte permet d'utiliser le dash pour etre sur du déplacement et de ses collisions
 * \param[out] compteurAme savoir combien il reste d'âme dans la carte
 * @fn void appuiTouchesJanus(MinGL & window, joueur & unJoueur, joueur & deuxJoueur, std::map<std::string,char> & params, std::vector<std::vector<char>> & carte, unsigned & compteurAme);
 */
void appuiTouchesJanus(MinGL & window, joueur & unJoueur, joueur & deuxJoueur, std::map<std::string,char> & params, std::vector<std::vector<char>> & carte, unsigned & compteurAme);

/*!
 * \brief Permet d'afficher et de modifier la carte dans le mode de jeu Janus
 * \param[out] window permet d'afficher les forme de MinGl
 * \param[in] carte savoir ce qu'il y a, a des coordonnees precise
 * \param[in] unjoueur pour connaitre ses coordonnees
 * \param[in] deuxjoueur pour connaitre ses coordonnees
 * \param[in, out] comptueur pour la duree de la mort
 * @fn void afficherCarteJanus(MinGL & window, const std::vector<std::vector<char>> & carte, joueur & unjoueur, joueur & deuxjoueur, unsigned compteur);
 */
void afficherCarteJanus(MinGL & window, const std::vector<std::vector<char>> & carte, joueur & unjoueur, joueur & deuxjoueur, unsigned compteur);

/*!
 * \brief Permet de lancer le mode de jeu Janus
 */
void jeuJanus();


#endif // JEU_H
