/**
 * @file Plateau.cpp
 * @author Eloi Tourangin
 * @brief
 * @version 0.1
 * @date 20-01-2026
 */

#include "Plateau.hpp"

Plateau::Plateau()
{
    grille = vector<vector<Case>>(3, vector<Case>(3));
}

bool Plateau::placerPion(int x, int y, Pion *p)
{
    if (!p) return false;

    // x = colonne, y = ligne
    if (x < 0 || x >= 3 || y < 0 || y >= 3)
        return false;

    return grille[y][x].placerPion(p);
}

Case *Plateau::getCase(int x, int y)
{
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return nullptr;
    return &grille[y][x];
}
const Case* Plateau::getCase(int x, int y) const
{
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return nullptr;
    return &grille[y][x];
}
bool Plateau::estPlein() const
{
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            const Case* c = getCase(x, y);
            if (!c) return false;

            // Une case est pleine si elle contient PETIT + MOYEN + GRAND
            if (c->estVide(PETIT) || c->estVide(MOYEN) || c->estVide(GRAND))
                return false;
        }
    }
    return true;
}

bool Plateau::verifierVictoire(Couleur couleur) const
{
    return verifierLignes(couleur)
        || verifierColonnes(couleur)
        || verifierDiagonales(couleur)
        || verifierEmpilements(couleur);
}

bool Plateau::verifierLignes(Couleur couleur) const
{
    for (int ligne = 0; ligne < 3; ++ligne)
    {
        Taille tailles[3];
        bool valide = true;

        for (int col = 0; col < 3; ++col)
        {
            Pion* pionTrouve = nullptr;

            for (int t = PETIT; t <= GRAND; ++t)
            {
                Pion* p = grille[ligne][col].getPion(static_cast<Taille>(t));
                if (p && p->getCouleur() == couleur)
                {
                    pionTrouve = p;
                    break;
                }
            }

            if (!pionTrouve)
            {
                valide = false;
                break;
            }

            tailles[col] = pionTrouve->getTaille();
        }

        if (!valide) continue;

        // identiques
        if (tailles[0] == tailles[1] && tailles[1] == tailles[2]) return true;
        // croissantes
        if (tailles[0] < tailles[1] && tailles[1] < tailles[2]) return true;
        // décroissantes
        if (tailles[0] > tailles[1] && tailles[1] > tailles[2]) return true;
    }

    return false;
}

bool Plateau::verifierColonnes(Couleur couleur) const
{
    for (int col = 0; col < 3; ++col)
    {
        Taille tailles[3];
        bool valide = true;

        for (int ligne = 0; ligne < 3; ++ligne)
        {
            Pion* pionTrouve = nullptr;

            for (int t = PETIT; t <= GRAND; ++t)
            {
                Pion* p = grille[ligne][col].getPion(static_cast<Taille>(t));
                if (p && p->getCouleur() == couleur)
                {
                    pionTrouve = p;
                    break;
                }
            }

            if (!pionTrouve)
            {
                valide = false;
                break;
            }

            tailles[ligne] = pionTrouve->getTaille();
        }

        if (!valide) continue;

        if (tailles[0] == tailles[1] && tailles[1] == tailles[2]) return true;
        if (tailles[0] < tailles[1] && tailles[1] < tailles[2]) return true;
        if (tailles[0] > tailles[1] && tailles[1] > tailles[2]) return true;
    }

    return false;
}

bool Plateau::verifierDiagonales(Couleur couleur) const
{
    const int diagonales[2][3][2] = {
        { {0,0}, {1,1}, {2,2} },
        { {0,2}, {1,1}, {2,0} }
    };

    for (int d = 0; d < 2; ++d)
    {
        Taille tailles[3];
        bool valide = true;

        for (int k = 0; k < 3; ++k)
        {
            int x = diagonales[d][k][0];
            int y = diagonales[d][k][1];

            Pion* pionTrouve = nullptr;

            for (int t = PETIT; t <= GRAND; ++t)
            {
                // ✅ correction : grille[y][x] (ligne, colonne)
                Pion* p = grille[y][x].getPion(static_cast<Taille>(t));
                if (p && p->getCouleur() == couleur)
                {
                    pionTrouve = p;
                    break;
                }
            }

            if (!pionTrouve)
            {
                valide = false;
                break;
            }

            tailles[k] = pionTrouve->getTaille();
        }

        if (!valide) continue;

        if (tailles[0] == tailles[1] && tailles[1] == tailles[2]) return true;
        if (tailles[0] < tailles[1] && tailles[1] < tailles[2]) return true;
        if (tailles[0] > tailles[1] && tailles[1] > tailles[2]) return true;
    }

    return false;
}

bool Plateau::verifierEmpilements(Couleur couleur) const
{
    for (const auto& ligne : grille)
    {
        for (const auto& casePlateau : ligne)
        {
            Pion* pPetit = casePlateau.getPion(PETIT);
            Pion* pMoyen = casePlateau.getPion(MOYEN);
            Pion* pGrand = casePlateau.getPion(GRAND);

            if (!pPetit || !pMoyen || !pGrand) continue;

            if (pPetit->getCouleur() == couleur &&
                pMoyen->getCouleur() == couleur &&
                pGrand->getCouleur() == couleur)
            {
                return true;
            }
        }
    }

    return false;
}

static char couleurToChar(Couleur c)
{
    switch (c)
    {
        case ROUGE:  return 'R';
        case VERT:   return 'V';
        case BLEU:   return 'B';
        case JAUNE:  return 'J'; // J comme JAUNE (ou 'P' si tu préfères)
        default:     return '?';
    }
}

void Plateau::afficher() const
{
    cout << "\n--PLATEAU--\n";
    cout << "y\\x    0          1           2\n";

    for (int y = 0; y < 3; ++y)
    {
        cout << y << "   ";
        for (int x = 0; x < 3; ++x)
        {
            const Case& c = grille[y][x];

            cout << "[";

            if (c.getPion(PETIT))
                cout << "p" << couleurToChar(c.getPion(PETIT)->getCouleur());
            else
                cout << "..";

            cout << " ";

            if (c.getPion(MOYEN))
                cout << "m" << couleurToChar(c.getPion(MOYEN)->getCouleur());
            else
                cout << "..";

            cout << " ";

            if (c.getPion(GRAND))
                cout << "g" << couleurToChar(c.getPion(GRAND)->getCouleur());
            else
                cout << "..";

            cout << "] ";
        }
        cout << '\n';
    }
    cout << "--------------\n";
}

bool Plateau::peutPlacer(int x, int y, const Pion* p) const
{
    if (!p) return false;
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;

    const Case& c = grille[y][x];
    return c.estVide(p->getTaille()); // même règle que Case::placerPion (slot libre)
}

bool Plateau::joueurPeutJouer(const Joueur& j) const
{
    const auto pions = j.getPionRestants();
    if (pions.empty()) return false;

    for (Pion* p : pions)
    {
        if (!p) continue;
        for (int y = 0; y < 3; ++y)
        {
            for (int x = 0; x < 3; ++x)
            {
                if (peutPlacer(x, y, p))
                    return true;
            }
        }
    }
    return false;
}
