#include "Otrio.hpp"
#include "Affichage.hpp"
#include <limits>

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

void Otrio::initialiserPartie(int mode)
{
    // Réinitialisation du plateau
    plateau = Plateau();

    // Réinitialisation des joueurs et de l'index du joueur courant
    joueurCourantIndex = 0;

    this->mode = mode;

    if(mode == 0){

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
    }else if(mode == 1){
        cout << "Initialisation de la partie Otrio avec 2 joueurs." << endl;
        cout << "Veuillez choisir les noms des 2 joueurs :" << endl;

        joueurs.clear();

        for(int i=0; i<2; i++){
            string nom;
            cout << "Nom du joueur " << (i+1) << " : ";
            cin >> nom;
            if(i == 0){
                joueurs.push_back(JoueurHumain(nom, ROUGE));
                joueurs.push_back(JoueurHumain(nom, BLEU));
            } else {
                joueurs.push_back(JoueurHumain(nom, VERT));
                joueurs.push_back(JoueurHumain(nom, JAUNE));
            }
        }
    }

    cout << "La partie peut commencer !" << endl;
    
    // Afficher l'état initial du plateau
    Affichage::afficherPlateau(this);
}

void Otrio::lancerBoucleJeu()
{
    if(mode == 0){
        while (!estFini() && Affichage::estActif())
        {
            // Affichage graphique du plateau
            Affichage::afficherPlateau(this);
            
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
        
        // Fermer l'affichage graphique
        Affichage::fermer();
    }
    else if(mode == 1){
        // ======= Mode 2 joueurs humains (2 couleurs chacun) =======
        // joueurCourantIndex : 0 => Humain 1, 1 => Humain 2

        while (!estFini() && Affichage::estActif())
        {
            Affichage::afficherPlateau(this);
            afficherEtatJeu();

            int base = (joueurCourantIndex == 0) ? 0 : 2; // 0/1 pour J1, 2/3 pour J2

            // Afficher le nom du joueur humain (même nom sur les deux couleurs)
            cout << "C'est au tour de " << joueurs[base].getNom() << " (2 couleurs)." << endl;

            // Choix de la couleur à jouer (donc quel JoueurHumain utiliser)
            cout << "Choisir la couleur a jouer : " << endl;
            cout << "  0 -> ";
            switch (joueurs[base].getCouleur()) {
                case ROUGE: cout << "ROUGE"; break;
                case BLEU:  cout << "BLEU";  break;
                case VERT:  cout << "VERT";  break;
                case JAUNE: cout << "JAUNE"; break;
            }
            cout << endl;

            cout << "  1 -> ";
            switch (joueurs[base+1].getCouleur()) {
                case ROUGE: cout << "ROUGE"; break;
                case BLEU:  cout << "BLEU";  break;
                case VERT:  cout << "VERT";  break;
                case JAUNE: cout << "JAUNE"; break;
            }
            cout << endl;

            int choix = -1;
            cout << "Votre choix (0/1) : ";
            cin >> choix;
            if (!cin || (choix != 0 && choix != 1))
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Choix invalide." << endl;
                continue; // même humain rejoue
            }

            Joueur& joueurCourant = joueurs[base + choix];

            // Optionnel : check main vide
            if (joueurCourant.getPionRestants().empty())
            {
                cout << "Aucun pion restant pour cette couleur. Choisissez l'autre couleur." << endl;
                continue;
            }

            cout << "Vous jouez la couleur ";
            switch (joueurCourant.getCouleur()) {
                case ROUGE: cout << "ROUGE"; break;
                case BLEU:  cout << "BLEU";  break;
                case VERT:  cout << "VERT";  break;
                case JAUNE: cout << "JAUNE"; break;
            }
            cout << "." << endl;

            if (!joueurCourant.jouerCoup(&plateau))
            {
                cout << "Coup invalide. Veuillez réessayer." << endl;
                continue; // même humain rejoue
            }

            passerAuJoueurSuivant(); // en mode 1 => modulo 2
        }

        afficherEtatJeu();
        cout << "La partie est terminée !" << endl;
        Affichage::fermer();
    }
}

bool Otrio::passerAuJoueurSuivant()
{
    if (mode == 0) joueurCourantIndex = (joueurCourantIndex + 1) % 4;
    else          joueurCourantIndex = (joueurCourantIndex + 1) % 2;
    return true;
}

bool Otrio::estFini() const
{
    if (mode == 0)
    {
        for (const auto& joueur : joueurs)
        {
            if (plateau.verifierVictoire(joueur.getCouleur()))
            {
                cout << "Le joueur " << joueur.getNom() << " a gagné la partie !" << endl;
                return true;
            }
        }
        return false;
    }

    // mode 1 : joueurs[0,1] pour humain 1 ; joueurs[2,3] pour humain 2
    bool win1 = plateau.verifierVictoire(joueurs[0].getCouleur()) ||
                plateau.verifierVictoire(joueurs[1].getCouleur());
    if (win1) {
        cout << "Le joueur " << joueurs[0].getNom() << " a gagné la partie !" << endl;
        return true;
    }

    bool win2 = plateau.verifierVictoire(joueurs[2].getCouleur()) ||
                plateau.verifierVictoire(joueurs[3].getCouleur());
    if (win2) {
        cout << "Le joueur " << joueurs[2].getNom() << " a gagné la partie !" << endl;
        return true;
    }

    return false;
}


void Otrio::afficherEtatJeu() const
{
    cout << "État actuel du plateau :" << endl;
    plateau.afficher();

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