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
#include "Otrio.hpp"

using namespace std;

// test de la classe Pion
void test_Pion(void);

// test de la classe Case
void test_Case(void);

// test de la classe Plateau
void test_Plateau(void);
void test_Plateau_v1(void);

// test de la classe Joueur
void test_Joueur(void);

// test de la classe Otrio
void test_Otrio(void);

// FICHIER PRINCIPAL DE TEST DES DIFFERENTES CLASSES (JEUX DESSAI)- A MODIFIER SELON VOS BESOINS
int main()
{

    // /*TEST DE LA CLASSE PION*/
    // test_Pion();

    // /*TEST DE LA CLASSE CASE*/
    // test_Case();

    // /*TEST DE LA CLASSE PLATEAU*/
    // test_Plateau();

    // /*TEST DE LA CLASSE JOUEUR*/
    // test_Joueur();

    /*TEST DE LA CLASSE OTRIO*/
    test_Otrio();

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
    cout << "=== Test Pion FIN ===\n\n";
}

// test de la classe Case
void test_Case(void)
{
    cout << "\n=== Tests Case ===\n";

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

    cout << "=== Test Case FIN ===\n\n";
}

// test de la classe Plateau
void test_Plateau_v1(void)
{
    cout << "\n=== Tests Plateau ===\n";

    Plateau plateau;
    plateau.afficher();

    plateau.placerPion(0, 0, new Pion(ROUGE, PETIT));
    plateau.placerPion(0, 0, new Pion(ROUGE, MOYEN));
    plateau.placerPion(1, 2, new Pion(BLEU, GRAND));
    plateau.afficher();

    // Tests de victoire
    JoueurHumain j1("Alice", ROUGE);
    JoueurHumain j2("Bob", BLEU);

    // Joueur1 place des pions pour
    j1.jouerCoup(&plateau); // Joueur 1 place un pion
    j1.jouerCoup(&plateau); // Joueur 1 place un pion
    j1.jouerCoup(&plateau); // Joueur 1 place un pion
    
    plateau.afficher();
    
    if (plateau.verifierVictoire(j1.getCouleur()))
        cout << j1.getNom() << " a gagne!\n";
    else
        cout << j1.getNom() << " n'a pas encore gagne.\n";

    

    cout << "=== Test Plateau FIN ===\n\n";
}


void test_Plateau()
{
    cout << "=== Tests Plateau ===\n";

    // -----------------------------
    // Test 0 : plateau vide
    // -----------------------------
    {
        Plateau p;
        cout << "\n[TEST] Plateau vide\n";
        p.afficher();

        assert(!p.verifierVictoire(ROUGE) && "Pas de victoire sur plateau vide");
        assert(!p.verifierVictoire(VERT)  && "Pas de victoire sur plateau vide");
        assert(!p.verifierVictoire(BLEU)  && "Pas de victoire sur plateau vide");
        assert(!p.verifierVictoire(JAUNE)&& "Pas de victoire sur plateau vide");
    }

    // -----------------------------
    // Test 1 : placements de base + empilement partiel
    // -----------------------------
    {
        Plateau p;
        cout << "\n[TEST] Placements de base\n";
        assert(p.placerPion(0, 0, new Pion(ROUGE, PETIT)));
        assert(p.placerPion(0, 0, new Pion(ROUGE, MOYEN)));
        // même taille au même endroit -> doit échouer
        assert(!p.placerPion(0, 0, new Pion(BLEU, PETIT)));

        // hors plateau -> doit échouer
        assert(!p.placerPion(-1, 0, new Pion(ROUGE, GRAND)));
        assert(!p.placerPion(3, 2, new Pion(ROUGE, GRAND)));

        p.afficher();

        assert(!p.verifierVictoire(ROUGE) && "Pas encore de victoire (empilement incomplet)");
    }

    // -----------------------------
    // Test 2 : victoire par alignement de 3 cercles identiques
    // Exemple : 3 PETITS ROUGES sur la ligne y=0
    // -----------------------------
    {
        Plateau p;
        cout << "\n[TEST] Victoire - alignement identique (3 PETITS)\n";
        assert(p.placerPion(0, 0, new Pion(ROUGE, PETIT)));
        assert(p.placerPion(1, 0, new Pion(ROUGE, PETIT)));
        assert(p.placerPion(2, 0, new Pion(ROUGE, PETIT)));

        p.afficher();

        assert(p.verifierVictoire(ROUGE) && "ROUGE doit gagner (3 identiques)");
        assert(!p.verifierVictoire(BLEU) && "BLEU ne doit pas gagner");
    }

    // -----------------------------
    // Test 3 : victoire par alignement croissant (PETIT, MOYEN, GRAND)
    // Exemple : colonne x=1, y=0..2
    // -----------------------------
    {
        Plateau p;
        cout << "\n[TEST] Victoire - alignement croissant (P->M->G)\n";
        assert(p.placerPion(1, 0, new Pion(VERT, PETIT)));
        assert(p.placerPion(1, 1, new Pion(VERT, MOYEN)));
        assert(p.placerPion(1, 2, new Pion(VERT, GRAND)));

        p.afficher();

        assert(p.verifierVictoire(VERT) && "VERT doit gagner (croissant)");
        assert(!p.verifierVictoire(ROUGE) && "ROUGE ne doit pas gagner");
    }

    // -----------------------------
    // Test 4 : victoire par empilement complet (PETIT+MOYEN+GRAND dans la même case)
    // Exemple : case (2,2)
    // -----------------------------
    {
        Plateau p;
        cout << "\n[TEST] Victoire - empilement (PETIT+MOYEN+GRAND)\n";
        assert(p.placerPion(2, 2, new Pion(BLEU, PETIT)));
        assert(p.placerPion(2, 2, new Pion(BLEU, MOYEN)));
        assert(p.placerPion(2, 2, new Pion(BLEU, GRAND)));

        p.afficher();

        assert(p.verifierVictoire(BLEU) && "BLEU doit gagner (empilement)");
        assert(!p.verifierVictoire(JAUNE) && "JAUNE ne doit pas gagner");
    }

    // -----------------------------
    // Test 5 (optionnel) : victoire décroissante (GRAND, MOYEN, PETIT)
    // Exemple : diagonale principale
    // -----------------------------
    {
        Plateau p;
        cout << "\n[TEST] Victoire - alignement décroissant (G->M->P)\n";
        assert(p.placerPion(0, 0, new Pion(JAUNE, GRAND)));
        assert(p.placerPion(1, 1, new Pion(JAUNE, MOYEN)));
        assert(p.placerPion(2, 2, new Pion(JAUNE, PETIT)));

        p.afficher();

        assert(p.verifierVictoire(JAUNE) && "JAUNE doit gagner (décroissant)");
    }

    cout << "\nOK: tests Plateau\n";
    cout << "=== Tests Plateau FIN ===\n";
}


// test de la classe Joueur
void test_Joueur(void)
{
    cout << "\n=== Tests Joueur ===\n";

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
    cout << "=== Test Joueur FIN ===\n\n";
}

// test de la classe Otrio
void test_Otrio(void)
{
    cout << "\n=== Tests Otrio ===\n";

    Otrio game;
    game.initialiserPartie();
    game.lancerBoucleJeu();

    cout << "=== Test Otrio FIN ===\n\n";
}