#include "case.hpp"

int Case::idx(Taille t) {
    switch (t) {
        case PETIT: return 0;
        case MOYEN: return 1;
        case GRAND: return 2;
        default:    return -1;
    }
}

// Constructeur par défaut
Case::Case() : emplacements{nullptr, nullptr, nullptr} {}

// Place un pion dans l’emplacement correspondant à sa taille.
// Retourne false si l’emplacement est déjà occupé ou si p == nullptr.
bool Case::placerPion(Pion* p) {
    if (!p) return false;

    const int i = idx(p->getTaille());
    if (i < 0) return false;

    if (emplacements[i] != nullptr) return false;

    emplacements[i] = p;
    return true;
}

// Retire et renvoie le pion de taille t (nullptr si vide).
Pion* Case::retirerPion(Taille t) {
    const int i = idx(t);
    if (i < 0) return nullptr;

    Pion* p = emplacements[i];
    emplacements[i] = nullptr;
    return p;
}

// Renvoie le pion de taille t (nullptr si vide).
Pion* Case::getPion(Taille t) const {
    const int i = idx(t);
    if (i < 0) return nullptr;

    return emplacements[i];
}

// Renvoie le pion de taille t (nullptr si vide).
bool Case::estVide() const {
    return emplacements[0] == nullptr &&
           emplacements[1] == nullptr &&
           emplacements[2] == nullptr;
}

// True si l’emplacement t est vide.
bool Case::aEmpilement() const {
    if (emplacements[0] == nullptr ||
        emplacements[1] == nullptr ||
        emplacements[2] == nullptr) {
        return false;
    }

    Couleur c = emplacements[0]->getCouleur();
    return (emplacements[1]->getCouleur() == c) &&
           (emplacements[2]->getCouleur() == c);
}

// True si la case contient un empilement complet (3 tailles) d’une même couleur.
bool Case::aEmpilement() const {
    if (emplacements[0] == nullptr ||
        emplacements[1] == nullptr ||
        emplacements[2] == nullptr) {
        return false;
    }

    Couleur c = emplacements[0]->getCouleur();
    return (emplacements[1]->getCouleur() == c) &&
           (emplacements[2]->getCouleur() == c);
}

