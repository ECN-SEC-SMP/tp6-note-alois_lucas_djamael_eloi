#include "Otrio.hpp"
#include "Affichage.hpp"
#include <limits>
#include <cctype>

static void afficherCouleur(Couleur c)
{
    switch (c) {
        case ROUGE: cout << "ROUGE"; break;
        case BLEU:  cout << "BLEU";  break;
        case VERT:  cout << "VERT";  break;
        case JAUNE: cout << "JAUNE"; break;
        default:    cout << "??";    break;
    }
}

Otrio::Otrio(void)
{
    // Initialisation du plateau
    plateau = Plateau();

    // Initialisation de l'index du joueur courant
    joueurCourantIndex = 0;
    mode = 0;

    // Initialisation des 4 joueurs humains par défaut
    joueurs.clear();
    joueurs.push_back(make_unique<JoueurHumain>("Player1", ROUGE));
    joueurs.push_back(make_unique<JoueurHumain>("Player2", BLEU));
    joueurs.push_back(make_unique<JoueurHumain>("Player3", VERT));
    joueurs.push_back(make_unique<JoueurHumain>("Player4", JAUNE));
}

Otrio::~Otrio() {}

void Otrio::initialiserPartie(int mode)
{
    plateau = Plateau();
    joueurCourantIndex = 0;
    this->mode = mode;

    if (mode == 0)
    {
        cout << "Initialisation de la partie Otrio avec 4 joueurs." << endl;

        // si joueurs pas initialisés (sécurité)
        if (joueurs.size() != 4)
        {
            joueurs.clear();
            joueurs.push_back(make_unique<JoueurHumain>("Player1", ROUGE));
            joueurs.push_back(make_unique<JoueurHumain>("Player2", BLEU));
            joueurs.push_back(make_unique<JoueurHumain>("Player3", VERT));
            joueurs.push_back(make_unique<JoueurHumain>("Player4", JAUNE));
        }

        cout << "Veuillez choisir les noms des 4 joueurs :" << endl;
        for (auto& joueurPtr : joueurs)
        {
            string nom;
            cout << "Nom du joueur de couleur ";
            afficherCouleur(joueurPtr->getCouleur());
            cout << " : ";
            cin >> nom;

            // on remplace l'objet par un nouveau JoueurHumain (même couleur)
            Couleur c = joueurPtr->getCouleur();
            joueurPtr = make_unique<JoueurHumain>(nom, c);
        }
    }
    else if (mode == 1)
    {
        cout << "Initialisation de la partie Otrio avec 2 joueurs." << endl;
        cout << "Veuillez choisir les noms des 2 joueurs :" << endl;

        joueurs.clear();

        string nom1, nom2;
        cout << "Nom du joueur 1 : ";
        cin >> nom1;
        cout << "Nom du joueur 2 : ";
        cin >> nom2;

        // Joueur 1 : ROUGE + BLEU
        joueurs.push_back(make_unique<JoueurHumain>(nom1, ROUGE));
        joueurs.push_back(make_unique<JoueurHumain>(nom1, BLEU));

        // Joueur 2 : VERT + JAUNE
        joueurs.push_back(make_unique<JoueurHumain>(nom2, VERT));
        joueurs.push_back(make_unique<JoueurHumain>(nom2, JAUNE));
    }
    else if (mode == 2)
    {
        // ======= MODE 2 (Version 3 : IA) =======
        cout << "Initialisation de la partie Otrio Version 3 (IA possible)." << endl;
        cout << "Pour chaque couleur, choisir Humain (H) ou IA (I)." << endl;

        joueurs.clear();
        const Couleur couleurs[4] = { ROUGE, BLEU, VERT, JAUNE };

        for (int i = 0; i < 4; ++i)
        {
            char type = '\0';
            while (type != 'H' && type != 'I')
            {
                cout << "Joueur " ;
                afficherCouleur(couleurs[i]);
                cout << " : Humain (H) ou IA (I) ? ";
                cin >> type;
                type = (char)toupper((unsigned char)type);
            }

            string nom;
            cout << "Nom du joueur ";
            afficherCouleur(couleurs[i]);
            cout << " : ";
            cin >> nom;

            if (type == 'H')
                joueurs.push_back(make_unique<JoueurHumain>(nom, couleurs[i]));
            else
                joueurs.push_back(make_unique<JoueurIA>(nom, couleurs[i]));
        }
    }

    cout << "La partie peut commencer !" << endl;
    Affichage::afficherPlateau(this);
}


void Otrio::lancerBoucleJeu()
{
    auto buildRawPlayers = [&]() {
        vector<Joueur*> raw;
        raw.reserve(joueurs.size());
        for (auto& up : joueurs) raw.push_back(up.get());
        return raw;
    };

    // ======= Modes 0 et 2 : 4 joueurs (humains et/ou IA) =======
    if (mode == 0 || mode == 2)
    {
        int passesConsecutifs = 0;
        const int nbJoueursActifs = (int)joueurs.size(); // normalement 4

        while (!estFini() && Affichage::estActif())
        {
            Affichage::afficherPlateau(this);
            afficherEtatJeu();

            Joueur& joueurCourant = *joueurs[joueurCourantIndex];

            cout << "C'est au tour de " << joueurCourant.getNom() << " (";
            afficherCouleur(joueurCourant.getCouleur());
            cout << ")." << endl;

            // Si IA (mode 2) : donner le contexte
            if (mode == 2)
            {
                if (auto* ia = dynamic_cast<JoueurIA*>(&joueurCourant))
                {
                    auto raw = buildRawPlayers();
                    ia->setContexte(raw, joueurCourantIndex);
                }
            }

            // 1) Si le joueur ne peut pas jouer : il passe
            if (!plateau.joueurPeutJouer(joueurCourant))
            {
                cout << joueurCourant.getNom() << " ne peut pas jouer -> passe son tour." << endl;
                passesConsecutifs++;

                if (passesConsecutifs >= nbJoueursActifs)
                {
                    cout << "Aucun joueur ne peut jouer sur un tour complet -> match nul !" << endl;
                    break;
                }

                passerAuJoueurSuivant();
                continue;
            }

            // Si on arrive ici : ce joueur peut jouer => reset passes
            // (on ne le fait qu'après un coup valide, pour éviter de “débloquer” si le joueur échoue)
            const auto& restants = joueurCourant.getPionRestants();
            if (restants.empty())
            {
                // Main vide = incapable de jouer (normalement joueurPeutJouer aurait déjà renvoyé false)
                cout << "Aucun pion restant pour ce joueur -> passe." << endl;
                passesConsecutifs++;

                if (passesConsecutifs >= nbJoueursActifs)
                {
                    cout << "Aucun joueur ne peut jouer sur un tour complet -> match nul !" << endl;
                    break;
                }

                passerAuJoueurSuivant();
                continue;
            }

            // 2) Jouer le coup
            if (!joueurCourant.jouerCoup(&plateau))
            {
                cout << "Coup invalide. Veuillez réessayer." << endl;
                continue; // même joueur rejoue (et n’est pas considéré comme “passe”)
            }

            // Coup valide => reset passes
            passesConsecutifs = 0;

            passerAuJoueurSuivant();
        }

        afficherEtatJeu();
        cout << "La partie est terminée !" << endl;
        Affichage::fermer();
    }

    // ======= Mode 1 : 2 humains, 2 couleurs chacun =======
    else if (mode == 1)
    {
        int passesConsecutifs = 0;
        const int nbHumains = 2;

        while (!estFini() && Affichage::estActif())
        {
            Affichage::afficherPlateau(this);
            afficherEtatJeu();

            int base = (joueurCourantIndex == 0) ? 0 : 2; // 0/1 => humain1 ; 2/3 => humain2

            cout << "C'est au tour de " << joueurs[base]->getNom() << " (2 couleurs)." << endl;

            bool peut0 = plateau.joueurPeutJouer(*joueurs[base]);
            bool peut1 = plateau.joueurPeutJouer(*joueurs[base + 1]);

            // 1) Si aucune des deux couleurs ne peut jouer : l'humain passe
            if (!peut0 && !peut1)
            {
                cout << joueurs[base]->getNom() << " ne peut jouer avec aucune couleur -> passe." << endl;
                passesConsecutifs++;

                if (passesConsecutifs >= nbHumains)
                {
                    cout << "Aucun des 2 joueurs ne peut jouer sur un tour complet -> match nul !" << endl;
                    break;
                }

                passerAuJoueurSuivant(); // modulo 2
                continue;
            }

            // Il peut jouer au moins une couleur => il ne passe pas (pour l’instant)
            cout << "Choisir la couleur a jouer : " << endl;
            cout << "  0 -> "; afficherCouleur(joueurs[base]->getCouleur());
            cout << (peut0 ? "" : " (bloqué)") << endl;

            cout << "  1 -> "; afficherCouleur(joueurs[base+1]->getCouleur());
            cout << (peut1 ? "" : " (bloqué)") << endl;

            int choix = -1;
            cout << "Votre choix (0/1) : ";
            cin >> choix;

            if (!cin || (choix != 0 && choix != 1))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choix invalide." << endl;
                continue;
            }

            // Refuser si la couleur choisie est bloquée
            if ((choix == 0 && !peut0) || (choix == 1 && !peut1))
            {
                cout << "Cette couleur ne peut pas jouer. Choisissez l'autre." << endl;
                continue; // même humain rejoue le choix
            }

            Joueur& joueurCourant = *joueurs[base + choix];

            cout << "Vous jouez la couleur ";
            afficherCouleur(joueurCourant.getCouleur());
            cout << "." << endl;

            if (!joueurCourant.jouerCoup(&plateau))
            {
                cout << "Coup invalide. Veuillez réessayer." << endl;
                continue;
            }

            // Coup valide => reset passes
            passesConsecutifs = 0;

            passerAuJoueurSuivant(); // modulo 2
        }

        afficherEtatJeu();
        cout << "La partie est terminée !" << endl;
        Affichage::fermer();
    }
}


bool Otrio::passerAuJoueurSuivant()
{
    if (mode == 0 || mode == 2)
        joueurCourantIndex = (joueurCourantIndex + 1) % 4;
    else
        joueurCourantIndex = (joueurCourantIndex + 1) % 2;

    return true;
}

bool Otrio::estFini() const
{
    if (mode == 0 || mode == 2)
    {
        for (const auto& joueur : joueurs)
        {
            if (plateau.verifierVictoire(joueur->getCouleur()))
            {
                cout << "Le joueur " << joueur->getNom() << " a gagné la partie !" << endl;
                return true;
            }
        }
        return false;
    }
    
    if (plateau.estPlein())
    {
        cout << "Le plateau est plein. Match nul !" << endl;
        return true;
    }

    // mode 1 : joueurs[0,1] humain 1 ; joueurs[2,3] humain 2
    bool win1 = plateau.verifierVictoire(joueurs[0]->getCouleur()) ||
                plateau.verifierVictoire(joueurs[1]->getCouleur());
    if (win1) {
        cout << "Le joueur " << joueurs[0]->getNom() << " a gagné la partie !" << endl;
        return true;
    }

    bool win2 = plateau.verifierVictoire(joueurs[2]->getCouleur()) ||
                plateau.verifierVictoire(joueurs[3]->getCouleur());
    if (win2) {
        cout << "Le joueur " << joueurs[2]->getNom() << " a gagné la partie !" << endl;
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
        cout << "- " << joueur->getNom() << " (";
        afficherCouleur(joueur->getCouleur());
        cout << ") a " << joueur->getPionRestants().size() << " pions restants." << endl;
    }
}
