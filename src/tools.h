#ifndef TOOLS_H
#define TOOLS_H

// N.B il ne faut pas melanger des sources alternatives et continue faire une fonction qui bloquera ca.

typedef struct{
    char Nom[50];
    char TypeSource[50];
    float Amplitude;
    float frequence;
    char sens[50]; //positif ou negatif
}SourceTension;

typedef struct{
    char composant_01[50];
    float Valeur_01;
    float impedance;
    char type[50]; // /*\ Ecrire soit resistance soit capacite soit inductance    Tout autre entrée entrainera une erreur

}Composants;

struct CelluleSource{
    SourceTension source;
    struct CelluleSource * suivant;
};

typedef struct CelluleSource celluleSource;

struct CelluleComposant{
    Composants composants;
    struct CelluleVoltmetre *Voltmetre;
    struct CelluleComposant * suivant;
};

typedef struct CelluleComposant celluleComposant;

typedef struct{
    float Tension;
    float intensite;
    float TensionTotale;
    float impedanceEquivalente;
    char Nom[50];
}Voltmetre;

struct CelluleVoltmetre{
    Voltmetre voltmetre;
    struct CelluleVoltmetre * suivant;
};

typedef struct CelluleVoltmetre celluleVoltmetre;


// Fonction d'initialisation, d'ajout et d'afichage ds sp=ources de tension
SourceTension initialiseSource(char Nom[], char *typeSource[], float amplitude, float frequence, char *sens[]);
celluleSource* CreerCelluleSource();
void updateCelluleSource(SourceTension source, celluleSource *cellSource);
void ajouterEnfinSource(celluleSource **liste, celluleSource *cellSource);
int NombreDesource(celluleSource * Liste);
void afficherSource(SourceTension source);
void afficherListeSource(celluleSource * liste);

// Fonction d'initialisation, d'ajout et d'affichage des composants

Composants initialiseComposant(char Nom_01[], float Valeur_01, char type[]);
void updateCelluleComposant(Composants Composant, celluleComposant *cell);
celluleComposant * CreerCelluleComposant();
void ajouterEnfinComposant(celluleComposant **liste , celluleComposant *cell);
int NombreDecomposant(celluleComposant * Liste);
void afficherComposant(Composants composant);
void afficherListeComposant(celluleComposant * liste);

// Gestion des voltmetres

celluleVoltmetre * CreerCelluleVoltmetre();
void updateCelluleVoltmetre(Voltmetre Voltmetre, celluleVoltmetre * cell);
void ajouterEnfinVoltmetre(celluleVoltmetre **liste , celluleVoltmetre *cell);
int NombreDeVoltmetre(celluleVoltmetre *Liste);
void afficheVoltmetre(Voltmetre voltmetre);
void afficherlisteVoltmetre(celluleVoltmetre * liste);


int comparerChaines(char *chaine1[], char *chaine2[]);

void sauvegarderSourceSerie(celluleSource *listesource, char *nomfichier[]);

void supprimerfichier(char *nomfichier[]);

void sauvegarderComposantSerie(celluleComposant *listecomposant, char *nomfichier[]);

// Calcul de l'impedance de chaque composant

float calculImpedance(Composants composant, char typeSource[], celluleSource *listeSource);
float ImpedanceequivalenteSerie(celluleComposant *liste);
float TensionSeries(celluleSource *liste);
float CourantSerie(Voltmetre voltmetre);
void CalculTension(celluleComposant **listeComposant, Voltmetre multimetre);
float trouverFrequenceMaximum(celluleSource *liste);

//Charger fichier
void chargerCompoSerie(celluleComposant **listeCompo, const char *fileCompo);
void chargerSourceSerie(celluleSource **liste, const char *fileSource);


/***Tension parallele***/

void sauvegarderComposantParallele(celluleComposant *listecomposant, char *nomfichier[]);
void sauvegarderSourceParallele(celluleSource *listesource, char *nomfichier[]);
void chargerCompoParallele(celluleComposant **listeCompo, const char *fileCompo);
void chargerSourceParallele(celluleSource **liste, const char *fileSource);
float ImpedanceequivalenteParallele(celluleComposant *liste);
float trouverTensionMaximum(celluleSource *liste);
float TensionParallele(celluleSource *liste);
void CalculCourant(celluleComposant **listeComposant, Voltmetre multimetre);


#endif
