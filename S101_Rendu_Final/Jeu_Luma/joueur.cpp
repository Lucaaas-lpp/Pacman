#include "joueur.h"
#include <string>
#include <vector>
#include "type.h"

using namespace std;

void mouvementJoueur(joueur & unJoueur, vector<vector<char>> & carte,unsigned & score,bool & modeDirectionEnAttente){
    string direction = unJoueur.directionEnAttente;
    if (!modeDirectionEnAttente){
        direction = unJoueur.directionActive;
    }
    pair <size_t, size_t> nouvellesCoordonnees = unJoueur.coordonnees;
    // Met à jour la direction en fonction des touches pressées
    if (direction == "KeyUp") {
        --nouvellesCoordonnees.first;
    }
    else if (direction == "KeyDown") {
        ++nouvellesCoordonnees.first;;
    }
    else if (direction == "KeyLeft") {
        --nouvellesCoordonnees.second;
    }
    else if (direction == "KeyRight") {
        ++nouvellesCoordonnees.second;
    }
    if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] != '#'
    and carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] != '-'
    and carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] != '_'){
        if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] == '*'){
            score += 10;
        }
        if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] == '0'){
            unJoueur.modeMange = true;
            score += 50;
        }
        carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] = ' ';
        unJoueur.coordonnees = nouvellesCoordonnees;
        if (modeDirectionEnAttente){
            unJoueur.directionActive = unJoueur.directionEnAttente;
        }
    }
    else if (modeDirectionEnAttente){
        bool modeMouvementEnAttente = false;
        mouvementJoueur(unJoueur,carte,score,modeMouvementEnAttente);
    }
    if (direction == "KeyRight" and carte[unJoueur.coordonnees.first][unJoueur.coordonnees.second+1] == 'P'){ // ------ activitation des tps
        unJoueur.coordonnees = {10, 2};
    }
    if (direction == "KeyLeft" and carte[unJoueur.coordonnees.first][unJoueur.coordonnees.second-1] == 'T'){
        unJoueur.coordonnees = {10, 36};
    }
}

void miseAJourMortsJanus(joueur & leJoueur1, joueur & leJoueur2){
    if (leJoueur1.coordonnees == leJoueur2.coordonnees){
        if (leJoueur1.modeMange){
            leJoueur2.vivant = false;
            leJoueur1.modeMange = false;
            leJoueur1.score += 100;
            leJoueur2.score -= 50;
            leJoueur2.coordonnees = {9, 19};
        }
        else if(leJoueur2.modeMange){
            leJoueur1.vivant = false;
            leJoueur2.modeMange = false;
            leJoueur2.score += 100;
            leJoueur1.score -= 50;
            leJoueur1.coordonnees = {9, 19};
        }
    }
}
