#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Declaration : fonction d'affichage en couleur
#define RESET   "\033[0m"
#define R     "\033[31m"
#define B    "\033[34m"
#define V   "\033[32m"
#define J  "\033[33m"
#define P  "\033[38;5;213m"
#define W  "\033[37m"
void printf_rouge(char carac_couleur);
void printf_bleu(char carac_couleur);
void printf_vert(char carac_couleur);
void printf_jaune(char carac_couleur);
void printf_rose(char carac_couleur);
void printf_blanc(char carac_couleur);
void printf_couleur(char carac_couleur);
