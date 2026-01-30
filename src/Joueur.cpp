#include "Joueur.hpp"

Joueur::Joueur(string nom, Couleur couleur)
    : nom(nom), couleur(couleur)
{
    main = vector<Pion*>();
    for (int i = 0; i < NB_GROUPES_PIONS; i++)
    {
        for (int j = 0; j < NB_PIONS_PAR_TAILLE; j++)
        {
            main.push_back(new Pion(couleur, static_cast<Taille>(j)));
        }
    }
    
}

Joueur::~Joueur()
{
    // for (Pion* p : main) delete p;
    // main.clear();
}

string Joueur::getNom() const
{
    return nom;
}

Couleur Joueur::getCouleur() const
{
    return couleur;
}

void Joueur::afficherMain() const
{
    cout << "Pions disponibles de " << nom << " :\n";

    if (main.empty())
    {
        cout << "  (aucun pion)\n";
        return;
    }

    for (const Pion* p : main)
    {
        cout << "  - Taille: " << p->getTailleStr()
             << ", Couleur: " << p->getCouleurStr() << '\n';
    }
}


vector<Pion*> Joueur::getPionRestants() const
{
    return main;
}

void Joueur::retirerPionDeMain(Pion* p)
{
    auto it = find(main.begin(), main.end(), p);
    if (it != main.end())
    {
        main.erase(it);
    }
}