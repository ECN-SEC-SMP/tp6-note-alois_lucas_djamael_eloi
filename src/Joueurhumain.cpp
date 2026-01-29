#include "Joueurhumain.hpp"

JoueurHumain::JoueurHumain(string nom, Couleur couleur)
    : Joueur(nom, couleur)
{
}

JoueurHumain::~JoueurHumain()
{
}


bool JoueurHumain::jouerCoup(Plateau* plateau)
{
    cout << "C'est au tour de " << nom << " de jouer.\n";

    // Afficher la main
    afficherMain();

    // Le joueur humain ne joue que sa couleur
    Couleur couleur = static_cast<Couleur>(this->couleur);

    // 1) Choix du pion (boucle jusqu'à choix valide)
    Pion* pionChoisi = nullptr;
    while (pionChoisi == nullptr)
    {
        int tailleInput;
        cout << "Taille (0: PETIT, 1: MOYEN, 2: GRAND): ";
        if (!(cin >> tailleInput))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide (non numérique). Réessayez.\n";
            continue;
        }

        if (tailleInput < 0 || tailleInput > 2)
        {
            cout << "Entrée invalide pour la taille. Réessayez.\n";
            continue;
        }

        Taille taille = static_cast<Taille>(tailleInput);

        // Chercher un pion correspondant dans la main
        for (Pion* p : main)
        {
            if (p->getTaille() == taille && p->getCouleur() == couleur)
            {
                pionChoisi = p;
                break;
            }
        }

        if (pionChoisi == nullptr)
        {
            cout << "Pion non disponible dans la main. Réessayez.\n";
        }
    }

    cout << "Pion choisi: Taille " << (string)pionChoisi->getTailleStr()
         << ", Couleur " << (string)pionChoisi->getCouleurStr() << "\n";

    // 2) Choix de la case (boucle jusqu'au placement valide)
    while (true)
    {
        int x, y;
        cout << "Indiquez les coordonnées (x y) pour placer le pion: ";
        if (!(cin >> x >> y))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide (non numérique). Réessayez.\n";
            continue;
        }

        // Tenter de placer SANS retirer de la main avant validation
        if (plateau->placerPion(x, y, pionChoisi))
        {
            // Maintenant seulement on retire de la main
            retirerPionDeMain(pionChoisi);
            cout << "Pion placé en (" << x << ", " << y << ").\n";
            return true;
        }

        cout << "Placement échoué (case occupée / hors plateau / taille déjà prise...). Réessayez.\n";
    }
}
