#include "routeur.h"
#include <string>
#include "type.h"
#include <cstdlib>
#include <ctime>

using namespace std;


void joueurDirection(const joueur & leJoueur, routeur & unRouteur){
    unRouteur.directionJoueur = leJoueur.directionActive;
}

void changeDirection(engloutisseur & unEngloutisseur, const routeur & unRouteur){
    unEngloutisseur.direction = unRouteur.directionJoueur;
}

bool respectIndicationRouteur(engloutisseur & unEngloutisseur){
    unsigned nombreAleatoire = (rand ( )%100) +1;
    if (nombreAleatoire <= unEngloutisseur.dangerosite){
        return true;
    }
    return false;
}
