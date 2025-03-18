#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Fonctions affichage du menu

void separateur();
void afficherregles();
void affichermenu();
int testchoix(char ch, int compteur);
char testchoix2(char ch,int compteur);
void test_nompartie(char * nom_partie);
