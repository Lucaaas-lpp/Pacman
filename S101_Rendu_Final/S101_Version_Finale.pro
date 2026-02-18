TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
include(mingl/mingl.pri)
SOURCES += \
        Jeu_Luma/ennemi.cpp \
        Jeu_Luma/jeu.cpp \
        Jeu_Luma/joueur.cpp \
        Jeu_Luma/parametre.cpp \
        Jeu_Luma/routeur.cpp \
        main.cpp

HEADERS += \
    Jeu_Luma/ennemi.h \
    Jeu_Luma/jeu.h \
    Jeu_Luma/joueur.h \
    Jeu_Luma/parametre.h \
    Jeu_Luma/routeur.h \
    Jeu_Luma/type.h \
