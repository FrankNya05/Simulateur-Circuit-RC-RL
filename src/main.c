#include<stdio.h>
#include<stdlib.h>
#include "../src/tools.h"
#include <string.h>




#define CHECK_TEST 0
#define CHECK_TEST2 1
#define CHECK_TEST1 0




int main() {

    if(CHECK_TEST){
    // CONFIGURATION SERIE

    SourceTension source1;
    celluleSource *listeSource1 = NULL;
    Composants composants1;
    celluleComposant *listecomposant1 = NULL;
    char fileCompo[50] = "fileCompoSerie";
    char fileSource[50] = "fileSourceSerie";

    // INITIALISATION ET ENREGISTREMENT DE LA LISTE DES SOURCES
    chargerSourceSerie(&listeSource1, fileSource);
    printf("2\n");
    afficherListeSource(listeSource1);
    source1 = initialiseSource("Source1", "AC", 10, 60, "positif");
    celluleSource *cellSource = CreerCelluleSource();
    updateCelluleSource(source1,cellSource);
    ajouterEnfinSource(&listeSource1, cellSource);
    sauvegarderSourceSerie(listeSource1,fileSource);
    afficherListeSource(listeSource1);
    printf("1\n");

    SourceTension source2;
    source2 = initialiseSource("Source2", "AC", 15, 30, "positif");
    celluleSource *cellSource1 = CreerCelluleSource();
    updateCelluleSource(source2,cellSource1);
    ajouterEnfinSource(&listeSource1, cellSource1);
    sauvegarderSourceSerie(listeSource1,fileSource);
    afficherListeSource(listeSource1);

    // INITIALISATION ET ENREGISTREMENT DE LA LISTE DES COMPOSANTS
    chargerCompoSerie(&listecomposant1, fileCompo);
    afficherListeComposant(listecomposant1);
    composants1 = initialiseComposant("resistance1", 1200, "resistance");
    composants1.impedance = calculImpedance(composants1, "AC", listeSource1);
    celluleComposant *cellCompo1 = CreerCelluleComposant();
    updateCelluleComposant(composants1, cellCompo1);
    ajouterEnfinComposant(&listecomposant1, cellCompo1);
    sauvegarderComposantSerie(listecomposant1, fileCompo);
    afficherListeComposant(listecomposant1);

    Composants composants2 = initialiseComposant("Imductance", 1.5, "inductance");
    composants2.impedance = calculImpedance(composants2, "AC", listeSource1);
    celluleComposant *cellCompo2 = CreerCelluleComposant();
    updateCelluleComposant(composants2, cellCompo2);
    ajouterEnfinComposant(&listecomposant1, cellCompo2);
    sauvegarderComposantSerie(listecomposant1, fileCompo);
    afficherListeComposant(listecomposant1);

    //CALCUL DE LA TENSION AUX BORNES DE CHAQUE COMPOSANT ET DU COURANT CIRCULANT DANS LE CIRCUIT ET DE L'IMPEDANCE TOTALE DU CIRCUIT

    Voltmetre voltmetre;
    voltmetre.impedanceEquivalente = ImpedanceequivalenteSerie(listecomposant1);
    voltmetre.TensionTotale = TensionSeries(listeSource1);
    voltmetre.intensite = CourantSerie(voltmetre);
    CalculTension(&listecomposant1, voltmetre);

    printf("Impedance equivalente: %f ||| Tension totale: %f ||| Courant: %f |||\n", voltmetre.impedanceEquivalente, voltmetre.TensionTotale, voltmetre.intensite); 

    supprimerfichier(fileCompo);
    supprimerfichier(fileSource);
    }

    if(CHECK_TEST2){
    // CONFIGURATION PARALLELE

    SourceTension source1;
    celluleSource *listeSource1 = NULL;
    Composants composants1;
    celluleComposant *listecomposant1 = NULL;
    char fileCompo1[50] = "fileCompoParallele";
    char fileSource1[50] = "fileSourceParallele";

    // INITIALISATION ET ENREGISTREMENT DE LA LISTE DES SOURCES
    chargerSourceParallele(&listeSource1, fileSource1);
    afficherListeSource(listeSource1);
    source1 = initialiseSource("Source1", "AC", 10, 60, "positif");
    celluleSource *cellSource = CreerCelluleSource();
    updateCelluleSource(source1,cellSource);
    ajouterEnfinSource(&listeSource1, cellSource);
    sauvegarderSourceParallele(listeSource1,fileSource1);
    afficherListeSource(listeSource1);
    printf("---------------------------------------------------------------------\n");

    SourceTension source2;
    source2 = initialiseSource("Source2", "AC", 15, 30, "positif");
    celluleSource *cellSource1 = CreerCelluleSource();
    updateCelluleSource(source2,cellSource1);
    ajouterEnfinSource(&listeSource1, cellSource1);
    sauvegarderSourceParallele(listeSource1,fileSource1);
    afficherListeSource(listeSource1);
    printf("---------------------------------------------------------------------\n");
    printf("\n");

    // INITIALISATION ET ENREGISTREMENT DE LA LISTE DES COMPOSANTS
    chargerCompoParallele(&listecomposant1, fileCompo1);
    afficherListeComposant(listecomposant1);
    composants1 = initialiseComposant("resistance1", 1200, "resistance");
    composants1.impedance = calculImpedance(composants1, "AC", listeSource1);
    celluleComposant *cellCompo1 = CreerCelluleComposant();
    updateCelluleComposant(composants1, cellCompo1);
    ajouterEnfinComposant(&listecomposant1, cellCompo1);
    sauvegarderComposantParallele(listecomposant1, fileCompo1);
    afficherListeComposant(listecomposant1);
    printf("-------------------------------------------------------------------------------------\n");
    printf("\n");

    Composants composants2 = initialiseComposant("Imductance", 1.5, "inductance");
    composants2.impedance = calculImpedance(composants2, "AC", listeSource1);
    celluleComposant *cellCompo2 = CreerCelluleComposant();
    updateCelluleComposant(composants2, cellCompo2);
    ajouterEnfinComposant(&listecomposant1, cellCompo2);
    sauvegarderComposantParallele(listecomposant1, fileCompo1);
    afficherListeComposant(listecomposant1);


    printf("--------------------------------------------------------------------------------------\n");
    printf("\n");

    //CALCUL DE LA TENSION AUX BORNES DE CHAQUE COMPOSANT ET DU COURANT CIRCULANT DANS LE CIRCUIT ET DE L'IMPEDANCE TOTALE DU CIRCUIT

    Voltmetre voltmetre;
    voltmetre.impedanceEquivalente = ImpedanceequivalenteParallele(listecomposant1);
    voltmetre.TensionTotale = TensionParallele(listeSource1);
    CalculCourant(&listecomposant1, voltmetre);
    printf("Impedance equivalente: %f ||| Tension totale: %f  |||\n", voltmetre.impedanceEquivalente, voltmetre.TensionTotale); 

    
    supprimerfichier(fileSource1);
    supprimerfichier(fileCompo1);

    }

    if(CHECK_TEST1){
    char choix;
    char choix2;
    char choix3;
    
    celluleComposant* listeComposant = NULL;
    celluleComposant* cellComposant ;
    celluleSource* cellSource;
    celluleSource* listeSource = NULL;

    celluleComposant* listeComposantParallele = NULL;
    celluleSource* listeSourceParallele = NULL;
    char fileCompo[50] = "fileCompoSerie";
    char fileSource[50] = "fileSourceSerie";
    char fileCompoParallele[50] = "fileCompoParallele";
    char fileSourceParallele[50] = "fileSourceParallele";

   chargerCompoSerie(&listeComposant, fileCompo);
   chargerSourceSerie(&listeSource, fileSource);

   chargerCompoParallele(&listeComposantParallele,fileCompoParallele);
   chargerSourceParallele(&listeSourceParallele, fileSourceParallele);

 

    do{
        system("clear");
        system("clear");

        printf("********************************************************\n");
        printf("** BIENVENUE DANS NOTRE SIMULATEUR DE CIRCUIT RC OU RL**\n");
        printf("********************************************************\n");
        printf("\n");

        printf("*****************************************************************************\n");
        printf("** Q : Quitter | S : Cconfiguration série | P : Configuration parallèle :) **\n");
        printf("******************************************************************************\n");

        printf("**************************---Choisissez une option:---*******************************\n");
        choix= getchar();
         
        switch (choix)
        {
        case 'S':
            system("clear");
            printf("*****Vous avez choisi la configuration Série*****\n");
          do{

            system ("clear");
            system("clear");

            printf("**************************************************************************************************************************************\n");
            printf("**                                               MENU SECONDAIRE                                                                    **\n");
            printf("**************************************************************************************************************************************\n");
            printf("** K : Quitter                                                     |  S : Calculer la tension, le courant et l'impedance du circuit **\n");
            printf("** A : Ajouter un composant                                        |                                                                 **\n");
            printf("** P : Afficher la liste des composants                            |                                                                **\n");
            printf("** B : Ajouter une source de tension                               |                                                                **\n");
            printf("** C : Afficher la liste des sources de Tensions                   |                                                                **\n");
            printf("** E : Supprimer un fichier                                        |                                                                **\n");
            printf("**************************************************************************************************************************************\n");

            choix2 = getchar();
           
            switch(choix2)
            {
                case 'A':
                system("clear");
                //Ajout d'un composant dans le circuit
                Composants composant;
                printf("*******************************************************************************************\n");
                printf("** COMME COMPOSANT DISPONILES VOUS AVEZ DES RESISTANCES DES CAPACITÉS ET DES INDUCTANCES **\n");
                printf("*******************************************************************************************\n");
                printf("\n");

                printf("Entrez le nom du composant de: ");
                scanf("%s", composant.composant_01);
                printf("Entrez sa valeur : ");
                scanf("%f", &(composant.Valeur_01));
                printf("Les types de composants ou d'impedances disponibles sont:** resistance , capacite , inductance **  TOUTE AUTRE ENTREE ENTRAINERA UNE ERREUR\n");
                printf("Donnez le type du composant: ");
                scanf("%s", composant.type);
                
                printf("\n");

                char type1[50];
                   
                composant = initialiseComposant(composant.composant_01, composant.Valeur_01, composant.type);
                printf("Donner le type de source de tension que vous comptez utiliser. Vous ne pouvez utiliser q'un seul type de source de tension à la fois !!!\n");
                scanf("%s", type1);
                composant.impedance = calculImpedance(composant, &type1, listeSource);
                cellComposant= CreerCelluleComposant();
                updateCelluleComposant(composant, cellComposant);
                ajouterEnfinComposant(&listeComposant, cellComposant);

                //Sauvegarder le composant ajouté dans le fichier

                printf("Entrer le nom du fichier: ");
                char nomfichier3[50] = "fileCompoSerie";
                sauvegarderComposantSerie(listeComposant,nomfichier3);
                
                printf("Appuyez sur Entrée pour revenir au menu...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur
                break; 

                // Affichage de la liste des composants

                case 'P':
                system("clear");
                afficherListeComposant(listeComposant);

                printf("Appuyez sur Entrée pour revenir au menu...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur
                break;

                case 'B':

               //Ajout d'une source de tension dans le circuit
               system("clear");
                SourceTension source;
                char type[5];
                char sens[12];
                printf("********************************************************\n");
                printf("** LES DIFFERENTS TYPES DE CIRCUIT SONT 'AC' ET  'DC' **\n");
                printf("********************************************************\n");
                printf("\n");

                printf("Entrez le nom de la source: ");
                scanf("%s", source.Nom);
                printf("Entrez sa valeur : ");
                scanf("%f", &(source.Amplitude));
                printf("Vous avez des sources à courant alternatif ou continue choisissez en une\n");
                printf("Entrer le type de source: ");
                scanf("%s", source.TypeSource);
                printf("Entrer la fréquence de la source: ");
                scanf("%f", &(source.frequence));
                printf("Donnez le sens de branchement de votre source de tension: ");
                scanf("%s", source.sens);
                strcpy(type,source.TypeSource);
                strcpy(sens,source.sens);
                printf("\n");
                   
                source = initialiseSource(source.Nom, type, source.Amplitude, source.frequence, sens);
                cellSource = CreerCelluleSource();
                updateCelluleSource(source, cellSource);
                ajouterEnfinSource(&listeSource, cellSource);

                //Sauvegarder les informations dans un fichier

                char nomfichier[20]= "fileSourceSerie";
                sauvegarderSourceSerie(listeSource,nomfichier);

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;

                case 'C':
                system("clear");
                afficherListeSource(listeSource);
                printf("-----------------------------------------------------\n");

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;


                case 'E':
                system("clear");
                printf("Entrer le nom du fichier à supprimer: ");
                char nomfichier2[50];
                scanf("%s",nomfichier2);
                supprimerfichier(nomfichier2);

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;

                case 'S':
                system("clear");

                printf("Nous allons proceder au calcul des caracteristiques du circuit.\n");
                Voltmetre multimetre;
                multimetre.impedanceEquivalente = ImpedanceequivalenteSerie(listeComposant);
                multimetre.TensionTotale = TensionSeries(listeSource);
                multimetre.intensite = CourantSerie(multimetre);         

                CalculTension(&listeComposant, multimetre);

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;
                
                default:
                break;
            }
          }while(choix2 != 'k' && choix2 != 'K');
                   
           printf("Appuyez sur Entrée pour continuer...");
           getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
           getchar(); // Attendez l'entrée de l'utilisateur
            break;



            /*****Configuration parallele******/  
        case 'P':

            system("clear");
            printf("*****Vous avez choisi la configuration parrallèle*****\n");

          do{

            system ("clear");
            system("clear");

            printf("**************************************************************************************************************************************\n");
            printf("**                                               MENU SECONDAIRE                                                                    **\n");
            printf("**************************************************************************************************************************************\n");
            printf("** K : Quitter                                                     |  S : Calculer la tension, le courant et l'impedance du circuit **\n");
            printf("** A : Ajouter un composant                                        |                                                                **\n");
            printf("** P : Afficher la liste des composants                            |                                                                **\n");
            printf("** B : Ajouter une source de tension                               |                                                                **\n");
            printf("** C : Afficher la liste des sources de Tensions                   |                                                                **\n");
            printf("** E : Supprimer un fichier                                        |                                                                **\n");
            printf("**************************************************************************************************************************************\n");

            choix2 = getchar();
           
            switch(choix2)
            {
                case 'A':
                system("clear");
                //Ajout d'un composant dans le circuit
                Composants composant;
                printf("*******************************************************************************************\n");
                printf("** COMME COMPOSANT DISPONILES VOUS AVEZ DES RESISTANCES DES CAPACITÉS ET DES INDUCTANCES **\n");
                printf("*******************************************************************************************\n");
                printf("\n");

                printf("Entrez le nom du composant de: ");
                scanf("%s", composant.composant_01);
                printf("Entrez sa valeur : ");
                scanf("%f", &(composant.Valeur_01));
                printf("Les types de composants ou d'impedances disponibles sont:** resistance , capacite , inductance **  TOUTE AUTRE ENTREE ENTRAINERA UNE ERREUR\n");
                printf("Donnez le type du composant: ");
                scanf("%s", composant.type);
                
                printf("\n");

                char type1[50];
                   
                composant = initialiseComposant(composant.composant_01, composant.Valeur_01, composant.type);
                printf("Donner le type de source de tension que vous comptez utiliser. Vous ne pouvez utiliser q'un seul type de source de tension à la fois !!!\n");
                scanf("%s", type1);
                composant.impedance = calculImpedance(composant, &type1, listeSource);
                cellComposant= CreerCelluleComposant();
                updateCelluleComposant(composant, cellComposant);
                ajouterEnfinComposant(&listeComposantParallele, cellComposant);

                //Sauvegarder le composant ajouté dans le fichier

                printf("Entrer le nom du fichier: ");
                char nomfichier3[50] = "fileCompoParallele";
                sauvegarderComposantParallele(listeComposantParallele,nomfichier3);
                
                printf("Appuyez sur Entrée pour revenir au menu...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur
                break; 

                // Affichage de la liste des composants

                case 'P':
                system("clear");
                afficherListeComposant(listeComposantParallele);

                printf("Appuyez sur Entrée pour revenir au menu...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur
                break;

                case 'B':

               //Ajout d'une source de tension dans le circuit
               system("clear");
                SourceTension source;
                char type[5];
                char sens[12];
                printf("********************************************************\n");
                printf("** LES DIFFERENTS TYPES DE CIRCUIT SONT 'AC' ET  'DC' **\n");
                printf("********************************************************\n");
                printf("\n");

                printf("Entrez le nom de la source: ");
                scanf("%s", source.Nom);
                printf("Entrez sa valeur : ");
                scanf("%f", &(source.Amplitude));
                printf("Vous avez des sources à courant alternatif ou continue choisissez en une\n");
                printf("Entrer le type de source: ");
                scanf("%s", source.TypeSource);
                printf("Entrer la fréquence de la source: ");
                scanf("%f", &(source.frequence));
                printf("Donnez le sens de branchement de votre source de tension: ");
                scanf("%s", source.sens);
                strcpy(type,source.TypeSource);
                strcpy(sens,source.sens);
                printf("\n");
                   
                source = initialiseSource(source.Nom, type, source.Amplitude, source.frequence, sens);
                cellSource = CreerCelluleSource();
                updateCelluleSource(source, cellSource);
                ajouterEnfinSource(&listeSourceParallele, cellSource);

                //Sauvegarder les informations dans un fichier

                char nomfichier[20]= "fileSourceParallele";
                sauvegarderSourceParallele(listeSourceParallele,nomfichier);

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;

                case 'C':
                system("clear");
                afficherListeSource(listeSourceParallele);
                printf("-----------------------------------------------------\n");

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;


                case 'E':
                system("clear");
                printf("Entrer le nom du fichier à supprimer: ");
                char nomfichier2[50];
                scanf("%s",nomfichier2);
                supprimerfichier(nomfichier2);

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;

                case 'S':
                system("clear");

                printf("Nous allons proceder au calcul des caracteristiques du circuit.\n");
                Voltmetre multimetre;
                multimetre.impedanceEquivalente = ImpedanceequivalenteParallele(listeComposantParallele);
                multimetre.TensionTotale = TensionParallele(listeSourceParallele);
                CalculCourant(&listeComposantParallele, multimetre);         

                printf("Appuyez sur Entrée pour revenir au menu précedent...");
                getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
                getchar(); // Attendez l'entrée de l'utilisateur

                break;
                
                default:
                break;
            }
          }while(choix2 != 'k' && choix2 != 'K');
                   
           printf("Appuyez sur Entrée pour continuer...");
           getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
           getchar(); // Attendez l'entrée de l'utilisateur
            break;
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        
        default:
            break;
        }
        
    }while(choix!= 'Q' && choix!= 'q');


}

    return 0;
}

