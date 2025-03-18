#include "header.h"
#include "affichagetxt.h"
#include "jeuA.h"
#include "jeuB.h"
#include "reprendre_partie.h"
#include "revisualiser_partie.h"
#include "sauvegarde.h"
#include "stat.h"

// Fonction principale permettant de revisualiser une partie donnée par son nom
void revisualiser_partie(char * nom_partie)
{
    // Création du nom de fichier avec l'extension ".txt"
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp, ".txt");

    // Ouverture du fichier de la partie
    FILE * fichier = fopen(nom_temp, "r");
    char joueur;
    float temp;
    int essais, victoire;

    // Vérification que le fichier a été lu correctement (5 valeurs attendues)
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        fclose(fichier);    // Fermeture du fichier en cas d'erreur
        exit(-1);           // Arrêt du programme en cas d'erreur
    }
    // Si le joueur est 'A', on appelle la fonction appropriée pour visualiser sa partie
    if (joueur == 'A')
    {
        revisualiser_partieA(nom_partie);
    }
    // Si le joueur est 'B', on appelle la fonction appropriée pour visualiser sa partie
    else if (joueur == 'B')
    {
        revisualiser_partieB(nom_partie);
    }

}

// Fonction pour visualiser la partie du joueur B
void revisualiser_partieB(char * nom_partie)
{
    // Création du nom de fichier avec l'extension ".txt"
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp, ".txt");

    // Affichage du nom de la partie et d'une ligne de séparation
    separateur();
    printf("Nom de la partie : %s\n", nom_temp);

    // Ouverture du fichier de la partie
    FILE * fichier = fopen(nom_temp, "r");
    char joueur;
    float temp;
    int essais, victoire;

    // Vérification que le fichier a été lu correctement (5 valeurs attendues)
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        printf("Erreur de lecture dans le fichier1 %s\n", nom_partie);
        exit(-1);
    }

    // Affichage des informations du joueur B
    printf("Role du joueur : Joueur %c\n", joueur);
    printf("Nombres d'essais : %d essais\n",essais);
    printf("Victoire : %d\n",victoire);

    // Lecture de la combinaison secrète que le joueur voulait faire deviner
    char combinaison[4];
    if (fscanf(fichier, "%c %c %c %c\n",&combinaison[0],&combinaison[1],&combinaison[2],&combinaison[3]) != 4){
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        fclose(fichier);    // Fermeture du fichier en cas d'erreur
        exit(-1);
    }

    printf("\nLa combinaison secrete que le joueur voulait faire deviner etait : %c%c%c%c\n\n",combinaison[0], combinaison[1], combinaison[2], combinaison[3]);

    char proposition[5];
    int bonne_place, mauvaise_place;
    // Lecture des essais précédents (propositions et résultats) et affichage
    while(fscanf(fichier, "%d %c%c%c%c %d %d\n",&essais,&proposition[0],&proposition[1],
                  &proposition[2],&proposition[3],&bonne_place,&mauvaise_place)!=EOF)
    {
        // Affichage de l'essai actuel avec la proposition et les résultats
        printf("\nEssai numero : %d\n",essais);
        printf("Proposition de combinaison de l'ordinateur : %c%c%c%c\n",proposition[0],
               proposition[1], proposition[2], proposition[3]);
        printf("\nCombien de couleurs sont a la bonne place ?\nVotre reponse (-1 pour quitter) : "
               R "%d bonne place" RESET, bonne_place);
        printf("\nCombien de couleurs sont a la mauvaise place ?\nVotre reponse (-1 pour quitter) : "
               "%d mauvaise place \n", mauvaise_place);
    }
    // Affichage d'une ligne de séparation et du menu après avoir affiché tous les essais
    separateur();
    affichermenu();
}

// Fonction pour visualiser la partie du joueur A
void revisualiser_partieA(char * nom_partie)
{
    // Création du nom de fichier avec l'extension ".txt"
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp, ".txt");

    // Affichage du nom de la partie et d'une ligne de séparation
    separateur();
    printf("Nom de la partie : %s\n", nom_temp);

    // Ouverture du fichier de la partie
    FILE * fichier = fopen(nom_temp, "r");
    char joueur;
    float temp;
    int essais, victoire;

    // Vérification que le fichier a été lu correctement (5 valeurs attendues)
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        printf("Erreur de lecture dans le fichier1 %s\n", nom_partie);
        exit(-1);
    }

    // Affichage des informations du joueur A
    printf("Role du joueur : Joueur %c\n", joueur);
    printf("Nombres d'essais : %d essais\n",essais);
    printf("Nombres d'essais max : %d essais\n",essais_max);
    printf("Victoire : %d\n",victoire);

    // Lecture de la combinaison secrète à deviner par le joueur A
    char combinaison[4];
    if (fscanf(fichier, "%c %c %c %c\n",&combinaison[0],&combinaison[1],&combinaison[2],&combinaison[3]) != 4){
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        fclose(fichier);    // Fermeture du fichier en cas d'erreur
        exit(-1);
    }

    // Affichage de la combinaison secrète à deviner par le joueur A
    printf("\nLa combinaison secrete qu'il fallait deviner etait : %c%c%c%c\n\n",combinaison[0], combinaison[1], combinaison[2], combinaison[3]);

    char proposition[5];
    int bonne_place, mauvaise_place;
    // Lecture des essais précédents (propositions et résultats) et affichage
    while(fscanf(fichier, "%d %c%c%c%c %d %d\n",&essais,&proposition[0],&proposition[1],
                  &proposition[2],&proposition[3],&bonne_place,&mauvaise_place)!=EOF)
    {
        // Affichage de l'essai actuel avec la proposition et les résultats
        printf("\nEssai numero : %d\n",essais);
        printf("Entrez votre proposition, il s'agira d'une suite de 4 couleurs (" R "R" RESET ","B "B" RESET ","
           V "V" RESET "," J "J" RESET "," P "P" RESET "," W "W" RESET ") (Q pour quitter) : ");
        printf("%c%c%c%c",proposition[0], proposition[1],proposition[2], proposition[3]);
        printf("\nResultat : " R "%d bonne place" RESET ", %d mauvaise place\n", bonne_place, mauvaise_place);
    }
    // Affichage d'une ligne de séparation et du menu après avoir affiché tous les essais
    separateur();
    affichermenu();
}
