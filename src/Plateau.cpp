/**
 * @file Plateau.cpp
 * @author Eloi Tourangin (Eloi.Tourangin@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "Plateau.hpp"

Plateau::Plateau()
{
}

bool Plateau::placerPion(int x, int y, Pion *p)
{
    // verifier si la case est valide et placer le pion
    if (x < 0 || x >= this->grille.size() || y < 0 || y >= this->grille.size())
    {
        return false;
        throw invalid_argument("placerPion: coordonnées de case invalides.");
    }
    
    bool placed = this->grille[y][x].placerPion(p);
    return placed;
}

Case *Plateau::getCase(int x, int y)
{
    return &grille[y][x];
}

bool Plateau::verifierVictoire(Joueur* joueur)
{
    return verifierLignes(joueur) || verifierColonnes(joueur) || verifierDiagonales(joueur) || verifierEmpilements(joueur);
}

bool Plateau::verifierLignes(Joueur* joueur)
{ 
    for(int ligne = 0; ligne < 3; ++ligne)
    {
            Taille tailles[3];
            bool valide = true;

            // Pour chaque case de la ligne
            for (int k = 0; k < 3; ++k)
            {
                Pion* pionTrouve = nullptr;

                // Chercher un pion de la bonne couleur dans la case
                for (int t = PETIT; t <= GRAND; ++t)
                {
                    Pion* p = grille[ligne][k].getPion(static_cast<Taille>(t));
                    if (p && p->getCouleur() == joueur->getCouleur())
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

            if (!valide)
                continue;

            // Cas 1 : tailles identiques
            if (tailles[0] == tailles[1] && tailles[1] == tailles[2])
                return true;

            // Cas 2 : tailles strictement croissantes
            if (tailles[0] < tailles[1] && tailles[1] < tailles[2])
                return true;

            // Cas 3 : tailles strictement décroissantes
            if (tailles[0] > tailles[1] && tailles[1] > tailles[2])
                return true;
    }
    
}

bool Plateau::verifierColonnes(Joueur* joueur)
{
    for(int colonne = 0; colonne < 3; ++colonne)
    {

            Taille tailles[3];
            bool valide = true;

            // Pour chaque case de la colonne
            for (int k = 0; k < 3; ++k)
            {
                Pion* pionTrouve = nullptr;

                // Chercher un pion de la bonne couleur dans la case
                for (int t = PETIT; t <= GRAND; ++t)
                {
                    Pion* p = grille[k][colonne].getPion(static_cast<Taille>(t));
                    if (p && p->getCouleur() == joueur->getCouleur())
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

            if (!valide)
                continue;

            // Cas 1 : tailles identiques
            if (tailles[0] == tailles[1] && tailles[1] == tailles[2])
                return true;

            // Cas 2 : tailles strictement croissantes
            if (tailles[0] < tailles[1] && tailles[1] < tailles[2])
                return true;

            // Cas 3 : tailles strictement décroissantes
            if (tailles[0] > tailles[1] && tailles[1] > tailles[2])
                return true;
        }
}

bool Plateau::verifierDiagonales(Joueur* joueur)
{
    // Coordonnées des deux diagonales
    const int diagonales[2][3][2] = {
        { {0,0}, {1,1}, {2,2} },
        { {0,2}, {1,1}, {2,0} }
    };

    for (int d = 0; d < 2; ++d)
    {
        for (int c = ROUGE; c <= JAUNE; ++c)
        {
            Couleur couleur = static_cast<Couleur>(c);
            Taille tailles[3];
            bool valide = true;

            // Pour chaque case de la diagonale
            for (int k = 0; k < 3; ++k)
            {
                int x = diagonales[d][k][0];
                int y = diagonales[d][k][1];

                Pion* pionTrouve = nullptr;

                // Chercher un pion de la bonne couleur dans la case
                for (int t = PETIT; t <= GRAND; ++t)
                {
                    Pion* p = grille[x][y].getPion(static_cast<Taille>(t));
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

            if (!valide)
                continue;

            // Cas 1 : tailles identiques
            if (tailles[0] == tailles[1] && tailles[1] == tailles[2])
                return true;

            // Cas 2 : tailles strictement croissantes
            if (tailles[0] < tailles[1] && tailles[1] < tailles[2])
                return true;

            // Cas 3 : tailles strictement décroissantes
            if (tailles[0] > tailles[1] && tailles[1] > tailles[2])
                return true;
        }
    }

    return false;
}




bool Plateau::verifierEmpilements(Joueur* joueur)
{
    // on appelle aEmpilement sur chaque case du plateau
    for (const auto& ligne : grille)
    {
        for (const auto& casePlateau : ligne)
        {
            if (casePlateau.aEmpilement(joueur))
            {
                return true;
            }
        }
    }
}