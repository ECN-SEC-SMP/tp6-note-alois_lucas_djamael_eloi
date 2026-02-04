/**
 * @file Pion.hpp
 * @author Aloïs Guillon
 * @author Djamaël Lahamion
 * @author Eloi Tourangin
 * @author Lucas Oros
 *
 * @brief Définition de la classe Pion utilisée dans le jeu Otrio
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <string>

using namespace std;

/**
 * @brief Énumération représentant la couleur d’un pion
 *
 * Chaque joueur est associé à une couleur unique.
 */
enum Couleur
{
    ROUGE,
    VERT,
    BLEU,
    JAUNE
};

/**
 * @brief Énumération représentant la taille d’un pion
 *
 * Les tailles sont ordonnées de la plus petite à la plus grande.
 */
enum Taille
{
    PETIT,
    MOYEN,
    GRAND
};

/**
 * @brief Classe représentant un pion du jeu Otrio
 *
 * Un pion est caractérisé par :
 * - une couleur (appartenant à un joueur),
 * - une taille (PETIT, MOYEN ou GRAND).
 *
 * Les pions sont empilables dans les cases du plateau,
 * sous réserve des règles du jeu.
 */
class Pion
{
private:
    Couleur couleur; /**< Couleur du pion */
    Taille taille;   /**< Taille du pion */

public:
    /**
     * @brief Constructeur de la classe Pion
     *
     * @param couleur couleur du pion
     * @param taille taille du pion
     */
    Pion(Couleur couleur, Taille taille);

    /**
     * @brief Retourne la couleur du pion
     *
     * @return Couleur du pion
     */
    Couleur getCouleur() const;

    /**
     * @brief Retourne la taille du pion
     *
     * @return Taille du pion
     */
    Taille getTaille() const;

    /**
     * @brief Retourne la taille du pion sous forme de chaîne
     *
     * @return string "PETIT", "MOYEN" ou "GRAND"
     */
    string getTailleStr() const;

    /**
     * @brief Retourne la couleur du pion sous forme de chaîne
     *
     * @return string "ROUGE", "VERT", "BLEU" ou "JAUNE"
     */
    string getCouleurStr() const;
};
