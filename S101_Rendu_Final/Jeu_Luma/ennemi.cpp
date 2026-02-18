#include "ennemi.h"
#include "type.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool deplacementSurMur(const pair <size_t, size_t> coordonnees, const vector<vector<char>> & carte, const string direction){
    bool mur = false;
    if (direction == "KeyUp") {
        mur = carte[coordonnees.first-1][coordonnees.second] == '#';
    }
    else if (direction == "KeyDown") {
        mur = carte[coordonnees.first+1][coordonnees.second] == '#';
    }
    else if (direction == "KeyLeft") {
        mur = carte[coordonnees.first][coordonnees.second-1] == '#';
    }
    else if (direction == "KeyRight") {
        mur = carte[coordonnees.first][coordonnees.second+1] == '#';
    }
    return mur;
}

void changeDirectionAleatoire(engloutisseur unEngloutisseur){
    unsigned nombreAleatoire = (rand ( )%4)+1;
    if (nombreAleatoire == 1){
        unEngloutisseur.direction = "KeyUp";
    }
    if (nombreAleatoire == 2){
        unEngloutisseur.direction = "KeyDown";
    }
    if (nombreAleatoire == 3){
        unEngloutisseur.direction = "KeyLeft";
    }
    if (nombreAleatoire == 4){
        unEngloutisseur.direction = "KeyRight";
    }
    cout << nombreAleatoire << ' ' << unEngloutisseur.direction;
}

engloutisseur directionOpposee(engloutisseur &unEngloutisseur,vector<vector<char>> & carte){
    pair <size_t, size_t> nouvellesCoordonnees = unEngloutisseur.coordonnees;
    if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second]== '-'){
        unEngloutisseur.direction = "KeyUp";
        --nouvellesCoordonnees.first;
    }
    else if (unEngloutisseur.direction == "KeyUp"){
        unEngloutisseur.direction = "KeyDown";
        ++nouvellesCoordonnees.first;
    }
    else if (unEngloutisseur.direction == "KeyDown"){
        unEngloutisseur.direction = "KeyUp";
        --nouvellesCoordonnees.first;
    }
    else if (unEngloutisseur.direction == "KeyLeft"){
        unEngloutisseur.direction = "KeyRight";
        ++nouvellesCoordonnees.second;
    }
    else if (unEngloutisseur.direction == "KeyRight"){
        unEngloutisseur.direction = "KeyLeft";
        --nouvellesCoordonnees.second;
    }
    unEngloutisseur.coordonnees = nouvellesCoordonnees;
    return unEngloutisseur;
}

engloutisseur mouvementEngloutisseur(engloutisseur unEngloutisseur,vector<vector<char>> & carte){
    pair <size_t, size_t> nouvellesCoordonnees = unEngloutisseur.coordonnees;
    //Si le personnage est sur le caractère '_' il ne peut que monter//Si le personnage est sur le caractère '-' il ne peut que monter
    if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second]== '-'){
        unEngloutisseur.direction = "KeyUp";
        --nouvellesCoordonnees.first;
    }
    else if (unEngloutisseur.direction == "KeyUp"){
        if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyUp")){
            unEngloutisseur.direction = "KeyUp";
            --nouvellesCoordonnees.first;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyLeft")){
            unEngloutisseur.direction = "KeyLeft";
            --nouvellesCoordonnees.second;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyRight")){
            unEngloutisseur.direction = "KeyRight";
            ++nouvellesCoordonnees.second;
        }
        else{
            return directionOpposee(unEngloutisseur, carte);
        }
    }
    else if (unEngloutisseur.direction == "KeyDown"){
        if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyDown")){
            unEngloutisseur.direction = "KeyDown";
            ++nouvellesCoordonnees.first;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyLeft")){
            unEngloutisseur.direction = "KeyLeft";
            --nouvellesCoordonnees.second;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyRight")){
            unEngloutisseur.direction = "KeyRight";
            ++nouvellesCoordonnees.second;
        }
        else{
            return directionOpposee(unEngloutisseur, carte);
        }
    }
    else if (unEngloutisseur.direction == "KeyLeft"){
        if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyLeft")){
            unEngloutisseur.direction = "KeyLeft";
            --nouvellesCoordonnees.second;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyUp")){
            unEngloutisseur.direction = "KeyUp";
            --nouvellesCoordonnees.first;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyDown")){
            unEngloutisseur.direction = "KeyDown";
            ++nouvellesCoordonnees.first;
        }
        else{
            return directionOpposee(unEngloutisseur, carte);
        }
    }
    else if (unEngloutisseur.direction == "KeyRight"){
        if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyRight")){
            unEngloutisseur.direction = "KeyRight";
            ++nouvellesCoordonnees.second;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyUp")){
            unEngloutisseur.direction = "KeyUp";
            --nouvellesCoordonnees.first;
        }
        else if (!deplacementSurMur(unEngloutisseur.coordonnees, carte, "KeyDown")){
            unEngloutisseur.direction = "KeyDown";
            ++nouvellesCoordonnees.first;
        }
        else{
            return directionOpposee(unEngloutisseur, carte);
        }
    }
    if (unEngloutisseur.direction == "KeyRight" and carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second+1] == 'P'){ // ------ activitation des tps
        nouvellesCoordonnees = {10, 2};
    }
    if (unEngloutisseur.direction == "KeyLeft" and carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second-1] == 'T'){
        nouvellesCoordonnees = {10, 36};
    }
    unEngloutisseur.coordonnees = nouvellesCoordonnees;
    return unEngloutisseur;
}



unsigned miseAJourDangerosite(unsigned & compteurDangerosite, vector<engloutisseur> &ensembleEngloutisseur){
    if (compteurDangerosite == 10){ // Tout les dix tours
        compteurDangerosite = 0;
        for (size_t i = 0; i < ensembleEngloutisseur.size() ; ++i){
            unsigned miseAJourDangerosite = (rand ( )%100) +1;
            if (miseAJourDangerosite <= 50 && ensembleEngloutisseur[i].dangerosite <= 90){
                // 50% de chance de devenir plus violent
                // Limité à 90 de dangerosite
                ++ensembleEngloutisseur[i].dangerosite;
            }
        }
    }
    ++compteurDangerosite;
    return compteurDangerosite;
}
