#pragma once

#include "Joueur.hpp"
#include <vector>
#include <array>
#include <limits>

class JoueurIA : public Joueur
{
private:
    // ---------- Etat interne ----------
    // board[y][x][t] = -1 vide, sinon valeur de Couleur
    using Board = std::array<std::array<std::array<int, 3>, 3>, 3>;

    struct Move { int x, y; Taille t; };

    std::vector<Joueur*> joueurs_;
    int myIndex_ = -1;

    // ---------- Construction état ----------
    Board lirePlateau(const Plateau* plateau) const;
    std::array<std::array<int,3>, 8> lireStocksParCouleur() const; 
    // (optionnel : on s'en sert peu, mais utile si tu veux être strict)

    // ---------- Menaces immédiates ----------
    bool trouverCoupPourGagner(const Board& b, Move& best) const;
    bool trouverCoupPourBloquer(const Board& b, Move& best) const;

    // ---------- Recherche / planification ----------
    int eval(const Board& b) const;
    bool victoireCouleur(const Board& b, Couleur c) const;

    std::vector<Move> coupsPossibles(const Board& b, Couleur c, const std::array<int,3>& stock) const;
    bool appliquer(Board& b, Couleur c, const Move& m) const;

    // minimax multi-joueurs (ordre de jeu réel)
    int minimax(Board b,
                std::vector<std::array<int,3>> stocks,
                int playerIndex,
                int depth,
                int alpha,
                int beta) const;

    Couleur couleurIndexToCouleur(int idx) const;
    int couleurToInt(Couleur c) const { return (int)c; }

    public:
    JoueurIA(std::string nom, Couleur couleur);

    // Contexte de la partie (à donner par Otrio avant jouerCoup)
    // joueurs : pointeurs vers tous les joueurs dans l'ordre de jeu
    // myIndex : index de cette IA dans ce tableau
    void setContexte(const std::vector<Joueur*>& joueurs, int myIndex);

    bool jouerCoup(Plateau* plateau) override;
    ~JoueurIA();
};
