/**
 * @file JoueurHumain.hpp
 * @author Djamaël Lahamion
 * @author Eloi Tourangin
 * @author Lucas Oros
 * @author Aloïs Guillon
 *
 * @brief Définition de la classe JoueurHumain pour le jeu Otrio
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include "Joueur.hpp"
#include <iostream>
#include <limits>

using namespace std;

/**
 * @brief Classe représentant un joueur humain
 *
 * La classe JoueurHumain hérite de la classe abstraite Joueur.
 * Elle implémente la méthode jouerCoup() en interagissant
 * directement avec l’utilisateur via l’entrée standard.
 *
 * Le joueur humain :
 * - choisit la taille du pion à jouer parmi ceux disponibles,
 * - saisit les coordonnées de la case,
 * - valide le coup selon les règles du plateau.
 */
class JoueurHumain : public Joueur
{
public:
    /**
     * @brief Constructeur de la classe JoueurHumain
     *
     * @param nom nom du joueur
     * @param couleur couleur associée au joueur
     */
    JoueurHumain(string nom, Couleur couleur);

    /**
     * @brief Destructeur de la classe JoueurHumain
     */
    ~JoueurHumain();

    /**
     * @brief Permet au joueur humain de jouer un coup
     *
     * Cette méthode :
     * - affiche la main du joueur,
     * - demande la taille du pion à jouer,
     * - demande les coordonnées de placement,
     * - vérifie la validité du coup via le plateau.
     *
     * @param plateau pointeur vers le plateau de jeu
     * @return true si le coup a été joué avec succès
     * @return false si le coup est invalide
     */
    bool jouerCoup(Plateau* plateau) override;
};
