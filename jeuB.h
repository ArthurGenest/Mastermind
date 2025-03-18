#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Declaration fonctions et variables pour le joueur B :
// Pour les couleurs on choisi :
// 0 = R, 1 = B, 2 = V, 3 = J, 4 = P, 5 = W

struct element
{
    int color_1;
    int color_2;
    int color_3;
    int color_4;
    struct element * suivant;
};
typedef struct element Element;

struct file
{
    Element * tete;
    Element * queue;
};
typedef struct file File;

File * creerFile();
File * enfiler(File * f, int w,int x,int y,int z);
File * defiler(File * f, int * coul1,int * coul2,int * coul3, int * coul4);
void afficherFile(File * f);
File * generer_file_combinaisons();
File * proposer_combinaison(File * f,char combi[]);
File * eliminer_comb(File * f,char combi_depile[],int   bonne_place,int mauvaise_place);
void evaluer_proposition_joueurB(const char proposition[], const char comparaison[], int *bonne_place, int *mauvaise_place);
void jouerB();
int convert_char_int(char lettre);
int testchoix3(char ch,int compteur);
