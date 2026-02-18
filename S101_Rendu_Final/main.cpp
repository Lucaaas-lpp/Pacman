#include "Jeu_Luma/jeu.h"
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
    system("xdg-open ../lumaLore.mp4 &");
    cout << "Bienvenue sur Luma, Choisissez votre jeu" << endl << "Luma Aventure : X" << '\t' << "Luma Janus : W" << endl;
    char choix;
    cout << "saisissez votre choix :";
    cin >> choix;
    switch(choix){
    case 'x':
        jeuAventure();
    case 'w':
        jeuJanus();
    }
    return 0;
}
