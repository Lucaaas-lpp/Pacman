# Pacman - Projet C++ (BUT 1)

> **Projet étudiant** réalisé dans le cadre de la 1ère année de BUT Informatique (Module S1.01 - Développement d'une application).

## Présentation

Ce projet est une réinterprétation du célèbre jeu **Pacman**, développée en C++ avec l'utilisation de la bibliothèque graphique simplifiée **MinGL** (Minimum Graphical Library).

L'objectif n'était pas de créer un jeu commercialisable, mais d'apprendre les concepts fondamentaux de la **Programmation Orientée Objet (POO)** :
* Classes et Objets
* Héritage et Polymorphisme (ex: Gestion des entités comme Pacman et les Fantômes)
* Gestion des événements (Clavier)
* Travail en équipe et gestion de versions (Git)

## Stack Technique

* **Langage :** C++
* **Graphisme :** MinGL (Librairie pédagogique basée sur OpenGL/Qt)
* **IDE recommandé :** Qt Creator

## Fonctionnalités implémentées

Cette version, présentée devant le jury, comprend :
* Déplacement du personnage principal.
* Gestion des collisions avec les murs (labyrinthe).
* Système de score (Manger les pac-gommes).
* Affichage d'un menu principal et d'un écran de fin.
* Intégration d'effets sonores.

## État du projet et Limitations

Ce projet est laissé dans son état de "rendu final" de première année pour témoigner de mon niveau à cette époque. Il comporte plusieurs axes d'amélioration identifiés avec le recul :
1.  **IA des Fantômes :** Le comportement des ennemis est basique et mériterait l'implémentation d'algorithmes de pathfinding (A* ou Dijkstra).
2.  **Optimisation :** La gestion de l'affichage pourrait être optimisée pour éviter certains ralentissements.
3.  **Architecture :** Certaines classes sont fortement couplées, ce qui rendrait l'ajout de nouvelles fonctionnalités complexe sans refactoring.

## Structure du projet

* `src/` : Contient le code source du jeu.
* `mingl/` : Les sources de la librairie graphique utilisée.
* `assets/` : Images, sons et polices.

## Auteurs

Projet réalisé en équipe par :
* Lucas Lepape et l'équipe Pacman
