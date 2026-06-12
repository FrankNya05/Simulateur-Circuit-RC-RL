# Simulateur de Circuit RC/RL

Simulateur en C de circuits électriques RC et RL, supportant les configurations **série** et **parallèle**. Le programme calcule l'impédance équivalente, la tension et le courant pour chaque composant du circuit.

## Fonctionnalités

- **Configurations supportées** : série et parallèle
- **Composants** : résistances, condensateurs (capacités), inductances
- **Sources de tension** : courant alternatif (AC) et continu (DC)
- **Calculs** :
  - Impédance de chaque composant
  - Impédance équivalente du circuit
  - Tension aux bornes de chaque composant
  - Courant circulant dans le circuit
- Persistance des données dans des fichiers binaires
- Interface menu interactive en terminal

## Structure du projet

```
.
├── src/
│   ├── main.c        # Point d'entrée et interface menu
│   ├── tools.c       # Implémentation des fonctions
│   └── tools.h       # Déclarations des structures et fonctions
├── test/
│   └── test_unit.c   # Tests unitaires
├── lib/              # Bibliothèques externes
└── Makefile
```

## Compilation

```bash
# Compiler le programme principal
make

# Compiler les tests unitaires
make test_unit

# Nettoyer les fichiers compilés
make clean
```

**Prérequis** : `gcc` et `make`

## Utilisation

```bash
./main
```

Le menu principal propose deux modes :
- **S** — Configuration série
- **P** — Configuration parallèle
- **Q** — Quitter

Dans chaque mode, vous pouvez ajouter des composants, des sources de tension, afficher les listes et lancer le calcul des caractéristiques du circuit.

## Langages et outils

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/GCC-blue?style=flat)
![Make](https://img.shields.io/badge/Make-darkgreen?style=flat)
