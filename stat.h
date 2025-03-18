#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Statistiques

#define MAX_PSEUDO 100
char pseudo[MAX_PSEUDO];

typedef struct {
    int partiesJouees;
    int victoires;
    int defaites;
    float pourcentage_Victoires;
    float pourcentage_Defaites;
    int temps_De_JeuTotal;
    int tentatives_Totales;
} Statistiques;

typedef struct {
    char role_joueur; // A ou B
    char nomPartie[100];  // Nom ou numéro de la partie
    float tempsMoyenReponse;         // Temps moyen de réponse (en secondes)
    int tentatives;                  // Nombre de tentatives
    int tentatives_max;
    int partieGagnee;                // 1 si gagnée, 0 si perdue
} ResultatPartie;

void demanderPseudo(char *pseudo);
int verifierFichier(char *pseudo);
void creerFichier(char *pseudo, Statistiques *stats);
void chargerFichier(char *pseudo, Statistiques *stats);
void creation_joueur();
void mettreAJourStatistiques(char *pseudo, int victoire);
void sauvegarderFichier(char *pseudo, Statistiques *stats);
void ajouterResultatPartie(char role,char *pseudo,char nompartie[],float tempsmoyen_reponse,int tentatives_partie, int partiegagne);
void lire_statistiques(char * nomFichier);
