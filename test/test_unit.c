#include "../lib/acutest.h"
#include <stdio.h>
#include <string.h>
#include "../src/tools.h"


void test_initialiseComposant(void){
    Composants c = initialiseComposant("R1", 1000, "resistance");
    TEST_CHECK_(c.Valeur_01 == 1000, "Valeur correcte");
    TEST_CHECK_(strcmp(c.type, "resistance") == 0, "Type correct");
    TEST_CHECK_(strcmp(c.composant_01, "R1") == 0, "Nom correct");
}

void test_initialiseComposant_type_invalide(void){
    Composants c = initialiseComposant("X1", 500, "inconnu");
    TEST_CHECK_(strcmp(c.type, "inconnu") != 0, "Type invalide rejete");
}

void test_NombreDecomposant(void){
    celluleComposant *liste = NULL;
    TEST_CHECK_(NombreDecomposant(liste) == 0, "Liste vide = 0 composant");

    Composants c1 = initialiseComposant("R1", 100, "resistance");
    celluleComposant *cell1 = CreerCelluleComposant();
    updateCelluleComposant(c1, cell1);
    ajouterEnfinComposant(&liste, cell1);
    TEST_CHECK_(NombreDecomposant(liste) == 1, "1 composant ajoute");

    Composants c2 = initialiseComposant("R2", 200, "resistance");
    celluleComposant *cell2 = CreerCelluleComposant();
    updateCelluleComposant(c2, cell2);
    ajouterEnfinComposant(&liste, cell2);
    TEST_CHECK_(NombreDecomposant(liste) == 2, "2 composants ajoutes");
}

void test_NombreDesource(void){
    celluleSource *liste = NULL;
    TEST_CHECK_(NombreDesource(liste) == 0, "Liste vide = 0 source");

    celluleSource *cell1 = CreerCelluleSource();
    strcpy(cell1->source.Nom, "S1");
    cell1->source.Amplitude = 10;
    ajouterEnfinSource(&liste, cell1);
    TEST_CHECK_(NombreDesource(liste) == 1, "1 source ajoutee");

    celluleSource *cell2 = CreerCelluleSource();
    strcpy(cell2->source.Nom, "S2");
    cell2->source.Amplitude = 15;
    ajouterEnfinSource(&liste, cell2);
    TEST_CHECK_(NombreDesource(liste) == 2, "2 sources ajoutees");
}

void test_ImpedanceequivalenteSerie(void){
    celluleComposant *liste = NULL;

    Composants c1 = initialiseComposant("R1", 100, "resistance");
    c1.impedance = 100;
    celluleComposant *cell1 = CreerCelluleComposant();
    updateCelluleComposant(c1, cell1);
    ajouterEnfinComposant(&liste, cell1);

    Composants c2 = initialiseComposant("R2", 200, "resistance");
    c2.impedance = 200;
    celluleComposant *cell2 = CreerCelluleComposant();
    updateCelluleComposant(c2, cell2);
    ajouterEnfinComposant(&liste, cell2);

    float zeq = ImpedanceequivalenteSerie(liste);
    TEST_CHECK_(zeq == 300, "Impedance serie = 100 + 200 = 300");
}

void test_ImpedanceequivalenteParallele(void){
    celluleComposant *liste = NULL;

    Composants c1 = initialiseComposant("R1", 100, "resistance");
    c1.impedance = 100;
    celluleComposant *cell1 = CreerCelluleComposant();
    updateCelluleComposant(c1, cell1);
    ajouterEnfinComposant(&liste, cell1);

    Composants c2 = initialiseComposant("R2", 100, "resistance");
    c2.impedance = 100;
    celluleComposant *cell2 = CreerCelluleComposant();
    updateCelluleComposant(c2, cell2);
    ajouterEnfinComposant(&liste, cell2);

    float zeq = ImpedanceequivalenteParallele(liste);
    TEST_CHECK_(zeq == 50, "Impedance parallele = 1/(1/100 + 1/100) = 50");
}

void test_CourantSerie(void){
    Voltmetre v;
    v.TensionTotale = 10;
    v.impedanceEquivalente = 100;
    float i = CourantSerie(v);
    TEST_CHECK_(i == 0.1f, "Courant = 10 / 100 = 0.1");
}

void test_TensionSeries(void){
    celluleSource *liste = NULL;

    celluleSource *cell1 = CreerCelluleSource();
    strcpy(cell1->source.TypeSource, "AC");
    cell1->source.Amplitude = 10;
    strcpy(cell1->source.sens, "positif");
    ajouterEnfinSource(&liste, cell1);

    celluleSource *cell2 = CreerCelluleSource();
    strcpy(cell2->source.TypeSource, "AC");
    cell2->source.Amplitude = 15;
    strcpy(cell2->source.sens, "positif");
    ajouterEnfinSource(&liste, cell2);

    float tension = TensionSeries(liste);
    TEST_CHECK_(tension == 25, "TensionSeries = 10 + 15 = 25");
}

void test_TensionParallele(void){
    celluleSource *liste = NULL;

    celluleSource *cell1 = CreerCelluleSource();
    cell1->source.Amplitude = 10;
    ajouterEnfinSource(&liste, cell1);

    celluleSource *cell2 = CreerCelluleSource();
    cell2->source.Amplitude = 15;
    ajouterEnfinSource(&liste, cell2);

    float tension = TensionParallele(liste);
    TEST_CHECK_(tension == 15, "TensionParallele = max(10, 15) = 15");
}


TEST_LIST = {
    {"initialiseComposant",               test_initialiseComposant},
    {"initialiseComposant type invalide",  test_initialiseComposant_type_invalide},
    {"NombreDecomposant",                  test_NombreDecomposant},
    {"NombreDesource",                     test_NombreDesource},
    {"ImpedanceequivalenteSerie",          test_ImpedanceequivalenteSerie},
    {"ImpedanceequivalenteParallele",      test_ImpedanceequivalenteParallele},
    {"CourantSerie",                       test_CourantSerie},
    {"TensionSeries",                      test_TensionSeries},
    {"TensionParallele",                   test_TensionParallele},
    {0}
};
