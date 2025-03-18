#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Declaration fonctions et variables pour le joueur A :
// Taille du code secret
#define taille_code 4

// Definition de la variable du nombre d'essais max
int essais_max;

// Génère le code aléatoirement
void generer_code(char code[]);

// Demande la proposition du joueur
void obtenir_proposition_du_joueur(char proposition[],float * tmps);

// Évalue la proposition du joueur
void evaluer_proposition(const char code[],const char proposition[],int *bonne_place,int *mauvaise_place);

// Permettre au joueur de quitter à tout moment
void testchar(char proposition[],float * tmps);

void jouer_A();
void choix_niveau_joueurA();
float moyenne_temps(float temps_jA, int nbessais, float moyenne_temps);
int testchoix4(char ch,int compteur);
