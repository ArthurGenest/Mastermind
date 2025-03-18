#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Reprendre une partie

void reprendre_partie(char * nom_partie);
void reprendre_partieB(char * nom_partie);
void reprendre_partieA(char * nom_partie);
void revisualiser_essai_precedentA(char * nom_partie);
void revisualiser_essai_precedentB(char * nom_partie);
File * regenererFile(File * toutes_les_combi,char *nom_partie);
