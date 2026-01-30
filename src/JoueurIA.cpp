#include "JoueurIA.hpp"
#include "Case.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

JoueurIA::JoueurIA(std::string nom, Couleur couleur)
: Joueur(nom, couleur)
{}

void JoueurIA::setContexte(const std::vector<Joueur*>& joueurs, int myIndex)
{
    joueurs_ = joueurs;
    myIndex_ = myIndex;
}

JoueurIA::Board JoueurIA::lirePlateau(const Plateau* plateau) const
{
    Board b;
    for (int y=0;y<3;y++)
        for (int x=0;x<3;x++)
            for (int t=0;t<3;t++)
                b[y][x][t] = -1;

    for (int y=0;y<3;y++)
    {
        for (int x=0;x<3;x++)
        {
            const Case* c = plateau->getCase(x,y);
            for (int ti=0; ti<3; ++ti)
            {
                Taille t = (Taille)ti;
                Pion* p = c->getPion(t);
                if (p) b[y][x][ti] = (int)p->getCouleur();
            }
        }
    }
    return b;
}

static bool isStrictInc(int a,int b,int c){ return a<b && b<c; }
static bool isStrictDec(int a,int b,int c){ return a>b && b>c; }
static bool isAllEq(int a,int b,int c){ return a==b && b==c; }

bool JoueurIA::victoireCouleur(const Board& b, Couleur c) const
{
    int col = (int)c;

    // Empilement complet (3 tailles sur une case)
    for(int y=0;y<3;y++)
    for(int x=0;x<3;x++)
    {
        if (b[y][x][0]==col && b[y][x][1]==col && b[y][x][2]==col)
            return true;
    }

    auto lineWin = [&](int x0,int y0,int dx,int dy)->bool
    {
        // pour chaque case, lister les tailles présentes pour la couleur c
        array<vector<int>,3> options;
        for(int k=0;k<3;k++)
        {
            int x = x0 + k*dx;
            int y = y0 + k*dy;
            for(int ti=0;ti<3;ti++)
                if(b[y][x][ti]==col) options[k].push_back(ti);
            if(options[k].empty()) return false;
        }

        // brute-force : une taille choisie par case (<= 27 combinaisons)
        for(int a: options[0])
        for(int bb: options[1])
        for(int cc: options[2])
        {
            if (isAllEq(a,bb,cc) || isStrictInc(a,bb,cc) || isStrictDec(a,bb,cc))
                return true;
        }
        return false;
    };

    // lignes
    for(int y=0;y<3;y++) if(lineWin(0,y,1,0)) return true;
    // colonnes
    for(int x=0;x<3;x++) if(lineWin(x,0,0,1)) return true;
    // diagonales
    if(lineWin(0,0,1,1)) return true;
    if(lineWin(0,2,1,-1)) return true;

    return false;
}

int JoueurIA::eval(const Board& b) const
{
    // Heuristique simple :
    // +10000 si IA gagne, -10000 si un adversaire gagne
    if (victoireCouleur(b, couleur)) return 10000;
    if (!joueurs_.empty())
    {
        for (auto* j : joueurs_)
        {
            if (!j) continue;
            Couleur c = j->getCouleur();
            if (c != couleur && victoireCouleur(b, c)) return -10000;
        }
    }

    // Bonus léger : encourager empilements partiels au centre
    int score = 0;
    int me = (int)couleur;
    for(int ti=0;ti<3;ti++)
        if (b[1][1][ti]==me) score += 3;

    return score;
}

bool JoueurIA::appliquer(Board& b, Couleur c, const Move& m) const
{
    int ti = (int)m.t;
    if (m.x<0 || m.x>=3 || m.y<0 || m.y>=3) return false;
    if (b[m.y][m.x][ti] != -1) return false;
    b[m.y][m.x][ti] = (int)c;
    return true;
}

vector<JoueurIA::Move> JoueurIA::coupsPossibles(const Board& b, Couleur c, const array<int,3>& stock) const
{
    vector<Move> moves;
    int col = (int)c;

    for (int ti=0; ti<3; ++ti)
    {
        if (stock[ti] <= 0) continue;
        for (int y=0;y<3;y++)
        for (int x=0;x<3;x++)
        {
            if (b[y][x][ti]==-1)
                moves.push_back({x,y,(Taille)ti});
        }
    }

    // petit tri : privilégier centre puis coins
    auto key = [](const Move& m){
        if(m.x==1 && m.y==1) return 0;
        if((m.x==0||m.x==2) && (m.y==0||m.y==2)) return 1;
        return 2;
    };
    stable_sort(moves.begin(), moves.end(), [&](const Move& a,const Move& b){
        return key(a)<key(b);
    });

    return moves;
}

Couleur JoueurIA::couleurIndexToCouleur(int idx) const
{
    return joueurs_[idx]->getCouleur();
}

int JoueurIA::minimax(Board b,
                      vector<array<int,3>> stocks,
                      int playerIndex,
                      int depth,
                      int alpha,
                      int beta) const
{
    if (depth == 0) return eval(b);

    Couleur c = couleurIndexToCouleur(playerIndex);

    // terminal : si quelqu'un a gagné, stop
    if (victoireCouleur(b, couleur)) return 10000;
    for (auto* j : joueurs_)
        if (j && j->getCouleur()!=couleur && victoireCouleur(b, j->getCouleur()))
            return -10000;

    auto moves = coupsPossibles(b, c, stocks[playerIndex]);
    if (moves.empty()) return eval(b);

    bool isMax = (c == couleur);

    if (isMax)
    {
        int best = -1000000;
        for (const auto& m : moves)
        {
            Board b2 = b;
            if(!appliquer(b2, c, m)) continue;

            auto stocks2 = stocks;
            stocks2[playerIndex][(int)m.t]--;

            int next = (playerIndex + 1) % (int)joueurs_.size();
            int val = minimax(b2, stocks2, next, depth-1, alpha, beta);

            best = max(best, val);
            alpha = max(alpha, best);
            if (beta <= alpha) break;
        }
        return best;
    }
    else
    {
        int best = 1000000;
        for (const auto& m : moves)
        {
            Board b2 = b;
            if(!appliquer(b2, c, m)) continue;

            auto stocks2 = stocks;
            stocks2[playerIndex][(int)m.t]--;

            int next = (playerIndex + 1) % (int)joueurs_.size();
            int val = minimax(b2, stocks2, next, depth-1, alpha, beta);

            best = min(best, val);
            beta = min(beta, best);
            if (beta <= alpha) break;
        }
        return best;
    }
}

bool JoueurIA::trouverCoupPourGagner(const Board& b, Move& best) const
{
    // Coup gagnant immédiat : on essaie tous les placements possibles de l'IA
    array<int,3> myStock = {0,0,0};
    for (Pion* p : main) myStock[(int)p->getTaille()]++;

    auto moves = coupsPossibles(b, couleur, myStock);
    for (const auto& m : moves)
    {
        Board b2 = b;
        if(!appliquer(b2, couleur, m)) continue;
        if (victoireCouleur(b2, couleur))
        {
            best = m;
            return true;
        }
    }
    return false;
}

bool JoueurIA::trouverCoupPourBloquer(const Board& b, Move& best) const
{
    // Menace immédiate : si un adversaire peut gagner en 1 coup,
    // on joue un coup qui empêche (même case+taille).
    // -> on cherche une case/size vide qui donnerait victoire à un adversaire.
    // -> si oui, on essaie de placer NOTRE pion sur ce slot.
    array<int,3> myStock = {0,0,0};
    for (Pion* p : main) myStock[(int)p->getTaille()]++;

    if (joueurs_.empty()) return false;

    for (auto* adv : joueurs_)
    {
        if (!adv) continue;
        Couleur cAdv = adv->getCouleur();
        if (cAdv == couleur) continue;

        // On suppose que l'adversaire a potentiellement du stock (approx),
        // ou on peut compter via adv->getPionRestants() si dispo.
        array<int,3> advStock = {3,3,3};
        auto rest = adv->getPionRestants();
        advStock = {0,0,0};
        for (Pion* p : rest) advStock[(int)p->getTaille()]++;

        auto advMoves = coupsPossibles(b, cAdv, advStock);
        for (const auto& threat : advMoves)
        {
            Board b2 = b;
            if(!appliquer(b2, cAdv, threat)) continue;
            if (victoireCouleur(b2, cAdv))
            {
                // On tente de bloquer exactement ce slot (x,y,taille)
                if (myStock[(int)threat.t] > 0 && b[threat.y][threat.x][(int)threat.t]==-1)
                {
                    best = threat;
                    return true;
                }
            }
        }
    }
    return false;
}

bool JoueurIA::jouerCoup(Plateau* plateau)
{
    if (!plateau) return false;
    if (joueurs_.empty() || myIndex_ < 0) {
        cout << "[IA] Contexte non defini (appel setContexte dans Otrio).\n";
        return false;
    }

    cout << "[IA] Tour de " << nom << " (" << (int)couleur << ")\n";

    // Stocks (strict) : comptage des pions restants par joueur et taille
    vector<array<int,3>> stocks(joueurs_.size(), {0,0,0});
    for (int i=0;i<(int)joueurs_.size();++i)
    {
        auto rest = joueurs_[i]->getPionRestants();
        for (Pion* p : rest) stocks[i][(int)p->getTaille()]++;
    }

    Board b = lirePlateau(plateau);

    // 1) Gagner immédiatement si possible
    Move chosen;
    if (trouverCoupPourGagner(b, chosen))
    {
        // trouver le pion dans la main correspondant
        Pion* pionChoisi = nullptr;
        for (Pion* p : main)
            if ((int)p->getTaille()==(int)chosen.t) { pionChoisi = p; break; }

        if (!pionChoisi) return false;

        if (plateau->placerPion(chosen.x, chosen.y, pionChoisi))
        {
            retirerPionDeMain(pionChoisi);
            cout << "[IA] Coup gagnant: (" << chosen.x << "," << chosen.y << ") taille=" << (int)chosen.t << "\n";
            return true;
        }
    }

    // 2) Bloquer une menace immédiate
    if (trouverCoupPourBloquer(b, chosen))
    {
        Pion* pionChoisi = nullptr;
        for (Pion* p : main)
            if ((int)p->getTaille()==(int)chosen.t) { pionChoisi = p; break; }

        if (pionChoisi && plateau->placerPion(chosen.x, chosen.y, pionChoisi))
        {
            retirerPionDeMain(pionChoisi);
            cout << "[IA] Blocage menace: (" << chosen.x << "," << chosen.y << ") taille=" << (int)chosen.t << "\n";
            return true;
        }
        // si blocage impossible (pas de pion de cette taille), on continue en planification
    }

    // 3) Planification : minimax sur plusieurs coups (>= 3 plies)
    // Ici depth=5 plies = IA, adv, adv, adv, IA (selon nb joueurs)
    // Tu peux augmenter à 7 si ça reste fluide.
    int depth = 5;

    // coups candidats IA
    auto moves = coupsPossibles(b, couleur, stocks[myIndex_]);
    if (moves.empty()) return false;

    int bestScore = -1000000;
    Move bestMove = moves[0];

    for (const auto& m : moves)
    {
        Board b2 = b;
        if(!appliquer(b2, couleur, m)) continue;

        auto stocks2 = stocks;
        stocks2[myIndex_][(int)m.t]--;

        int next = (myIndex_ + 1) % (int)joueurs_.size();
        int score = minimax(b2, stocks2, next, depth-1, -1000000, 1000000);

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = m;
        }
    }

    // jouer bestMove sur le vrai plateau
    Pion* pionChoisi = nullptr;
    for (Pion* p : main)
        if ((int)p->getTaille()==(int)bestMove.t) { pionChoisi = p; break; }

    if (!pionChoisi) return false;

    if (plateau->placerPion(bestMove.x, bestMove.y, pionChoisi))
    {
        retirerPionDeMain(pionChoisi);
        cout << "[IA] Planification: (" << bestMove.x << "," << bestMove.y << ") taille=" << (int)bestMove.t
             << " score=" << bestScore << "\n";
        return true;
    }

    return false;
}
JoueurIA::~JoueurIA()
{}