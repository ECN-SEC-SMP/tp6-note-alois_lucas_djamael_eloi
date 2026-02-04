/**
 * @file Joueur.hpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr)
 * @author Lucas Oros (lucas.oros@eleves.ec-nantes.fr)
 * @author Djamael Lahamion (djamael.lahamion@eleves.ec-nantes.fr)
 * @author Aloïs Guillon (alois.guillon@eleves.ec-nantes.fr)
 *
 * @brief Déclaration de la classe abstraite Joueur
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Pion.hpp"
#include "Plateau.hpp"

class Plateau;

/**
 * @def NB_PIONS_PAR_TAILLE
 * @brief Nombre de pions par taille pour un joueur
 */
#define NB_PIONS_PAR_TAILLE 3

/**
 * @def NB_GROUPES_PIONS
 * @brief Nombre de tailles différentes de pions
 */
#define NB_GROUPES_PIONS    3

using namespace std;

/**
 * @brief Classe abstraite représentant un joueur du jeu Otrio
 *
 * Cette classe définit les attributs et comportements communs
 * à tous les joueurs (humains ou IA).
 * Elle est destinée à être héritée.
 */
class Joueur
{
protected:
    /**
     * @brief Nom du joueur
     */
    string nom;

    /**
     * @brief Couleur associée au joueur
     */
    Couleur couleur;

    /**
     * @brief Liste des pions encore disponibles dans la main du joueur
     */
    vector<Pion*> main;

public:
    /**
     * @brief Constructeur de la classe Joueur
     *
     * Initialise le joueur avec un nom, une couleur
     * et génère l'ensemble de ses pions.
     *
     * @param nom Nom du joueur
     * @param couleur Couleur du joueur
     */
    Joueur(string nom, Couleur couleur);

    /**
     * @brief Destructeur de la classe Joueur
     */
    ~Joueur();

    /**
     * @brief Récupère le nom du joueur
     *
     * @return string Nom du joueur
     */
    string getNom() const;

    /**
     * @brief Récupère la couleur du joueur
     *
     * @return Couleur Couleur du joueur
     */
    Couleur getCouleur() const;

    /**
     * @brief Récupère la liste des pions restants dans la main
     *
     * @return vector<Pion*> Liste des pions disponibles
     */
    vector<Pion*> getPionRestants() const;

    /**
     * @brief Affiche les pions encore disponibles dans la main du joueur
     */
    void afficherMain() const;

    /**
     * @brief Retire un pion de la main du joueur
     *
     * @param p Pion à retirer
     */
    void retirerPionDeMain(Pion* p);

    /**
     * @brief Joue un coup sur le plateau
     *
     * Méthode virtuelle pure à implémenter dans les classes filles
     * (JoueurHumain, JoueurIA).
     *
     * @param plateau Plateau de jeu
     * @return true si le coup est valide
     * @return false sinon
     */
    virtual bool jouerCoup(Plateau* plateau) = 0;
};
