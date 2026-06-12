#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "../src/tools.h"



// Charger les données des fichiers dans les differentes listes chainés

void chargerCompoSerie(celluleComposant **listeCompo, const char *fileCompo)
{
    FILE *fichier = fopen(fileCompo, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", fileCompo);
        return;
    }

    Composants compo;
    float impedance;
    char nom[50];
    char type[50];
    float valeur;
    while (fscanf(fichier, "%s  %f  %f  %s", nom, &valeur, &impedance, type) != EOF)
    {
        celluleComposant *cell;
        cell = CreerCelluleComposant();
        compo = initialiseComposant(nom, valeur, type);
        compo.impedance = impedance;
        updateCelluleComposant(compo,cell);
        ajouterEnfinComposant(listeCompo, cell);
    }

    fclose(fichier);
}

void chargerSourceSerie(celluleSource **liste, const char *fileSource){
    FILE *fichier = fopen(fileSource, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", fileSource);
        return;
    }

    SourceTension source;
    char nom[50];
    float amplitude;
    float frequence;
    char sens[50];
    char type[50];
    while (fscanf(fichier, "%s  %f  %f  %s  %s", nom, &amplitude, &frequence, sens, type) != EOF)
    {
        celluleSource *cell;
        cell = CreerCelluleSource();
        source = initialiseSource(nom, type, amplitude, frequence, sens);
        updateCelluleSource(source,cell);
        ajouterEnfinSource(liste, cell);
    }

    fclose(fichier);
}

float trouverFrequenceMaximum(celluleSource *liste) {
    if (liste == NULL) {
        printf("La liste est vide.\n");
        return 0.0;
    }

    float maximum = liste->source.frequence;
    celluleSource *actuel = liste->suivant;

    while (actuel != NULL) {
        if (actuel->source.frequence > maximum) {
            maximum = actuel->source.frequence;
        }
        actuel = actuel->suivant;
    }

    return maximum;
}


//Liste des Composants

//Initialisation, ajout et affichage des sources de tension du circuit

//Intialisation des sources de tension

int comparerChaines(char *chaine1[],char *chaine2[]) {
    return strcmp(chaine1, chaine2);
}
//test
SourceTension initialiseSource(char Nom[], char *typeSource[], float amplitude, float frequence, char *sens[]){
    SourceTension source;
    char chaine2[] = "DC";
    char chaine3[] = "AC";
    char chaine4[]= "positif";
    char chaine5[]= "negatif";

    int resultat1= comparerChaines(&chaine2,typeSource);
    int resultat2= comparerChaines(&chaine3,typeSource);
    int resultat3= comparerChaines(&chaine4,sens);
    int resultat4= comparerChaines(&chaine5,sens);
    //Comparaison permet de detecter si le type de source entré par l'utilisateur est valide ou non en cas d'invalidité il sera ramené au menu
    
    if((resultat3==0)||(resultat4==0)){
        
        if(((resultat1==0)||(resultat2==0))){
            strcpy(source.Nom, Nom);
            strcpy(source.TypeSource, typeSource);
            source.Amplitude = amplitude;
            source.frequence = frequence;
            strcpy(source.sens, sens);
            return source;
        }
        else{
            printf("\n");
            printf("*******Veillez Entrer un type de source valide:  AC  ou   DC*******\n");
            return source;
        }
    }
    else{
        printf("Le sens que vous avez entré est invalide! ***Veillez entrer un sens valide***\n");
        return source;
    }

}

//Creation d'une cellule source de tension
celluleSource* CreerCelluleSource(){
    celluleSource * cellSource = (celluleSource *)malloc(sizeof(celluleSource));
    cellSource->suivant = NULL;
    return cellSource;
}

//Mise à jour de la cellule 
void updateCelluleSource(SourceTension source, celluleSource * cellSource){
    cellSource->source = source;
}

//Ajout de la cellule à la fin de la liste des sources de tension
void ajouterEnfinSource(celluleSource **liste, celluleSource * cellSource){
    celluleSource * p = *liste;
    if(*liste == NULL){
        *liste = cellSource;
        return;
    }
    while(p->suivant != NULL){
        p = p->suivant;
        }
    p->suivant = cellSource; 
}

//Decomptage du nombre de sources de tension
int NombreDesource(celluleSource *Liste){
    int nbSource = 0;
    celluleSource *p = Liste;
    while( p != NULL){
        p = p->suivant;
        nbSource++;
    }
    return nbSource;
}

//Permet d'afficher la souce entré 
void afficherSource(SourceTension source){
    printf("Nom de la source: %s ||| Tension de la source: %.2f ||| Frequence de la source: %.2f ||| Sens de connection: %s \n", source.Nom, source.Amplitude, source.frequence, source.sens);
    printf("----------------------------------------------------------------------------------------------------------------------|\n");
}

void supprimerfichier(char *nomfichier[]){
    remove(nomfichier);
}

//Affichage de la liste des sources de tension
void afficherListeSource(celluleSource * liste){
     
    if(liste == NULL){
        printf("Vous n'avez pas encore de source de tension dans votre circuit\n");
        return;
    }
    celluleSource * p = liste;
    while( p != NULL ){      
        afficherSource(p->source);
        p=p->suivant;
    }
}

//Sauvegarder les sources de tensions dans un fichier

void sauvegarderSourceSerie(celluleSource *listesource, char *nomfichier[]) {
    FILE* file1 = fopen(nomfichier, "w");
    
    // Vérifier si le fichier est ouvert avec succès
    if (file1 == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    // Parcourt la liste et enregistre chaque élément dans le fichier
    celluleSource* p = listesource;
    while (p != NULL) {
        fprintf(file1,"%s  %.2f  %.2f  %s  %s\n", p->source.Nom, p->source.Amplitude, p->source.frequence, p->source.sens, p->source.TypeSource); // Écrit les données dans le fichier
        p = p->suivant; // Passe à la cellule suivante
    }
    
    // Ferme le fichier
    fclose(file1);
}


//Initialisation, ajout et affichage des composants du circuit

//Initialisation du composant

Composants initialiseComposant(char Nom_01[], float Valeur_01, char type[]){
    Composants composant;
    char chaine1[] = "resistance";
    char chaine2[] = "capacite";
    char chaine3[] = "inductance";
    int resultat1=comparerChaines(type,chaine1);
    int resultat2= comparerChaines(type,chaine2);
    int resultat3= comparerChaines(type,chaine3);
    if((resultat1==0)||(resultat2==0)||(resultat3==0)){
    strcpy(composant.composant_01, Nom_01);
    strcpy(composant.type, type);
    composant.Valeur_01 = Valeur_01;
    return composant;
    }
    printf("VOUS AVEZ ENTRÉ UN TYPE DE COMPOSANT INVALIDE! VEILLEZ EN ENTRER UN NOUVEAU\n");
    return composant;
}

// Creation d'une cellule composant

celluleComposant * CreerCelluleComposant(){
    celluleComposant * cell = (celluleComposant *)malloc(sizeof(celluleComposant) );
    cell->suivant= NULL;
    return cell;
}

//Mise à jour de la cellule composant

void updateCelluleComposant(Composants Composant, celluleComposant * cell){
     cell->composants = Composant;
}

//Ajout du nouveau composant à la fin de la liste

void ajouterEnfinComposant(celluleComposant **liste , celluleComposant *cell){
    //celluleComposant * liste;   
    //celluleComposant * p = listeComposant;
    if(*liste == NULL){
        *liste = cell;
        return;
    }
  celluleComposant * p = *liste;
    while(p->suivant != NULL){
        p = p->suivant;
        }
    p->suivant = cell; 
    
}

// Decomptage du nombre de composant

int NombreDecomposant(celluleComposant *Liste){
    int nbComposant = 0;
    celluleComposant *p = Liste;
    while( p != NULL){
        p = p->suivant;
        nbComposant++;
    }
    return nbComposant;
}

// Permet d'afficher les composants

void afficherComposant(Composants composant){
    printf("Nom du Composant: %s ||| Valeur: %.2f ||| Type: %s ||| Impedance: %f \n", composant.composant_01, composant.Valeur_01, composant.type, composant.impedance);
    printf("------------------------------------------------------------------------\n");
}

// Affichage de la liste des composants

void afficherListeComposant(celluleComposant * liste){
    
    if(liste == NULL){
        printf("Il n'y a aucun composant dans la liste\n");
        return;
    }
    celluleComposant * p = liste;
    while( p != NULL ){

         
        afficherComposant(p->composants);
        p=p->suivant;
    
    }
}


void sauvegarderComposantSerie(celluleComposant *listecomposant, char *nomfichier[]) {
    FILE* file1 = fopen(nomfichier, "w");
    
    // Vérifier si le fichier est ouvert avec succès
    if (file1 == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    // Parcourt la liste et enregistre chaque élément dans le fichier
    celluleComposant* p = listecomposant;
    while (p != NULL) {
        fprintf(file1,"  %s  %.2f  %f  %s \n", p->composants.composant_01, p->composants.Valeur_01, p->composants.impedance, p->composants.type); // Écrit les données dans le fichier
        p = p->suivant; // Passe à la cellule suivante
    }
    
    // Ferme le fichier
    fclose(file1);
}

// CREATION DE LA LISTE DES VOLTMETRE


// Creation d'une cellule Voltmetre

celluleVoltmetre * CreerCelluleVoltmetre(){
    celluleVoltmetre * cell = (celluleVoltmetre *)malloc(sizeof(celluleVoltmetre) );
    cell->suivant= NULL;
    return cell;
}

//Mise à jour de la cellule voltmtre

void updateCelluleVoltmetre(Voltmetre Voltmetre, celluleVoltmetre * cell){
     cell->voltmetre = Voltmetre;
}

//Ajout du nouveau composant à la fin de la liste

void ajouterEnfinVoltmetre(celluleVoltmetre **liste , celluleVoltmetre *cell){
    //celluleComposant * liste;   
    //celluleComposant * p = listeComposant;
    if(*liste == NULL){
        *liste = cell;
        return;
    }
  celluleVoltmetre * p = *liste;
    while(p->suivant != NULL){
        p = p->suivant;
        }
    p->suivant = cell; 
    
}

// Decomptage du nombre de composant

int NombreDeVoltmetre(celluleVoltmetre *Liste){
    int nbComposant = 0;
    celluleVoltmetre *p = Liste;
    while( p != NULL){
        p = p->suivant;
        nbComposant++;
    }
    return nbComposant;
}

// Permet d'afficher les composants

void afficheVoltmetre(Voltmetre voltmetre){
    printf("Nom : %s ||| Tension: %.2f V ||| Intensite: %.2f A\n",voltmetre.Nom , voltmetre.Tension, voltmetre.intensite);
    printf("--------------------------------------------------\n");
}

// Affichage de la liste des composants

void afficherlisteVoltmetre(celluleVoltmetre * liste){
    
    if(liste == NULL){
        printf("Il n'y a aucun voltmetre branché dans le circuit\n");
        return;
    }
    celluleVoltmetre * p = liste;
    while( p != NULL ){

         
        afficheVoltmetre(p->voltmetre);
        p=p->suivant;
    
    }
}

 
  //                              //
 //*** CALCUL DES IMPEDANCES  ***//
//------------------------------//  

float calculImpedance(Composants composant, char typeSource[], celluleSource *listeSource){
    // Identification du type de composant pour utiliser la formule d'impedance approprié
    char chaine1[] = "resistance";
    char chaine2[] = "capacite";
    char chaine3[] = "inductance";
    char chaine4[] = "AC";
    char chaine5[] = "DC";
    int resultat1= comparerChaines(composant.type,chaine1);
    int resultat2= comparerChaines(composant.type,chaine2);
    int resultat3= comparerChaines(composant.type,chaine3);
    celluleSource *p = listeSource;
    float maxfrequence =  trouverFrequenceMaximum(p);
    float pulsation = 2*M_PI* maxfrequence;
    int resultat4= comparerChaines(typeSource, chaine4);
    int resultat5= comparerChaines(typeSource, chaine5);
    if(resultat1 == 0){
        printf("Ce composant est une résitance.\n");
        composant.impedance = composant.Valeur_01;
        return composant.impedance;
    }
        else{
            if(resultat2 == 0){
                printf("Ce composant est une capacité.\n");
                float c;
                if(resultat4 == 0){
                    // Cas ou la source est en mode alternatif
                    c = 1/((composant.Valeur_01)*pulsation);
                    composant.impedance = c;
                    return composant.impedance;
                }
                // Cas ou la source est en mode continue (circuit ouvert)
                printf("Circuit ouvert : une capacite bloque le courant continu.\n");
                c = 1000000.0;
                return c;
            }

            printf("Ce composant est une inductance.\n");
            float l;
            if(resultat4 == 0){
              // Cas ou la source est en mode alternatif
                l = (composant.Valeur_01)*pulsation;
                composant.impedance = l;
                return composant.impedance;
           }

            // Cas ou nous sommes dans un cas DC

            l = 0;

            return l;
        }
        printf("Ce composant est d'un type invalide.\n");
        return 0;
}

float ImpedanceequivalenteSerie(celluleComposant *liste){
    celluleComposant * p = liste;
    Voltmetre Voltmetre;
    
    if(liste == NULL){
        printf("Aucun composant n'a été entrée, Veillez entrer au moins un composant.\n");
        return 0;
    }

    float Impedance;
    float ImpedanceEquivalent = 0;

    while(p != NULL){
       ImpedanceEquivalent = ImpedanceEquivalent + p->composants.impedance;
       p = p->suivant;
    }
    Voltmetre.impedanceEquivalente = ImpedanceEquivalent;
    return Voltmetre.impedanceEquivalente;

}


// Calcul de la somme des Tensions generatrices

float TensionSeries(celluleSource *liste){
    if(liste == NULL){
        printf("Vous n'avez entré aucune source de tension. Veillez en entrer au moins une pour continuer.\n");
        printf("\n");
        return 0;
    }

    celluleSource * p = liste;
    float TensionTotale = 0;
    Voltmetre Voltmetre;

    while(p != NULL){
        char chaine4[] = "AC";
        char chaine5[] = "DC";
        char chaine6[] = "positif";
        char chaine7[] = "negatif";

        int resultat1 = comparerChaines(&(p->source.TypeSource),chaine4);
        int resultat2 = comparerChaines(&(p->source.TypeSource),chaine5);
        int resultat3 = comparerChaines(&(p->source.sens),chaine6);
        int resultat4 = comparerChaines(&(p->source.sens),chaine7);

        if(resultat3 == 0){
            printf("\n");
            TensionTotale = TensionTotale + p->source.Amplitude;
        }
        else if(resultat4 == 0){
            TensionTotale = TensionTotale - p->source.Amplitude;
        }
        else{
            printf("***Vous avez mal connecté vos sources de tension. Veillez réessayer.***\n");
        }

        p = p->suivant;
    }
    Voltmetre.TensionTotale = TensionTotale;
    printf("La tension totale du circuit est: %.3f \n", TensionTotale);

    return Voltmetre.TensionTotale;
}

float CourantSerie(Voltmetre voltmetre){

    float intensite;

    intensite = voltmetre.TensionTotale / (voltmetre.impedanceEquivalente);

    //voltmetre.intensite = intensite;

    return intensite; 
}

void CalculTension(celluleComposant **listeComposant, Voltmetre multimetre){
    celluleComposant *p = *listeComposant;
    int i=1;

    while(p != NULL){
        float Tension;  
        Tension = p->composants.impedance * multimetre.intensite;
        printf("La tension aux bornes du composant %d est de  %f \n", i, Tension);
        i = i+1;
        p= p->suivant;
    }
}


//CONFIGURATION PARALLELE

void sauvegarderComposantParallele(celluleComposant *listecomposant, char *nomfichier[]) {
    FILE* file1 = fopen(nomfichier, "w");
    
    // Vérifier si le fichier est ouvert avec succès
    if (file1 == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    // Parcourt la liste et enregistre chaque élément dans le fichier
    celluleComposant* p = listecomposant;
    while (p != NULL) {
        fprintf(file1,"  %s  %.2f  %f  %s \n", p->composants.composant_01, p->composants.Valeur_01, p->composants.impedance, p->composants.type); // Écrit les données dans le fichier
        p = p->suivant; // Passe à la cellule suivante
    }
    
    // Ferme le fichier
    fclose(file1);
}

void sauvegarderSourceParallele(celluleSource *listesource, char *nomfichier[]) {
    FILE* file1 = fopen(nomfichier, "w");
    
    // Vérifier si le fichier est ouvert avec succès
    if (file1 == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    // Parcourt la liste et enregistre chaque élément dans le fichier
    celluleSource* p = listesource;
    while (p != NULL) {
        fprintf(file1,"%s  %.2f  %.2f  %s  %s\n", p->source.Nom, p->source.Amplitude, p->source.frequence, p->source.sens, p->source.TypeSource); // Écrit les données dans le fichier
        p = p->suivant; // Passe à la cellule suivante
    }
    
    // Ferme le fichier
    fclose(file1);
}


void chargerCompoParallele(celluleComposant **listeCompo, const char *fileCompo)
{
    FILE *fichier = fopen(fileCompo, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", fileCompo);
        return;
    }

    Composants compo;
    float impedance;
    char nom[50];
    char type[50];
    float valeur;
    while (fscanf(fichier, "%s  %f  %f  %s", nom, &valeur, &impedance, type) != EOF)
    {
        celluleComposant *cell;
        cell = CreerCelluleComposant();
        compo = initialiseComposant(nom, valeur, type);
        compo.impedance = impedance;
        updateCelluleComposant(compo,cell);
        ajouterEnfinComposant(listeCompo, cell);
    }

    fclose(fichier);
}


void chargerSourceParallele(celluleSource **liste, const char *fileSource){
    FILE *fichier = fopen(fileSource, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", fileSource);
        return;
    }

    SourceTension source;
    char nom[50];
    float amplitude;
    float frequence;
    char sens[50];
    char type[50];
    while (fscanf(fichier, "%s  %f  %f  %s  %s", nom, &amplitude, &frequence, sens, type) != EOF)
    {
        celluleSource *cell;
        cell = CreerCelluleSource();
        source = initialiseSource(nom, type, amplitude, frequence, sens);
        updateCelluleSource(source,cell);
        ajouterEnfinSource(liste, cell);
        printf("fini\n");
    }

    fclose(fichier);
}


float ImpedanceequivalenteParallele(celluleComposant *liste){
    celluleComposant * p = liste;
    Voltmetre Voltmetre;
    
    if(liste == NULL){
        printf("Aucun composant n'a été entrée, Veillez entrer au moins un composant.\n");
        return 0;
    }

    float Impedance;
    float ImpedanceEquivalent = 0;
    float somme = 0;

    while(p != NULL){

       somme = (1/p->composants.impedance) +somme;
       p = p->suivant;
    }
    ImpedanceEquivalent = 1/somme;
    Voltmetre.impedanceEquivalente = ImpedanceEquivalent;
    return Voltmetre.impedanceEquivalente;

}

float trouverTensionMaximum(celluleSource *liste) {
    if (liste == NULL) {
        printf("La liste est vide.\n");
        return 0.0;
    }

    float maximumTension = liste->source.Amplitude;
    celluleSource *actuel = liste->suivant;

    while (actuel != NULL) {
        if (actuel->source.Amplitude > maximumTension) {
            maximumTension = actuel->source.Amplitude;
        }
        actuel = actuel->suivant;
    }

    return maximumTension;
}



float TensionParallele(celluleSource *liste){
    if(liste == NULL){
        printf("Vous n'avez entré aucune source de tension. Veillez en entrer au moins une pour continuer.\n");
        printf("\n");
        return 0;
    }

    celluleSource * p = liste;
    Voltmetre Voltmetre;

    
    float tension =trouverTensionMaximum(p);
    Voltmetre.TensionTotale = tension;
    printf("La tension totale du circuit est: %f \n", tension);

    return Voltmetre.TensionTotale;
}

void CalculCourant(celluleComposant **listeComposant, Voltmetre multimetre){
    celluleComposant *p = *listeComposant;
    int i=1;

    while(p != NULL){
        float Courant;  
        Courant = multimetre.TensionTotale / p->composants.impedance;
        printf("Le courant entrant dans le composant %d est de  %f \n", i, Courant);
        i = i+1;
        p= p->suivant;
    }
}

