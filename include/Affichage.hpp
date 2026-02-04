/**
 * @file Affichage.hpp
 * @author Eloi Tourangin (Eloi.Tourangin@eleves.ec-nantes.fr)
 * @brief Interface graphique du jeu Otrio
 * @version 0.2
 * @date 30-01-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "Pion.hpp"

// Forward declarations
class Plateau;
class Joueur;
class Case;
class Otrio;

class Affichage {
private:
    // --- Membres Statiques (remplacent les globales) ---
    static sf::RenderWindow* window;
    static sf::Font* font;

    // --- Paramètres graphiques ---
    static constexpr float WINDOW_WIDTH = 1600.0f;
    static constexpr float WINDOW_HEIGHT = 1000.0f;
    static constexpr float PLATEAU_SIZE = 600.0f;
    static constexpr float CASE_SIZE = 200.0f;
    static constexpr float MARGIN_PLATEAU = 50.0f;
    
    // Rayons
    static constexpr float RAYON_PETIT = 15.0f;
    static constexpr float RAYON_MOYEN = 35.0f;
    static constexpr float RAYON_GRAND = 55.0f;
    static constexpr float MAIN_CIRCLE_RAYON = 20.0f;
    static constexpr float MAIN_SPACING = 35.0f;

    // Main des joueurs
    static constexpr float MAIN_SCALE = 0.6f; 
    
    static constexpr float MAIN_SPACING_X = 70.0f; // Espacement horizontal
    static constexpr float MAIN_START_X = 55.0f;   // Décalage du premier groupe
    static constexpr float MAIN_CENTER_Y = 100.0f; // Hauteur des cercles dans la boîte

    // Constructeur privé pour empêcher l'instanciation
    Affichage();

    static sf::Color couleurToSfColor(Couleur couleur);
    static std::string couleurToString(Couleur couleur);
    static std::string tailleToString(Taille taille);
    
    static void dessinerCase(float x, float y, const Case* cas);
    static void dessinerPion(float x, float y, const Pion* pion, float rayon);
    static void dessinerGrillePlateau(const Plateau& plateau);
    static void afficherMainJoueur(const Joueur* joueur, float x, float y, bool estJoueurCourant);
    static bool chargerPolice();
    static void traiterEvenements(); // Pour empêcher le gel de la fenêtre

public:    
    static void afficherPlateau(const Plateau& plateau, 
                                const std::vector<Joueur*>& joueurs,
                                int joueurCourantIndex = -1);

    static void afficherPlateau(Otrio* otrio);
    static bool estActif();
    static void fermer();
};