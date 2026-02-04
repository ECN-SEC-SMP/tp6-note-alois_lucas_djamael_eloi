/**
 * @file Case.hpp
 * @author
 * @brief Déclaration de la classe Case représentant une case du plateau Otrio
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "Pion.hpp"   // Définit Pion, Couleur et Taille
#include <cstddef>    // nullptr

using namespace std;

/**
 * @brief Classe représentant une case du plateau de jeu Otrio
 *
 * Une case peut contenir jusqu'à trois pions superposés,
 * un par taille (PETIT, MOYEN, GRAND).
 * Chaque emplacement est indépendant et ne peut contenir
 * qu’un seul pion de la taille correspondante.
 */
class Case
{
private:
    /**
     * @brief Tableau des emplacements de pions
     *
     * Index :
     * - 0 : pion PETIT
     * - 1 : pion MOYEN
     * - 2 : pion GRAND
     *
     * Un pointeur nullptr indique que l’emplacement est vide.
     */
    Pion *emplacements[3];

public:
    /**
     * @brief Constructeur par défaut
     *
     * Initialise tous les emplacements de la case à nullptr (case vide).
     */
    Case();

    /**
     * @brief Place un pion sur la case
     *
     * Le pion est placé dans l’emplacement correspondant à sa taille.
     *
     * @param pion Pointeur vers le pion à placer
     * @return true si le pion a été placé avec succès
     * @return false si l’emplacement est déjà occupé ou si pion == nullptr
     */
    bool placerPion(Pion *pion);

    /**
     * @brief Retire un pion de la case
     *
     * Retire et renvoie le pion correspondant à la taille demandée.
     *
     * @param taille Taille du pion à retirer
     * @return Pion* pointeur vers le pion retiré, ou nullptr si l’emplacement est vide
     */
    Pion *retirerPion(Taille taille);

    /**
     * @brief Accède à un pion présent sur la case
     *
     * @param taille Taille du pion recherché
     * @return Pion* pointeur vers le pion, ou nullptr s’il n’existe pas
     */
    Pion *getPion(Taille taille) const;

    /**
     * @brief Indique si un emplacement est vide
     *
     * @param taille Taille de l’emplacement à tester
     * @return true si aucun pion n’est présent
     * @return false si un pion est présent
     */
    bool estVide(Taille taille) const;
};
