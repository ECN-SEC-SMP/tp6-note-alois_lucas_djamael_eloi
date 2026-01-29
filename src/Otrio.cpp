#include "Otrio.hpp"

Otrio::Otrio(void)
{
    // Initialisation des 4 joueurs
    joueurs.push_back(JoueurHumain("Player1", ROUGE));
    joueurs.push_back(JoueurHumain("Player2", BLEU));
    joueurs.push_back(JoueurHumain("Player3", VERT));
    joueurs.push_back(JoueurHumain("Player4", JAUNE));

    // Initialisation du plateau
    plateau = Plateau();

    // Initialisation de l'index du joueur courant
    joueurCourantIndex = 0;
}

Otrio::~Otrio()
{
}

void Otrio::initialiserPartie()
{
    // Réinitialisation du plateau
    plateau = Plateau();

    // Réinitialisation des joueurs et de l'index du joueur courant
    joueurCourantIndex = 0;

    //Affichage de l'état initial du jeu
    cout << "Initialisation de la partie Otrio avec 4 joueurs." << endl;
    
    cout << "Veuillez choisir les noms des 4 joueurs :" << endl;
    for (auto& joueur : joueurs) {
        string nom;
        cout << "Nom du joueur de couleur ";
        switch (joueur.getCouleur()) {
            case ROUGE: cout << "ROUGE"; break;
            case BLEU: cout << "BLEU"; break;
            case VERT: cout << "VERT"; break;
            case JAUNE: cout << "JAUNE"; break;
        }
        cout << " : ";
        cin >> nom;
        joueur = JoueurHumain(nom, joueur.getCouleur());
    }

    cout << "La partie peut commencer !" << endl;
}

void Otrio::lancerBoucleJeu()
{
    while (!estFini())
    {
        afficherEtatJeu(); // Affichage de l'état actuel du jeu avant le coup
        Joueur& joueurCourant = joueurs[joueurCourantIndex];
        cout << "C'est au tour de " << joueurCourant.getNom() << " (" ;
        switch (joueurCourant.getCouleur()) {
            case ROUGE: cout << "ROUGE"; break;
            case BLEU: cout << "BLEU"; break;
            case VERT: cout << "VERT"; break;
            case JAUNE: cout << "JAUNE"; break;
        }
        cout << ")." << endl;

        // On indique au joueur courant ses pions restants
        cout << "Pions restants : ";
        for (const auto& pion : joueurCourant.getPionRestants()) {
            cout << "(";
            switch (pion->getCouleur()) {
                case ROUGE: cout << "ROUGE"; break;
                case BLEU: cout << "BLEU"; break;
                case VERT: cout << "VERT"; break;
                case JAUNE: cout << "JAUNE"; break;
            }
            cout << ", ";
            switch (pion->getTaille()) {
                case PETIT: cout << "PETIT"; break;
                case MOYEN: cout << "MOYEN"; break;
                case GRAND: cout << "GRAND"; break;
            }
            cout << ") ";
        }
        cout << endl;

        cout << joueurCourant.getNom() << " peut jouer son coup..." << endl;

        // Demander quel pion jouer et où le placer

        // 1) Choix du pion parmi ceux restants
        const auto& restants = joueurCourant.getPionRestants();
        if (restants.empty()) {
            cout << "Aucun pion restant pour ce joueur." << endl;
            passerAuJoueurSuivant();
            continue;
        }

        // Dire si le coup a été joué avec succès ou non
        if (!joueurCourant.jouerCoup(&plateau))
        {
            cout << "Coup invalide. Veuillez réessayer." << endl;
            continue; // Le même joueur rejoue
        }

  
        passerAuJoueurSuivant();
    }

    afficherEtatJeu();
    cout << "La partie est terminée !" << endl;
}

bool Otrio::passerAuJoueurSuivant()
{
    joueurCourantIndex = (joueurCourantIndex + 1) % joueurs.size();
    return true;
}

bool Otrio::estFini() const
{
    // Vérification des conditions de victoire pour chaque joueur
    for (const auto& joueur : joueurs)
    {
        if(plateau.verifierVictoire(joueur.getCouleur()))
        {
            cout << "Le joueur " << joueur.getNom() << " a gagné la partie !" << endl;
            return true;
        }
    }
    return false;
}

void Otrio::afficherEtatJeu() const
{
    cout << "État actuel du plateau :" << endl;
    //plateau.afficher();

    cout << "État des joueurs :" << endl;
    for (const auto& joueur : joueurs)
    {
        cout << "- " << joueur.getNom() << " (";
        switch (joueur.getCouleur()) {
            case ROUGE: cout << "ROUGE"; break;
            case BLEU: cout << "BLEU"; break;
            case VERT: cout << "VERT"; break;
            case JAUNE: cout << "JAUNE"; break;
        }
        cout << ") a " << joueur.getPionRestants().size() << " pions restants." << endl;
    }
}