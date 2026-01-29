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
#include <cassert>
    
//#include "Plateau.hpp"
#include "Case.hpp"
#include "Pion.hpp"
#include "Joueur.hpp"
#include "Joueurhumain.hpp"

using namespace std;

// test de la classe Pion
void test_Pion(void);

// test de la classe Case
void test_Case(void);

// test de la classe Plateau
void test_Plateau(void);

// test de la classe Joueur
void test_Joueur(void);

// test de la classe Otrio

// FICHIER PRINCIPAL DE TEST DES DIFFERENTES CLASSES (JEUX DESSAI)- A MODIFIER SELON VOS BESOINS
int main()
{

    /*TEST DE LA CLASSE PION*/
    test_Pion();

    /*TEST DE LA CLASSE CASE*/
    test_Case();

    /*TEST DE LA CLASSE PLATEAU*/
    test_Plateau();

    /*TEST DE LA CLASSE JOUEUR*/
    test_Joueur();

    /*TEST DE LA CLASSE OTRIO*/

    return 0;
}

// test de la classe Pion
void test_Pion(void)
{
    cout << "=== Tests Pion ===\n";

    // 1) Création de pions
    Pion p1(ROUGE, PETIT);
    Pion p2(BLEU, MOYEN);
    Pion p3(VERT, GRAND);

    // 2) Vérification des attributs
    assert(p1.getCouleur() == ROUGE && "p1 couleur doit etre ROUGE");
    assert(p1.getTaille() == PETIT && "p1 taille doit etre PETIT");
    assert(p2.getCouleur() == BLEU && "p2 couleur doit etre BLEU");
    assert(p2.getTaille() == MOYEN && "p2 taille doit etre MOYEN");
    assert(p3.getCouleur() == VERT && "p3 couleur doit etre VERT");
    assert(p3.getTaille() == GRAND && "p3 taille doit etre GRAND");

    cout << "OK: creation et verification des pions\n";
    cout << "=== Test Pion FIN ===\n";
}

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

    // 10) Ajouter le moyen et le grand -> empilement attendu
    assert(c.placerPion(&pMoyen) && "re-placerPion(MOYEN) doit reussir");
    assert(c.placerPion(&pGrand) && "placerPion(GRAND) doit reussir");

    cout << "=== Test Case FIN ===\n";
}

// test de la classe Plateau
void test_Plateau(void)
{
    cout << "=== Tests Plateau ===\n";

    Plateau plateau;
    plateau.afficher();

    plateau.placerPion(0, 0, new Pion(ROUGE, PETIT));
    plateau.placerPion(0, 0, new Pion(ROUGE, MOYEN));
    plateau.placerPion(1, 2, new Pion(BLEU, GRAND));
    plateau.afficher();

    // Tests à implémenter

    cout << "=== Test Plateau FIN ===\n";
}

// test de la classe Joueur
void test_Joueur(void)
{
    cout << "=== Tests Joueur ===\n";

    // 1) Création d'un joueur
    JoueurHumain j("Alice", ROUGE);

    // 2) Vérification des attributs
    assert(j.getNom() == "Alice" && "Le nom du joueur doit etre Alice");
    assert(j.getCouleur() == ROUGE && "La couleur du joueur doit etre ROUGE");

    // 3) Vérification du nombre de pions dans la main
    vector<Pion*> pionsRestants = j.getPionRestants();
    assert(pionsRestants.size() == NB_GROUPES_PIONS * NB_PIONS_PAR_TAILLE && "Le joueur doit avoir le bon nombre de pions");

    // 4) Retirer un pion de la main
    Pion* pionARetirer = pionsRestants[0];
    j.retirerPionDeMain(pionARetirer);
    pionsRestants = j.getPionRestants();
    assert(pionsRestants.size() == (NB_GROUPES_PIONS * NB_PIONS_PAR_TAILLE) - 1 && "Le joueur doit avoir un pion de moins apres retrait");

    cout << "OK: creation et verification du joueur\n";

    // 5) Jouer un coup
    // Note: Ce test nécessite une instance de Plateau valide
    Plateau plateau;
    bool coupJoue = j.jouerCoup(&plateau);
    assert(coupJoue && "Le joueur doit pouvoir jouer un coup");
    cout << "OK: jouerCoup\n";
    plateau.afficher();
    cout << "=== Test Joueur FIN ===\n";
}

// test de la classe Otrio