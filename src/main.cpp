/**
 * @file main.cpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr)
 * @author Lucas Oros (lucas.oros@eleves.ec-nantes.fr)
 * @author Djamael Lahamion (djamael.lahamion@eleves.ec-nantes.fr)
 * @author Aloïs Guillon (alois.guillon@eleves.ec-nantes.fr)
 *
 * @brief
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <vector>

#include "Plateau.hpp"
#include "Case.hpp"
#include "Pion.hpp"

using namespace std;

// test de la classe Pion

// test de la classe Case
void test_Case(void);

// test de la classe Plateau

// test de la classe Joueur

// test de la classe Otrio

// FICHIER PRINCIPAL DE TEST DES DIFFERENTES CLASSES (JEUX DESSAI)- A MODIFIER SELON VOS BESOINS
int main()
{

    /*TEST DE LA CLASSE PION*/

    /*TEST DE LA CLASSE CASE*/
    test_Case();

    /*TEST DE LA CLASSE PLATEAU*/

    /*TEST DE LA CLASSE JOUEUR*/

    /*TEST DE LA CLASSE OTRIO*/

    return 0;
}

// test de la classe Pion

// test de la classe Case
void test_Case(void)
{
    cout << "=== Tests Case ===\n";

    // 1) Trois pions (couleur: VERT)
    Pion pPetit(VERT, PETIT);
    Pion pMoyen(VERT, MOYEN);
    Pion pGrand(VERT, GRAND);

    // 2) Une case vide
    Case c;

    // 3) Placer le petit
    assert(c.placerPion(&pPetit) && "placerPion(PETIT) doit reussir");
    cout << "OK: placement PETIT\n";

    // 4) Placer le moyen
    assert(c.placerPion(&pMoyen) && "placerPion(MOYEN) doit reussir");
    cout << "OK: placement MOYEN\n";
    // 5) Tester estVide
    assert(!c.estVide(PETIT) && "PETIT ne doit pas etre vide");
    assert(!c.estVide(MOYEN) && "MOYEN ne doit pas etre vide");
    assert(c.estVide(GRAND) && "GRAND doit etre vide");
    cout << "OK: estVide\n";

    // 6) Tester getPion
    assert(c.getPion(PETIT) == &pPetit && "getPion(PETIT) doit renvoyer pPetit");
    assert(c.getPion(MOYEN) == &pMoyen && "getPion(MOYEN) doit renvoyer pMoyen");
    assert(c.getPion(GRAND) == nullptr && "getPion(GRAND) doit etre nullptr");
    cout << "OK: getPion\n";

    // 7) Supprimer le moyen
    Pion *ret = c.retirerPion(MOYEN);
    assert(ret == &pMoyen && "retirerPion(MOYEN) doit renvoyer pMoyen");
    cout << "OK: retrait MOYEN\n";

    // 8) getPion après suppression
    assert(c.getPion(MOYEN) == nullptr && "Apres retrait, getPion(MOYEN) doit etre nullptr");
    cout << "OK: getPion apres retrait\n";
    // 9) Tester empilement : pour l’instant faux (il manque MOYEN + GRAND)
    assert(!c.aEmpilement() && "aEmpilement doit etre faux (manque des tailles)");
    cout << "OK: aEmpilement faux (incomplet)\n";

    // 10) Ajouter le moyen et le grand -> empilement attendu
    assert(c.placerPion(&pMoyen) && "re-placerPion(MOYEN) doit reussir");
    assert(c.placerPion(&pGrand) && "placerPion(GRAND) doit reussir");
    assert(c.aEmpilement() && "aEmpilement doit etre vrai (3 tailles VERT)");
    cout << "OK: aEmpilement vrai (3 tailles)\n";

    cout << "=== Test Case FIN ===\n";
}

// test de la classe Plateau

// test de la classe Joueur

// test de la classe Otrio