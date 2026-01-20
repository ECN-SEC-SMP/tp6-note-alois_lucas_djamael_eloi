/**
 * @file Pion.hpp
 * @author Aloïs GUILLON (alois.guillon@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 2026-01-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

enum Couleur
{
    ROUGE,
    VERT,
    BLEU,
    JAUNE
};

enum Taille
{
    PETIT,
    MOYEN,
    GRAND
};

class Pion
{
private:
    Couleur couleur;
    Taille taille;

public:
    Pion(Couleur, Taille);

    Couleur getCouleur();

    Taille getTaille();
};