/**
 * @file JoueurIA.hpp
 * @author
 * @brief Déclaration de la classe JoueurIA, représentant un joueur contrôlé par une intelligence artificielle
 * @version 0.1
 * @date 2026-01-30
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "Joueur.hpp"
#include <vector>
#include <array>
#include <limits>

/**
 * @brief Classe représentant un joueur IA pour le jeu Otrio
 *
 * Cette classe hérite de Joueur et implémente une intelligence artificielle
 * capable de :
 *  - détecter des victoires immédiates,
 *  - bloquer les menaces adverses,
 *  - planifier plusieurs coups à l’avance grâce à une recherche de type minimax.
 */
class JoueurIA : public Joueur
{
private:
    /**
     * @brief Représentation interne du plateau
     *
     * board[y][x][t] :
     *  - -1 si l’emplacement est vide
     *  - sinon valeur entière correspondant à une Couleur
     */
    using Board = std::array<std::array<std::array<int, 3>, 3>, 3>;

    /**
     * @brief Structure représentant un coup possible
     *
     * x, y : coordonnées sur le plateau  
     * t    : taille du pion à jouer
     */
    struct Move {
        int x;
        int y;
        Taille t;
    };

    /// Liste des joueurs de la partie (ordre réel de jeu)
    std::vector<Joueur*> joueurs_;

    /// Index de cette IA dans le tableau des joueurs
    int myIndex_ = -1;

    /* ================= Construction de l’état ================= */

    /**
     * @brief Lit l’état actuel du plateau et le convertit en Board
     *
     * @param plateau pointeur vers le plateau de jeu
     * @return Board représentation interne du plateau
     */
    Board lirePlateau(const Plateau* plateau) const;

    /**
     * @brief Lit le stock de pions restants par couleur
     *
     * @return tableau contenant le nombre de pions PETIT, MOYEN et GRAND
     *         pour chaque joueur
     */
    std::array<std::array<int,3>, 8> lireStocksParCouleur() const;

    /* ================= Gestion des menaces ================= */

    /**
     * @brief Recherche un coup gagnant immédiat pour l’IA
     *
     * @param b état du plateau
     * @param best coup gagnant trouvé
     * @return true si un coup gagnant existe
     */
    bool trouverCoupPourGagner(const Board& b, Move& best) const;

    /**
     * @brief Recherche un coup permettant de bloquer une victoire adverse
     *
     * @param b état du plateau
     * @param best coup bloquant trouvé
     * @return true si une menace est détectée
     */
    bool trouverCoupPourBloquer(const Board& b, Move& best) const;

    /* ================= Recherche et évaluation ================= */

    /**
     * @brief Évalue un état du plateau pour l’IA
     *
     * Plus la valeur est élevée, plus la position est favorable à l’IA.
     *
     * @param b état du plateau
     * @return score heuristique
     */
    int eval(const Board& b) const;

    /**
     * @brief Vérifie si une couleur donnée a gagné sur un état du plateau
     *
     * @param b état du plateau
     * @param c couleur à tester
     * @return true si la couleur a une condition de victoire
     */
    bool victoireCouleur(const Board& b, Couleur c) const;

    /**
     * @brief Génère la liste des coups possibles pour une couleur donnée
     *
     * @param b état du plateau
     * @param c couleur du joueur
     * @param stock stock de pions disponibles
     * @return liste des coups possibles
     */
    std::vector<Move> coupsPossibles(const Board& b,
                                     Couleur c,
                                     const std::array<int,3>& stock) const;

    /**
     * @brief Applique un coup sur un état du plateau
     *
     * @param b état du plateau à modifier
     * @param c couleur du joueur
     * @param m coup à appliquer
     * @return true si le coup est valide
     */
    bool appliquer(Board& b, Couleur c, const Move& m) const;

    /**
     * @brief Algorithme minimax multi-joueurs avec élagage alpha-bêta
     *
     * @param b état du plateau
     * @param stocks stocks des pions de chaque joueur
     * @param playerIndex index du joueur courant
     * @param depth profondeur restante
     * @param alpha borne alpha
     * @param beta borne bêta
     * @return score évalué
     */
    int minimax(Board b,
                std::vector<std::array<int,3>> stocks,
                int playerIndex,
                int depth,
                int alpha,
                int beta) const;

    /**
     * @brief Convertit un index de joueur en couleur
     *
     * @param idx index du joueur
     * @return Couleur correspondante
     */
    Couleur couleurIndexToCouleur(int idx) const;

    /**
     * @brief Convertit une couleur en entier
     *
     * @param c couleur
     * @return valeur entière associée
     */
    int couleurToInt(Couleur c) const { return static_cast<int>(c); }

public:
    /**
     * @brief Constructeur de JoueurIA
     *
     * @param nom nom du joueur IA
     * @param couleur couleur associée à l’IA
     */
    JoueurIA(std::string nom, Couleur couleur);

    /**
     * @brief Définit le contexte de jeu de l’IA
     *
     * Doit être appelé par Otrio avant jouerCoup().
     *
     * @param joueurs pointeurs vers tous les joueurs de la partie
     * @param myIndex index de cette IA dans la liste
     */
    void setContexte(const std::vector<Joueur*>& joueurs, int myIndex);

    /**
     * @brief Fait jouer l’IA sur le plateau
     *
     * @param plateau plateau de jeu
     * @return true si un coup a été joué
     */
    bool jouerCoup(Plateau* plateau) override;

    /**
     * @brief Destructeur de JoueurIA
     */
    ~JoueurIA();
};
