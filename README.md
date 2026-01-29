# TP6 - TP noté jeu Otrio

SEC 2

- Eloi Tourangin - <eloi.tourangin@eleves.ec-nantes.fr>
- Lucas Oros - <lucas.oros@eleves.ec-nantes.fr>
- Djamael Lahamion - <djamael.lahamion@eleves.ec-nantes.fr>
- Aloïs Guillon - <alois.guillon@eleves.ec-nantes.fr>

Lien github : https://github.com/ECN-SEC-SMP/tp6-note-alois_lucas_djamael_eloi

## Table des matières

- [TP6 - TP noté jeu Otrio](#tp6---tp-noté-jeu-otrio)
  - [Table des matières](#table-des-matières)
  - [Organisation du groupe](#organisation-du-groupe)
    - [Répartition initiale](#répartition-initiale)
  - [Compilation et Exécution](#compilation-et-exécution)
  - [Diagramme des classes](#diagramme-des-classes)
  - [Description des classes](#description-des-classes)
    - [Classe Otrio](#classe-otrio)
      - [Description](#description)
      - [Méthodes](#méthodes)
      - [Tests de Otrio](#tests-de-otrio)
      - [Gestion des Exceptions de Otrio](#gestion-des-exceptions-de-otrio)
    - [Classe Joueur](#classe-joueur)
      - [Description](#description-1)
    - [Classe JoueurHumain](#classe-joueurhumain)
      - [Description](#description-2)
      - [Méthodes principales](#méthodes-principales)
      - [Tests de Joueur](#tests-de-joueur)
      - [Gestion des exceptions de Joueur/JoueurHumain](#gestion-des-exceptions-de-joueurjoueurhumain)
    - [Classe Plateau](#classe-plateau)
      - [Description](#description-3)
      - [Méthodes principales](#méthodes-principales-1)
      - [Tests de Plateau](#tests-de-plateau)
        - [`test_Plateau_v1()`](#test_plateau_v1)
        - [`test_Plateau()`](#test_plateau)
      - [Gestion des exceptions de Plateau](#gestion-des-exceptions-de-plateau)
    - [Classe Case](#classe-case)
      - [Description](#description-4)
      - [Tests de Case](#tests-de-case)
      - [Gestion des exceptions de Case](#gestion-des-exceptions-de-case)
    - [Classe Pion](#classe-pion)
      - [Description](#description-5)
      - [Tests de Pion](#tests-de-pion)
      - [Gestion des exceptions de Pion](#gestion-des-exceptions-de-pion)
  - [Concepts Clés](#concepts-clés)

## Organisation du groupe
Nous avons débuter le projet par une étape de modélisation où chacun a pu proposer une solution.
Puis, nous nous sommes répartis le travail.

### Répartition initiale
Chaque membre du groupe a pris en charge un ensemble cohérent de classes du projet :

- **Lucas** : classe `Otrio` et `Case`, gestion de la boucle de jeu et des tours
- **Eloi** : classes `Plateau` et `Affichage`, affichage du plateau
- **Djamaël** : classes `Joueur`, `JoueurHumain`, gestion des coups joueurs
- **Aloïs** : classe `Pion`, enums (`Couleur`, `Taille`) et tests unitaires

Diagramme de séquence
Itération de jeu




## Compilation et Exécution

Utiliser le script bash :

```bash
./build_and_execute.sh
```

## Diagramme des classes

![Diagramme des classes](assets/diagramme_classes.svg)

## Description des classes

### Classe Otrio

#### Description

La classe `Otrio` est la classe principale du programme.  
Elle gère le déroulement global de la partie en orchestrant :
- l’initialisation des joueurs,
- la gestion du plateau,
- l’enchaînement des tours de jeu,
- la détection de la fin de partie.

Elle constitue le point d’entrée logique du jeu.


#### Méthodes 

| Méthode | Description |
|--------|-------------|
| `initialiserPartie()` | Initialise le plateau et demande les noms des joueurs |
| `lancerBoucleJeu()` | Lance la boucle principale du jeu |
| `estFini()` | Vérifie si un joueur a gagné |
| `passerAuJoueurSuivant()` | Change le joueur courant |
| `afficherEtatJeu()` | Affiche l’état du plateau et des joueurs |

---


#### Tests de Otrio

Dans `main.cpp`, la partie “Test Otrio” n’est pas encore automatisée :  
les tests d’intégration sont réalisés par exécution du programme complet et par interaction avec `JoueurHumain`.

Les classes `Plateau` et `Joueur` étant déjà testées, la robustesse de `Otrio` se valide principalement en conditions réelles d’exécution (enchaînement de tours et détection de victoire).

#### Gestion des Exceptions de Otrio

`Otrio` délègue :
- la validation des entrées utilisateur à `JoueurHumain`,
- la validation des placements à `Plateau`.

Ainsi, aucune exception n’est nécessaire au niveau de `Otrio` pour le déroulement nominal du jeu.


---
### Classe Joueur

#### Description

La classe `Joueur` est une classe abstraite représentant un joueur générique du jeu Otrio.  
Elle définit les attributs communs à tous les joueurs :
- un nom,
- une couleur,
- une main de pions.

Elle impose également l’implémentation de la méthode `jouerCoup`.


---

### Classe JoueurHumain

#### Description

La classe `JoueurHumain` hérite de `Joueur` et représente un joueur réel interagissant via le terminal.  
Elle implémente la logique de saisie utilisateur pour :
- choisir un pion parmi ceux restants,
- sélectionner une position valide sur le plateau.

Cette classe gère également l’affichage de la main du joueur.

#### Méthodes principales

| Méthode | Description |
|--------|-------------|
| `jouerCoup(Plateau*)` | Gère l’interaction utilisateur pour jouer un coup |
| `afficherMain()` | Affiche les pions encore disponibles |

---
#### Tests de Joueur

Le test `test_Joueur()` effectue les vérifications suivantes :

- création d’un `JoueurHumain("Alice", ROUGE)`,
- vérification du nom et de la couleur via `assert`,
- vérification du nombre de pions initiaux (`NB_GROUPES_PIONS * NB_PIONS_PAR_TAILLE`),
- retrait d’un pion de la main et vérification que la taille diminue de 1,
- test d’un coup réel via `jouerCoup(&plateau)` sur un plateau valide, puis affichage du plateau.

Ce test combine vérifications unitaires (assert) et interaction utilisateur.

#### Gestion des exceptions de Joueur/JoueurHumain

Dans notre implémentation, `jouerCoup()` gère les erreurs de saisie de manière robuste :
- si l’entrée n’est pas numérique, le flux est nettoyé puis une nouvelle saisie est demandée,
- si la taille est invalide, l’utilisateur est invité à recommencer,
- si le pion n’existe pas dans la main, un message est affiché et l’utilisateur recommence,
- si le placement échoue (`placerPion` retourne `false`), l’utilisateur recommence.

L’objectif est de ne pas interrompre la partie à cause d’une erreur utilisateur.



### Classe Plateau

#### Description

La classe `Plateau` représente la grille de jeu du Otrio, composée de 9 cases organisées en une grille 3×3.  
Chaque case peut contenir jusqu’à trois pions de tailles différentes (PETIT, MOYEN, GRAND).

La classe est responsable :
- du placement des pions,
- de l’affichage du plateau,
- de la vérification des conditions de victoire.

#### Méthodes principales

| Méthode | Description |
|--------|-------------|
| `placerPion(x, y, pion)` | Place un pion sur le plateau si la position est valide |
| `verifierVictoire(Couleur)` | Vérifie si une couleur satisfait une condition de victoire |
| `afficher()` | Affiche l’état du plateau dans le terminal |
| `getCase(x, y)` | Retourne un pointeur vers une case du plateau |

---
#### Tests de Plateau

Deux fonctions de test sont présentes :

##### `test_Plateau_v1()`

Ce test mélange affichage et jeu interactif :

- création d’un plateau et affichage initial,
- placement de quelques pions “en dur” puis affichage,
- création de deux joueurs (`Alice` ROUGE, `Bob` BLEU),
- `Alice` joue trois coups via `jouerCoup(&plateau)`,
- affichage du plateau puis vérification de victoire avec `plateau.verifierVictoire(j1.getCouleur())`.

Ce test sert principalement de démonstration interactive.

##### `test_Plateau()`

Ce test est plus “unitaire” et utilise `assert` pour valider plusieurs scénarios indépendants :

- **Test 0 : plateau vide** → aucune victoire pour aucune couleur,
- **Test 1 : placements de base** (placements valides, refus sur même taille, refus hors plateau),
- **Test 2 : victoire par alignement identique** (3 PETITS alignés),
- **Test 3 : victoire par alignement croissant** (PETIT → MOYEN → GRAND),
- **Test 4 : victoire par empilement complet** (PETIT+MOYEN+GRAND sur une même case),
- **Test 5 : victoire décroissante** (GRAND → MOYEN → PETIT) sur une diagonale.

> Remarque : dans le code actuel, la couleur `JAUNE` est utilisée dans les tests.  
> Pour rester conforme à l’énoncé Otrio, il faut remplacer `JAUNE` par `VIOLET`.

#### Gestion des exceptions de Plateau

La classe `Plateau` n’interrompt pas le programme par exception lors des erreurs de jeu courantes.  
Les cas invalides sont gérés par retour `false`, par exemple :

- coordonnées hors plateau (`x` ou `y` hors `[0..2]`),
- pointeur de pion nul,
- placement refusé par une `Case` (taille déjà occupée).

Ce choix simplifie la gestion dans `JoueurHumain::jouerCoup()` (qui peut redemander une saisie).

### Classe Case

#### Description

La classe `Case` représente une position du plateau.  
Elle peut contenir au maximum un pion de chaque taille (PETIT, MOYEN, GRAND).

Elle assure :
- la vérification de la disponibilité d’une taille,
- l’interdiction de placer deux pions de même taille sur une même case.

#### Tests de Case

Le test `test_Case()` vérifie les comportements suivants :

- placement d’un pion PETIT puis MOYEN dans une case vide,
- vérification de l’état via `estVide(Taille)` (PETIT et MOYEN occupés, GRAND libre),
- récupération correcte via `getPion(Taille)`,
- retrait d’un pion (`retirerPion(MOYEN)`) et vérification que la case redevient vide sur cette taille,
- re-placement du pion MOYEN puis placement du pion GRAND pour constituer un empilement complet.

Ces tests permettent de garantir les invariants fondamentaux d’une case.

#### Gestion des exceptions de Case

La classe `Case` ne lève pas d’exception dans le flux normal de jeu.  
Les actions invalides (ex : placer un pion sur une taille déjà occupée) sont gérées par retour `false` (selon l’implémentation), ce qui facilite la gestion d’erreur dans `Plateau` et `JoueurHumain`.

---

### Classe Pion

#### Description

La classe `Pion` représente une pièce du jeu Otrio.  
Chaque pion est caractérisé par :
- une couleur,
- une taille.

Les pions sont utilisés par les joueurs pour tenter de remplir les conditions de victoire.

#### Tests de Pion

Le test `test_Pion()` valide la création et l’intégrité des attributs de plusieurs pions :

- création de trois pions : `(ROUGE, PETIT)`, `(BLEU, MOYEN)`, `(VERT, GRAND)`,
- vérification avec `assert` que `getCouleur()` et `getTaille()` retournent les valeurs attendues.

L’objectif est de garantir que la classe se comporte comme un simple conteneur de données fiable pour le reste du projet.

#### Gestion des exceptions de Pion

La classe `Pion` ne déclenche pas d’exception dans notre implémentation :  
les valeurs sont encadrées par des enums et les invariants sont garantis par conception.

---

## Concepts Clés
