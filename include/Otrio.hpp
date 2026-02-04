/**
 * @file Otrio.hpp
 * @author
 *  Aloïs Guillon (alois.guillon@eleves.ec-nantes.fr)
 *  Lucas Oros (lucas.oros@eleves.ec-nantes.fr)
 *  Djamaël Lahamion (djamael.lahamion@eleves.ec-nantes.fr)
 *  Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr)
 *
 * @brief Définition de la classe principale Otrio, responsable du déroulement
 *        complet d'une partie (initialisation, boucle de jeu, victoire, affichage).
 *
 * @version 0.3
 * @date 30-01-2026
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

#include "Joueur.hpp"
#include "Joueurhumain.hpp"
#include "JoueurIA.hpp"
#include "Plateau.hpp"

using namespace std;

/**
 * @brief Classe principale du jeu Otrio
 *
 * Cette classe orchestre :
 *  - la gestion du plateau
 *  - la gestion des joueurs (humains et IA)
 *  - le déroulement des tours
 *  - la détection de fin de partie
 *
 * Elle supporte plusieurs modes de jeu :
 *  - mode 0 : 4 joueurs humains
 *  - mode 1 : 2 joueurs humains (2 couleurs chacun)
 *  - mode 3 : joueurs humains + joueurs IA
 */
class Otrio
{
protected:
    /**
     * @brief Plateau de jeu (grille 3x3 contenant les cases)
     */
    Plateau plateau;

    /**
     * @brief Liste polymorphe des joueurs
     *
     * Permet de stocker à la fois des JoueurHumain et des JoueurIA
     * grâce à l'héritage et aux pointeurs intelligents.
     */
    vector<unique_ptr<Joueur>> joueurs;

    /**
     * @brief Index du joueur courant dans le vecteur joueurs
     */
    int joueurCourantIndex;

    /**
     * @brief Mode de jeu courant
     *
     * 0 : 4 joueurs humains  
     * 1 : 2 joueurs humains (2 couleurs chacun)  
     * 3 : présence de joueurs IA  
     */
    int mode;

public:
    /**
     * @brief Constructeur par défaut
     *
     * Initialise le plateau, les joueurs par défaut et
     * positionne le premier joueur courant.
     */
    Otrio(void);

    /**
     * @brief Destructeur
     */
    ~Otrio();

    /**
     * @brief Initialise une nouvelle partie
     *
     * Crée les joueurs selon le mode sélectionné, réinitialise
     * le plateau et prépare la boucle de jeu.
     *
     * @param mode mode de jeu (0, 1 ou 3)
     */
    void initialiserPartie(int mode = 0);

    /**
     * @brief Lance la boucle principale du jeu
     *
     * Gère l'alternance des tours, les coups des joueurs,
     * l'affichage graphique et l'arrêt de la partie.
     */
    void lancerBoucleJeu();

    /**
     * @brief Affiche l'état courant du jeu dans le terminal
     *
     * Affiche le plateau et les informations sur les joueurs
     * (nom, couleur, pions restants).
     */
    void afficherEtatJeu() const;

    /**
     * @brief Passe au joueur suivant
     *
     * Met à jour l'index du joueur courant en fonction du mode.
     *
     * @return true si le changement est effectué
     */
    bool passerAuJoueurSuivant();

    /**
     * @brief Vérifie si la partie est terminée
     *
     * La partie se termine si :
     *  - un joueur a gagné
     *  - aucun joueur ne peut jouer
     *
     * @return true si la partie est finie
     */
    bool estFini() const;

    /**
     * @brief Accès en lecture au plateau (pour l'affichage graphique)
     *
     * @return référence constante vers le plateau
     */
    const Plateau& getPlateau() const { return plateau; }

    /**
     * @brief Accès à la liste des joueurs (sans transfert de propriété)
     *
     * Utilisé notamment par la classe Affichage pour afficher
     * les mains des joueurs.
     *
     * @return référence constante vers le vecteur de joueurs
     */
    const vector<unique_ptr<Joueur>>& getJoueurs() const { return joueurs; }

    /**
     * @brief Récupère l'index du joueur courant
     *
     * @return index du joueur courant
     */
    int getJoueurCourantIndex() const { return joueurCourantIndex; }

    /**
     * @brief Récupère le mode de jeu courant
     *
     * @return mode de jeu
     */
    int getMode() const { return mode; }
};
