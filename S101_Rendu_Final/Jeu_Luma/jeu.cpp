#include "jeu.h"

#define FPS_LIMIT 7

#include "ennemi.h"
#include "joueur.h"
#include "routeur.h"
#include "type.h"
#include "parametre.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include "mingl/mingl.h"
#include "mingl/gui/text.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"

using namespace std;

void mouvementJanus(joueur & unJoueur, joueur & deuxJoueur, vector<vector<char>> & carte,bool & modeDirectionEnAttente, unsigned & compteurAme){
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
        ++nouvellesCoordonnees.first;
    }
    else if (direction == "KeyLeft") {
        --nouvellesCoordonnees.second;
    }
    else if (direction == "KeyRight") {
        ++nouvellesCoordonnees.second;
    }
    if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] != '#' and carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] != '-'){
        if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] == '*'){
            unJoueur.score += 10;
            ++compteurAme;
        }
        if (carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] == '0'){
            unJoueur.modeMange = true;
            deuxJoueur.modeMange = false;
            unJoueur.score += 50;
            ++compteurAme;
        }
        carte[nouvellesCoordonnees.first][nouvellesCoordonnees.second] = ' ';
        unJoueur.coordonnees = nouvellesCoordonnees;
        if (modeDirectionEnAttente){
            unJoueur.directionActive = unJoueur.directionEnAttente;
        }
    }

    else if (modeDirectionEnAttente){
        bool modeMouvementEnAttente = false;
        mouvementJanus(unJoueur, deuxJoueur, carte,modeMouvementEnAttente,compteurAme);
    }
    if (direction == "KeyRight" && carte[unJoueur.coordonnees.first][unJoueur.coordonnees.second+1] == 'P'){ // ------ activitation des tps
        unJoueur.coordonnees = {10, 2};
    }
    if (direction == "KeyLeft" && carte[unJoueur.coordonnees.first][unJoueur.coordonnees.second-1] == 'T'){
        unJoueur.coordonnees = {10, 36};
    }
}

void dash(joueur & unJoueur, joueur & deuxJoueur, vector<vector<char>> & carte, unsigned & compteurAme){
    bool dash = false;
    mouvementJanus(unJoueur, deuxJoueur, carte, dash,compteurAme);
    mouvementJanus(unJoueur, deuxJoueur, carte, dash,compteurAme);
    mouvementJanus(unJoueur, deuxJoueur, carte, dash,compteurAme);
}

void appuiTouchesJanus(MinGL & window, joueur & unJoueur, joueur & deuxJoueur, std::map<string, char> &params, std::vector<std::vector<char> > &carte, unsigned & compteurAme){
    if (window.isPressed({params["KeyUp"], false})) {
        unJoueur.directionEnAttente = "KeyUp";
    }
    else if (window.isPressed({params["KeyDown"], false})) {
        unJoueur.directionEnAttente = "KeyDown";
    }
    else if (window.isPressed({params["KeyLeft"], false})) {
        unJoueur.directionEnAttente = "KeyLeft";
    }
    else if (window.isPressed({params["KeyRight"], false})) {
        unJoueur.directionEnAttente = "KeyRight";
    }
    else if (window.isPressed({params["KeyPower"], false})){
        dash(unJoueur, deuxJoueur, carte, compteurAme);
    }
}

void miseAJourMorts(joueur & unJoueur, vector <engloutisseur> & ensembleEngloutisseur){
    for (size_t i = 0; i < ensembleEngloutisseur.size(); ++i){
        if (ensembleEngloutisseur[i].coordonnees == unJoueur.coordonnees){
            if (unJoueur.modeMange){
                ensembleEngloutisseur[i].coordonnees = ensembleEngloutisseur[i].pointDApparition; //r emise de l'engloutisseur au point de départ.
                ensembleEngloutisseur[i].immobilisation = 21; // temps d'immobilisation.
                if (i!=2){
                    ensembleEngloutisseur[i].dangerosite = 30;
                };
                ensembleEngloutisseur[i].direction = "KeyUp"; // réinitialisation de la position de l'engloutisseur.
            }
            else{
                unJoueur.vivant = false;
            }
        }
    }
}

void appuiTouches(MinGL & window, joueur & unJoueur, map<string,char> & params){
    if (window.isPressed({params["KeyUp"], false})) {
        unJoueur.directionEnAttente = "KeyUp";
    }
    else if (window.isPressed({params["KeyDown"], false})) {
        unJoueur.directionEnAttente = "KeyDown";
    }
    else if (window.isPressed({params["KeyLeft"], false})) {
        unJoueur.directionEnAttente = "KeyLeft";
    }
    else if (window.isPressed({params["KeyRight"], false})) {
        unJoueur.directionEnAttente = "KeyRight";
    }
}



void afficherCarteJanus(MinGL & window, const vector<vector<char>> & carte, joueur & unJoueur, joueur & deuxJoueur, unsigned compteur){
    unsigned ajustementX = 25;
    unsigned ajustementY = 80;
    string texteScore1 = "score Joueur 1 :" + to_string(unJoueur.score);
    string texteScore2 = "score Joueur 2 :" + to_string(deuxJoueur.score);
    string reaparition = "reaparition dans : " + to_string(3 - compteur/7);
    string modemange1 = "Mode Mange Joueur 1 : " + to_string(unJoueur.modeMange);
    string modemange2 = "Mode Mange Joueur 2 : " + to_string(deuxJoueur.modeMange);
    window << nsGui::Text(nsGraphics::Vec2D(10,10),texteScore1,nsGraphics::KWhite);
    window << nsGui::Text(nsGraphics::Vec2D(200,10),texteScore2,nsGraphics::KWhite);
    window << nsGui::Text(nsGraphics::Vec2D(400,10),reaparition,nsGraphics::KWhite);
    window << nsGui::Text(nsGraphics::Vec2D(600,10),modemange1,nsGraphics::KWhite);
    window << nsGui::Text(nsGraphics::Vec2D(800,10),modemange2,nsGraphics::KWhite);
    for(unsigned y = 0; y < carte.size(); ++y){
        for(unsigned x = 0; x < carte[y].size(); ++x){
            if(carte[y][x] == '#'){
                nsShape::Rectangle Mur = nsShape::Rectangle(nsGraphics::Vec2D(x*30 + ajustementX, y*30 + ajustementY), nsGraphics::Vec2D(x*30 + 30 + ajustementX, y*30 +30 + ajustementY), nsGraphics::KYellow);
                window << Mur;
            }
            else if(carte[y][x] == '*'){
                nsShape::Circle ame(nsGraphics::Vec2D(x * 30 + 15 + ajustementX, y * 30 + 15 + ajustementY), 5, nsGraphics::KWhite);
                window << ame;
            }
            else if(carte[y][x] == '0'){
                nsShape::Circle ame(nsGraphics::Vec2D(x * 30 + 15 + ajustementX, y * 30 + 15 + ajustementY), 10, nsGraphics::KWhite);
                window << ame;
            }
        }
    }
    if (unJoueur.vivant == true){
        window << nsShape::Circle(nsGraphics::Vec2D(unJoueur.coordonnees.second*30 +15 + ajustementX , unJoueur.coordonnees.first*30 +15 + ajustementY), 15, nsGraphics::KCyan);
    }
    else{
        window << nsShape::Circle(nsGraphics::Vec2D(unJoueur.coordonnees.second*30 +15 + ajustementX , unJoueur.coordonnees.first*30 +15 + ajustementY), 15, nsGraphics::KCyan);
    }

    if (deuxJoueur.vivant == true){
        window << nsShape::Circle(nsGraphics::Vec2D(deuxJoueur.coordonnees.second*30 +15 + ajustementX , deuxJoueur.coordonnees.first*30 +15 + ajustementY), 15, nsGraphics::KPurple);
    }
    else{
        window << nsShape::Circle(nsGraphics::Vec2D(deuxJoueur.coordonnees.second*30 +15 + ajustementX , deuxJoueur.coordonnees.first*30 +15 + ajustementY), 15, nsGraphics::KPurple);
    }
}

void afficherCarte(MinGL & window, const vector<vector<char>> & carte, joueur & unJoueur, unsigned & score, vector <engloutisseur> & ensembleEngloutisseur){
    unsigned ajustementX = 50;
    unsigned ajustementY = 15;
    string texteScore = "score : " + to_string(score);
    window << nsGui::Text(nsGraphics::Vec2D(10,10),texteScore,nsGraphics::KWhite);
    for(unsigned y = 0; y < carte.size(); ++y){
        for(unsigned x = 0; x < carte[y].size(); ++x){
            if(carte[y][x] == '#'){
                nsShape::Rectangle Mur = nsShape::Rectangle(nsGraphics::Vec2D(x*30 + ajustementX, y*30 + ajustementY), nsGraphics::Vec2D(x*30 + 30 + ajustementX, y*30 +30 + ajustementY), nsGraphics::KPurple);
                window << Mur;
            }
            else if(carte[y][x] == '*'){
                nsShape::Circle ame(nsGraphics::Vec2D(x * 30 + 15 + ajustementX, y * 30 + 15 + ajustementY), 5, nsGraphics::KWhite);
                window << ame;
            }
            else if(carte[y][x] == '0'){
                nsShape::Circle ame(nsGraphics::Vec2D(x * 30 + 15 + ajustementX, y * 30 + 15 + ajustementY), 10, nsGraphics::KWhite);
                window << ame;
            }
        }
    }
    window << nsShape::Circle(nsGraphics::Vec2D(unJoueur.coordonnees.second*30 +15 + ajustementX , unJoueur.coordonnees.first*30 +15 + ajustementY), 15, nsGraphics::KCyan);
    for (size_t i = 0; i < ensembleEngloutisseur.size() ; ++i){
        window << nsShape::Circle(nsGraphics::Vec2D(ensembleEngloutisseur[i].coordonnees.second*30 +15 + ajustementX , ensembleEngloutisseur[i].coordonnees.first*30 +15 + ajustementY), 15, nsGraphics::KRed);
    }
}

void jeuJanus(){
    // La carte du jeu
    vector<vector<char>> carte1 = { // ------------- portail a faire au centre de la map pour fantome
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#'},
        {'#','*','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','*','#'},
        {'#','*','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','*','#'},
        {'#','*','*','0','*','*','*','*','*','*','*','*','r','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','0','*','*','*','*','#'},
        {'#','*','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'#','*','*','*','*','*','*','*','*','#','#','#','*','*','*','*','*','*','*','#','*','*','*','*','*','*','*','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','*','#','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','-',' ','-','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'T',' ',' ','*','*','*','*','*','*','*','*','*','*','#',' ',' ',' ',' ','-','-','-',' ',' ',' ',' ','#','*','*','*','*','*','*','*','*','*','*',' ',' ','P'},
        {'#','#','#','#','#','#','#','#','*','#','#','#','*','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','*','#','#','#','*','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
        {'#','*','*','*','*','*','*','*','0','*','*','*','*','*','*','*','*','*','*','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#'},
        {'#','*','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','*','#'},
        {'#','*','*','*','*','*','*','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','*','*','*','*','*','*','#'},
        {'#','#','#','#','#','#','*','#','*','#','#','#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#','#','#','*','#','*','#','#','#','#','#','#'},
        {'#','*','*','*','*','*','*','*','*','#','#','#','*','*','*','*','*','*','*','#','*','*','*','*','*','*','0','#','#','#','*','*','*','*','*','*','*','*','#'},
        {'#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#'},
        {'#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    // Compteur d'ame
    unsigned compteurAme = 0;

    // Initialise le système
    MinGL window("Luma", nsGraphics::Vec2D(1220, 800), nsGraphics::Vec2D(1080, 1920), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();
    map<string,char> parametres1 = initParams1();
    map<string,char> parametres2 = initParams2();
    //     chrono::milliseconds tempsArret(1000/tickParSecondes);
    joueur leJoueur1 = {{1,1},false,true,"KeyLeft","KeyLeft"};//initialisation du joueur1
    joueur leJoueur2 = {{carte1.size()-2, carte1[0].size()-2},true,true,"KeyRight", "KeyRight"};//initialisation du joueur2

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // compteur déplacement
    unsigned compteur = 0;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();
        //On fait tourner les procédures
        appuiTouchesJanus(window,leJoueur1, leJoueur2, parametres1,carte1,compteurAme);
        appuiTouchesJanus(window,leJoueur2, leJoueur1,parametres2,carte1,compteurAme);
        bool modeMouvementEnAttente = true;
        if (leJoueur1.vivant){
            mouvementJanus(leJoueur1, leJoueur2, carte1, modeMouvementEnAttente,compteurAme);
        }
        else if (!leJoueur1.vivant) {
            ++compteur;
            if (compteur == 21){
                leJoueur1.vivant = true;
                leJoueur1.modeMange = true;
                leJoueur2.modeMange = false;
                compteur = 0;
            }
        }
        miseAJourMortsJanus(leJoueur1, leJoueur2);
        if (leJoueur2.vivant){
            mouvementJanus(leJoueur2, leJoueur1, carte1,modeMouvementEnAttente,compteurAme);
        }
        else if (!leJoueur2.vivant){
            ++compteur;
            if (compteur == 21){
                leJoueur2.vivant = true;
                leJoueur2.modeMange = true;
                leJoueur1.modeMange = false;
                compteur = 0;
            }
        }
        miseAJourMortsJanus(leJoueur1, leJoueur2);
        afficherCarteJanus(window, carte1, leJoueur1, leJoueur2, compteur);

        if(compteurAme == 324){
            break;
        }

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
}

void jeuAventure(){
    srand (time (0));
    // Initialise le système
    MinGL window("Luma", nsGraphics::Vec2D(1280, 840), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();
    unsigned score = 0;
    unsigned cptMange = 0;
    unsigned compteurDangerosite = 0;
    // Initialisation des paramètres
    map<string,char> parametres = initParams1();
    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()){
        unsigned nbVies = 3;
        while (nbVies > 0){
            // La carte du jeu
            vector<vector<char>> carte1 = { // ------------- portail a faire au centre de la map pour fantome
                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                {'#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#'},
                {'#','*','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','*','#'},
                {'#','*','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','*','#'},
                {'#','*','*','0','*','*','*','*','*','*','*','*','r','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','0','*','*','*','*','#'},
                {'#','*','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'#','*','*','*','*','*','*','*','*','#','#','#','*','*','*','*','*','*','*','#','*','*','*','*','*','*','*','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'#','#','#','#','#','#','#','#','*','#','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'#','#','#','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','-','-','-','#','#','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'T',' ',' ','*','*','*','*','*','*','*','*','*','*','#',' ',' ',' ',' ','-','-','-',' ',' ',' ',' ','#','*','*','*','*','*','*','*','*','*','*',' ',' ','P'},
                {'#','#','#','#','#','#','#','#','*','#','#','#','*','#',' ','#','#','#','#','#','#','#','#','#',' ','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'#','#','#','#','#','#','#','#','*','#','#','#','*','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'#','#','#','#','#','#','#','#','*','#','#','#','*','#','#','#','_','#','#','#','#','#','_','#','#','#','*','#','#','#','*','#','#','#','#','#','#','#','#'},
                {'#','*','*','*','*','*','*','*','0','*','*','*','*','*','*','*','*','*','*','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#'},
                {'#','*','#','#','#','#','#','#','*','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','*','#','#','#','#','#','#','*','#'},
                {'#','*','*','*','*','*','*','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','*','*','*','*','*','*','#'},
                {'#','#','#','#','#','#','*','#','*','#','#','#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#','#','#','*','#','*','#','#','#','#','#','#'},
                {'#','*','*','*','*','*','*','*','*','#','#','#','*','*','*','*','*','*','*','#','*','*','*','*','*','*','0','#','#','#','*','*','*','*','*','*','*','*','#'},
                {'#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','*','#'},
                {'#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#'},
                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
            };


            // On initialise que le jour n'est pas sur un routeur
            bool joueurSurRouteur = false;

            //initialisation du joueur
            joueur unJoueur = {{4,8},false,true,"KeyRight","KeyRight",0};

            //Initialisation des engloutisseurs
            vector <engloutisseur> ensembleEngloutisseur;
            engloutisseur engloutisseurUn = {{12,14},true,"KeyUp",{12,14},30};
            engloutisseur engloutisseurDeux = {{12,16},true,"KeyDown",{12,16},30};
            engloutisseur engloutisseurTrois = {{12,22},true,"KeyDown",{12,22},90};
            engloutisseur engloutisseurQuatre = {{12,24},true,"KeyUp",{12,24},30};
            ensembleEngloutisseur.push_back(engloutisseurUn);
            ensembleEngloutisseur.push_back(engloutisseurDeux);
            ensembleEngloutisseur.push_back(engloutisseurTrois);
            ensembleEngloutisseur.push_back(engloutisseurQuatre);

            // Initialisation des routeurs
            vector <routeur> ensembleRouteurs;
            routeur R1 = {{1,8},"KeyDown"};
            ensembleRouteurs.push_back(R1);
            routeur R2 = {{1,30},"KeyDown"};
            ensembleRouteurs.push_back(R2);
            routeur R3 = {{4,1},"KeyRight"};
            ensembleRouteurs.push_back(R3);
            routeur R4 = {{4,8},"KeyRight"};
            ensembleRouteurs.push_back(R4);
            routeur R5 = {{4,12},"KeyLeft"};
            ensembleRouteurs.push_back(R5);
            routeur R6 = {{4,18},"KeyLeft"};
            ensembleRouteurs.push_back(R6);
            routeur R7 = {{4,20},"KeyLeft"};
            ensembleRouteurs.push_back(R7);
            routeur R8 = {{4,26},"KeyLeft"};
            ensembleRouteurs.push_back(R8);
            routeur R9 = {{4,30},"KeyDown"};
            ensembleRouteurs.push_back(R9);
            routeur R10 = {{6,8},"KeyUp"};
            ensembleRouteurs.push_back(R10);
            routeur R11 = {{8,18},"KeyUp"};
            ensembleRouteurs.push_back(R11);
            routeur R12 = {{8,20},"KeyLeft"};
            ensembleRouteurs.push_back(R12);
            routeur R13 = {{10,8},"KeyUp"};
            ensembleRouteurs.push_back(R13);
            routeur R16 = {{10,30},"KeyLeft"};
            ensembleRouteurs.push_back(R16);
            routeur R17 = {{10,16},"KeyRight"};
            ensembleRouteurs.push_back(R17);
            routeur R18 = {{10,22},"KeyLeft"};
            ensembleRouteurs.push_back(R18);
            routeur R19 = {{14,8},"KeyUp"};
            ensembleRouteurs.push_back(R19);
            routeur R20 = {{14,12},"KeyLeft"};
            ensembleRouteurs.push_back(R20);
            routeur R21 = {{14,26},"KeyUp"};
            ensembleRouteurs.push_back(R21);
            routeur R22 = {{14,30},"KeyUp"};
            ensembleRouteurs.push_back(R22);
            routeur R23 = {{16,8},"KeyUp"};
            ensembleRouteurs.push_back(R23);
            routeur R24 = {{16,12},"KeyLeft"};
            ensembleRouteurs.push_back(R24);
            routeur R25 = {{16,18},"KeyUp"};
            ensembleRouteurs.push_back(R25);
            routeur R26 = {{16,20},"KeyLeft"};
            ensembleRouteurs.push_back(R26);
            routeur R27 = {{16,26},"KeyLeft"};
            ensembleRouteurs.push_back(R27);
            routeur R28 = {{16,30},"KeyUP"};
            ensembleRouteurs.push_back(R28);
            routeur R29 = {{18,6},"KeyRight"};
            ensembleRouteurs.push_back(R29);
            routeur R30 = {{18,32},"KeyRight"};
            ensembleRouteurs.push_back(R30);
            routeur R31 = {{20,18},"KeyUp"};
            ensembleRouteurs.push_back(R31);
            routeur R32 = {{20,20},"KeyUp"};
            ensembleRouteurs.push_back(R32);
            size_t indiceRouteur = 0;

            while (unJoueur.vivant) {
                if (unJoueur.modeMange){
                    cptMange = 70;
                }
                // Variable qui tient le temps de frame
                chrono::microseconds frameTime = chrono::microseconds::zero();
                // Récupère l'heure actuelle
                chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

                // On efface la fenêtre
                window.clearScreen();


                // On regarde les touches pressés par le joueur
                appuiTouches(window,unJoueur,parametres);

                // On effectue le mouvement du joueur
                bool modeMouvementEnAttente = true;
                mouvementJoueur(unJoueur,carte1,score,modeMouvementEnAttente);

                miseAJourMorts(unJoueur,ensembleEngloutisseur);


                // Si le joueur est sur un routeur, on met a jour la direction du routeur
                if (joueurSurRouteur){
                    joueurDirection(unJoueur,ensembleRouteurs[indiceRouteur]);
                    joueurSurRouteur = false;
                }

                // On regarde si un joueur est au même endroit qu'un routeur
                for (size_t i = 0; i < ensembleRouteurs.size() ; ++i){
                    if (unJoueur.coordonnees == ensembleRouteurs[i].coordonnees){
                        joueurSurRouteur = true;
                        indiceRouteur = i;
                    }
                }


                cout << engloutisseurUn.direction <<endl;

                // On effectue le mouvement des engloutisseurs
                for (size_t i = 0; i < ensembleEngloutisseur.size(); ++i) {
                    if (ensembleEngloutisseur[i].immobilisation == 0){
                        ensembleEngloutisseur[i] = mouvementEngloutisseur(ensembleEngloutisseur[i],carte1);
                    }
                    else{
                        ensembleEngloutisseur[i].immobilisation -= 1;
                    }
                }

                miseAJourMorts(unJoueur,ensembleEngloutisseur);
                // On regarde si un engloutisseur est au même endroit qu'un routeur
                for (size_t i = 0; i < ensembleEngloutisseur.size(); ++i) {
                    for (size_t j = 0; j < ensembleRouteurs.size() ; ++j){
                        if (ensembleEngloutisseur[i].coordonnees == ensembleRouteurs[j].coordonnees){
                            bool respect = respectIndicationRouteur(ensembleEngloutisseur[i]);
                            if (!respect){
                                changeDirectionAleatoire(ensembleEngloutisseur[i]);
                            }
                            else{
                                changeDirection(ensembleEngloutisseur[i],ensembleRouteurs[j]);
                            }
                        }
                    }
                }

                if (cptMange > 0){
                    --cptMange;
                }
                // On augmente la dangerosité du jeu
                compteurDangerosite = miseAJourDangerosite(compteurDangerosite, ensembleEngloutisseur);
                cout << engloutisseurUn.direction<< ' ' << engloutisseurUn.coordonnees.first << ' ' << engloutisseurUn.coordonnees.second << endl;

                // On affiche les modifications
                afficherCarte(window, carte1, unJoueur,score, ensembleEngloutisseur);

                // for(unsigned y = 0; y < carte1.size(); ++y){
                //     for(unsigned x = 0; x < carte1[y].size(); ++x){
                //         if(carte1[y][x] == '#'){
                //             cout << '#';
                //         }
                //         else if(carte1[y][x] == '*'){
                //             cout << '*';
                //         }
                //         else if(carte1[y][x] == '0'){
                //             cout << '0';
                //         }
                //         else if(carte1[y][x] == ' '){
                //             cout << ' ';
                //         }
                //     }
                //     cout << endl;
                // }
                // cout << endl;
                // cout << score << endl;


                // On finit la frame en cours
                window.finishFrame();

                // On vide la queue d'évènements
                window.getEventManager().clearEvents();

                // On attend un peu pour limiter le framerate et soulager le CPU
                this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

                // On récupère le temps de frame
                frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
            }
            cout << nbVies << endl;
            --nbVies;
        }
        break;
    }
}
