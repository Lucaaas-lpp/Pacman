#include "parametre.h"
#include <string>
#include <map>

using namespace std;

map<string,char> initParams1(){
    map<string,char> params;
    params["KeyUp"] = 'z';
    params["KeyDown"] = 's';
    params["KeyLeft"] = 'q';
    params["KeyRight"] = 'd';
    params["KeyPower"] = 'a'; //mettre un pouvoir
    return params;
}

map<string,char> initParams2(){
    map<string,char> params;
    params["KeyUp"] = 'o';
    params["KeyDown"] = 'l';
    params["KeyLeft"] = 'k';
    params["KeyRight"] = 'm';
    params["KeyPower"] = 'i'; //mettre un pouvoir
    return params;
}
