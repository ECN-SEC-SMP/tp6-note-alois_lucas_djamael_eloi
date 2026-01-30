/**
 * @file Affichage.cpp
 * @author Eloi Tourangin (Eloi.Tourangin@eleves.ec-nantes.fr)
 * @brief Implémentation du rendu graphique pour le jeu Otrio
 * @version 0.2
 * @date 30-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "Affichage.hpp"
#include "Plateau.hpp"
#include "Joueur.hpp"
#include "Case.hpp"
#include "Pion.hpp"
#include "Otrio.hpp"
#include "JoueurHumain.hpp"
#include <sstream>

// Initialisation des membres statiques
sf::RenderWindow *Affichage::window = nullptr;
sf::Font *Affichage::font = nullptr;

// Constructeur privé
Affichage::Affichage() {}

sf::Color Affichage::couleurToSfColor(Couleur couleur)
{
    switch (couleur)
    {
    case ROUGE:
        return sf::Color(230, 50, 50);
    case VERT:
        return sf::Color(50, 200, 50);
    case BLEU:
        return sf::Color(50, 100, 230);
    case JAUNE:
        return sf::Color(255, 220, 0);
    default:
        return sf::Color::Black;
    }
}

std::string Affichage::couleurToString(Couleur couleur)
{
    switch (couleur)
    {
    case ROUGE:
        return "ROUGE";
    case VERT:
        return "VERT";
    case BLEU:
        return "BLEU";
    case JAUNE:
        return "JAUNE";
    default:
        return "INCONNU";
    }
}

std::string Affichage::tailleToString(Taille taille)
{
    switch (taille)
    {
    case PETIT:
        return "P";
    case MOYEN:
        return "M";
    case GRAND:
        return "G";
    default:
        return "?";
    }
}

bool Affichage::chargerPolice()
{
    if (font != nullptr)
        return true; // Déjà chargée

    font = new sf::Font();
    std::vector<std::string> cheminsPolice = {
        "C:\\Windows\\Fonts\\arial.ttf",
        "C:\\Windows\\Fonts\\ARIAL.TTF",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/System/Library/Fonts/Arial.ttf",
        "arial.ttf"
    };

    for (const auto &chemin : cheminsPolice)
    {
        if (font->loadFromFile(chemin))
        {
            std::cout << "[INFO] Police chargée: " << chemin << std::endl;
            return true;
        }
    }

    std::cerr << "[ERREUR] Police introuvable." << std::endl;
    delete font;
    font = nullptr;
    return false;
}

void Affichage::dessinerPion(float x, float y, const Pion *pion, float rayon)
{
    if (!window)
        return;

    sf::CircleShape circle(rayon);
    circle.setOrigin(rayon, rayon);
    circle.setPosition(x, y);
    circle.setOutlineThickness(2.5f);

    if (pion)
    {
        circle.setOutlineColor(couleurToSfColor(pion->getCouleur()));
    }
    else
    {
        circle.setOutlineThickness(1.0f);
        circle.setOutlineColor(sf::Color(200, 200, 200));
    }

    circle.setFillColor(sf::Color::Transparent);
    window->draw(circle);
}

void Affichage::dessinerCase(float x, float y, const Case *cas)
{
    if (!window)
        return;

    // Fond de la case
    sf::RectangleShape rect(sf::Vector2f(CASE_SIZE, CASE_SIZE));
    rect.setPosition(x, y);
    rect.setOutlineThickness(2.0f);
    rect.setOutlineColor(sf::Color(100, 100, 100));
    rect.setFillColor(sf::Color(245, 245, 245));
    window->draw(rect);

    if (!cas)
        return;

    float centerX = x + CASE_SIZE / 2.0f;
    float centerY = y + CASE_SIZE / 2.0f;

    dessinerPion(centerX, centerY, cas->getPion(GRAND), RAYON_GRAND);
    dessinerPion(centerX, centerY, cas->getPion(MOYEN), RAYON_MOYEN);
    dessinerPion(centerX, centerY, cas->getPion(PETIT), RAYON_PETIT);
}

void Affichage::dessinerGrillePlateau(const Plateau &plateau)
{
    if (!window)
        return;

    // Cadre général du plateau
    sf::RectangleShape cadrePlateau(sf::Vector2f(PLATEAU_SIZE, PLATEAU_SIZE));
    cadrePlateau.setPosition(MARGIN_PLATEAU, MARGIN_PLATEAU);
    cadrePlateau.setFillColor(sf::Color::White); // Fond blanc derrière les cases
    cadrePlateau.setOutlineThickness(3.0f);
    cadrePlateau.setOutlineColor(sf::Color(50, 50, 50));
    window->draw(cadrePlateau);

    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            float posX = MARGIN_PLATEAU + x * CASE_SIZE;
            float posY = MARGIN_PLATEAU + y * CASE_SIZE;

            Case *cas = const_cast<Plateau &>(plateau).getCase(x, y);
            dessinerCase(posX, posY, cas);

            if (font)
            {
                sf::Text coordText;
                coordText.setFont(*font);
                coordText.setString("(" + std::to_string(x) + "," + std::to_string(y) + ")");
                coordText.setCharacterSize(12);
                coordText.setFillColor(sf::Color(150, 150, 150));
                coordText.setPosition(posX + 5, posY + 5);
                window->draw(coordText);
            }
        }
    }
}

void Affichage::afficherMainJoueur(const Joueur *joueur, float x, float y, bool estJoueurCourant)
{
    if (!joueur || !window || !font)
        return;

    // 1. Compter les pions restants
    std::vector<Pion *> pions = joueur->getPionRestants();
    int nbGrands = 0;
    int nbMoyens = 0;
    int nbPetits = 0;

    for (auto *p : pions)
    {
        if (!p)
            continue;
        switch (p->getTaille())
        {
        case GRAND:
            nbGrands++;
            break;
        case MOYEN:
            nbMoyens++;
            break;
        case PETIT:
            nbPetits++;
            break;
        default:
            break;
        }
    }

    // 2. Fond et Nom
    sf::RectangleShape fond(sf::Vector2f(250.0f, 160.0f));
    fond.setPosition(x, y);
    fond.setFillColor(estJoueurCourant ? sf::Color(230, 255, 230) : sf::Color(245, 245, 245));
    fond.setOutlineThickness(estJoueurCourant ? 3.0f : 1.0f);
    fond.setOutlineColor(estJoueurCourant ? sf::Color(0, 180, 0) : sf::Color(150, 150, 150));
    window->draw(fond);

    sf::Text nomText;
    nomText.setFont(*font);
    nomText.setString(joueur->getNom());
    nomText.setCharacterSize(18);
    nomText.setFillColor(couleurToSfColor(joueur->getCouleur()));
    nomText.setPosition(x + 10, y + 5);
    if (estJoueurCourant)
        nomText.setStyle(sf::Text::Bold);
    window->draw(nomText);

    // 3. Dessiner les 3 emplacements concentriques
    for (int i = 0; i < 3; ++i)
    {
        float centerX = x + MAIN_START_X + (i * MAIN_SPACING_X);
        float centerY = y + MAIN_CENTER_Y;

        // --- Grand ---
        if (nbGrands > 0)
        {
            sf::CircleShape g(RAYON_GRAND * MAIN_SCALE);
            g.setOrigin(RAYON_GRAND * MAIN_SCALE, RAYON_GRAND * MAIN_SCALE);
            g.setPosition(centerX, centerY);
            g.setOutlineThickness(2.0f);
            g.setOutlineColor(couleurToSfColor(joueur->getCouleur()));
            g.setFillColor(sf::Color::Transparent);
            window->draw(g);
            nbGrands--;
        }
        else
        {
            // Emplacement vide (gris clair)
            sf::CircleShape g(RAYON_GRAND * MAIN_SCALE);
            g.setOrigin(RAYON_GRAND * MAIN_SCALE, RAYON_GRAND * MAIN_SCALE);
            g.setPosition(centerX, centerY);
            g.setOutlineThickness(1.0f);
            g.setOutlineColor(sf::Color(220, 220, 220));
            g.setFillColor(sf::Color::Transparent);
            window->draw(g);
        }

        // --- Moyen ---
        if (nbMoyens > 0)
        {
            sf::CircleShape m(RAYON_MOYEN * MAIN_SCALE);
            m.setOrigin(RAYON_MOYEN * MAIN_SCALE, RAYON_MOYEN * MAIN_SCALE);
            m.setPosition(centerX, centerY);
            m.setOutlineThickness(2.0f);
            m.setOutlineColor(couleurToSfColor(joueur->getCouleur()));
            m.setFillColor(sf::Color::Transparent);
            window->draw(m);
            nbMoyens--;
        }

        // --- Petit ---
        if (nbPetits > 0)
        {
            sf::CircleShape p(RAYON_PETIT * MAIN_SCALE);
            p.setOrigin(RAYON_PETIT * MAIN_SCALE, RAYON_PETIT * MAIN_SCALE);
            p.setPosition(centerX, centerY);
            p.setOutlineThickness(2.0f);
            p.setOutlineColor(couleurToSfColor(joueur->getCouleur()));
            p.setFillColor(sf::Color::Transparent); // Fond transparent
            window->draw(p);
            nbPetits--;
        }
    }
}

void Affichage::traiterEvenements()
{
    if (!window)
        return;
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            fermer();
        }
    }
}

void Affichage::afficherPlateau(const Plateau &plateau,
                                const std::vector<Joueur *> &joueurs,
                                int joueurCourantIndex)
{
    // 1. Initialisation unique
    if (!window)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8; // Pour des cercles plus lisses
        window = new sf::RenderWindow(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "OTRIO - C++", sf::Style::Default, settings);
        window->setFramerateLimit(60);
    }

    if (!chargerPolice())
        return;

    // 2. Gestion des événements
    traiterEvenements();
    if (!window || !window->isOpen())
        return;

    // 3. Rendu
    window->clear(sf::Color::White);

    // Titre
    sf::Text titre;
    titre.setFont(*font);
    titre.setString("OTRIO");
    titre.setCharacterSize(32);
    titre.setFillColor(sf::Color::Black);
    titre.setPosition(MARGIN_PLATEAU, 10);
    window->draw(titre);

    // Dessiner le plateau
    dessinerGrillePlateau(plateau);

    // Dessiner les mains des joueurs
    float mainStartX = MARGIN_PLATEAU + PLATEAU_SIZE + 50;
    float mainStartY = MARGIN_PLATEAU;

    for (size_t i = 0; i < joueurs.size(); ++i)
    {
        if (joueurs[i])
        {
            afficherMainJoueur(joueurs[i], mainStartX, mainStartY + i * 200, (int)i == joueurCourantIndex);
        }
    }

    window->display();
}

void Affichage::afficherPlateau(Otrio *otrio)
{
    if (!otrio)
        return;

    std::vector<Joueur *> joueursPtr;
    auto &joueursRef = otrio->getJoueurs();
    for (size_t i = 0; i < joueursRef.size(); ++i)
    {
        joueursPtr.push_back((Joueur *)&joueursRef[i]);
    }

    afficherPlateau(otrio->getPlateau(), joueursPtr, otrio->getJoueurCourantIndex());
}

bool Affichage::estActif()
{
    return window != nullptr && window->isOpen();
}

void Affichage::fermer()
{
    if (window)
    {
        window->close();
        delete window;
        window = nullptr;
    }
    if (font)
    {
        delete font;
        font = nullptr;
    }
}