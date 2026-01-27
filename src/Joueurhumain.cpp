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

    // Implémentation spécifique pour le joueur humain
    cout << "C'est au tour de " << nom << " de jouer." << endl;

    // Affichage des pions disponibles pour le joueur
    for(Pion* p : main)
    {
        cout << "Pion disponible: " << p->getTaille() << "; " << p->getCouleur() << endl;
    }

    // Sélection du pion par le joueur humain
    cout << "Sélectionner un pion à jouer." << endl;
    cout << "Indiquez la taille et la couleur du pion." << endl;

    int tailleInput, couleurInput;

    cout << "Taille (0: PETIT, 1: MOYEN, 2: GRAND): ";
    cin >> tailleInput;
    cout << "Couleur (0: ROUGE, 1: VERT, 2: BLEU, 3: JAUNE): ";
    cin >> couleurInput;

    if(tailleInput < 0 || tailleInput > 2 )
    {
        cout << "Entrée invalide pour la taille." << endl;
        throw invalid_argument("jouerCoup: Entrée invalide pour la taille.");
        return false;
    }
    if(couleurInput < 0 || couleurInput > 3 )
    {
        cout << "Entrée invalide pour la couleur." << endl;
        throw invalid_argument("jouerCoup: Entrée invalide pour la couleur.");
        return false;
    }
    
    // Conversion des entrées en enums
    Taille taille = static_cast<Taille>(tailleInput);
    Couleur couleur = static_cast<Couleur>(couleurInput);

    // Création d'un pointeur vers le pion choisi
    Pion* pionChoisi = nullptr;
    for(Pion* p : main)
    {
        if(p->getTaille() == taille && p->getCouleur() == couleur)
        {
            pionChoisi = p;
            break;
        }
    }

    if(pionChoisi == nullptr)
    {
        cout << "Pion non disponible dans la main." << endl;
        throw invalid_argument("jouerCoup: Pion non disponible dans la main.");
        return false;
    }
    retirerPionDeMain(pionChoisi);
    cout << "Pion choisi: Taille " << pionChoisi->getTaille()
            << ", Couleur " << pionChoisi->getCouleur() << endl;    
    int x, y;
    cout << "Indiquez les coordonnées (x y) pour placer le pion: ";
    cin >> x >> y;

    if(plateau->placerPion(x, y, pionChoisi))
    {
        cout << "Pion placé en (" << x << ", " << y << ")." << endl;
    }
    else
    {
        cout << "Placement du pion échoué. Réessayez." << endl;
        main.push_back(pionChoisi); // Remettre le pion dans la main en cas d'échec
        return false;
    }
    return true;
}