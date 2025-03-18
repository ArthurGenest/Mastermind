#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Fonctions sauvegarde

void creer_ou_remplacer_fichier(char *nom_partie);
void ajouter_type_joueur(char *nom_fichier, char joueur);
void supprimer_fichier(char *nom_partie);
void demande_sauvegarde(char*nom_partie);
void ajouter_combi_secrete(char *nom_partie, char *combinaison);
void ajouter_essai(char *nom_partie, int essais, char* proposition, int bonne_place, int mauvaise_place);
void sauvegarderetat(char *nom_partie, char joueur, float temp, int essais, int essais_max, int victoire);

void sauvegarderFile(File *f, char *nom_partie);

void charger_reprendre_partie();
void afficher_partie_revisualiser();
void afficher_partie_recharger();
void verifier_existence_partie_revisualiser(char *nom_partie);
void verifier_existence_partie_recharger(char * nom_partie);
int testchoix5(char ch,int compteur);
int testchoix6(char ch,int compteur);
