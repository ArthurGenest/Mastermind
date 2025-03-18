#include "header.h"
#include "affichagetxt.h"
#include "jeuA.h"
#include "jeuB.h"
#include "reprendre_partie.h"
#include "revisualiser_partie.h"
#include "sauvegarde.h"
#include "stat.h"

// Creation des fichiers de sauvegardes, tout joueur confondu

void creer_ou_remplacer_fichier(char *nom_partie) {
    FILE *fichier;
    int reponse; int compteur = 0; char reponse_prov;

    char nom_temp[100];
    strcpy(nom_temp,nom_partie);    // Copie du nom de la partie dans une variable temporaire
    strcat(nom_temp, ".txt");       // Ajout de l'extension '.txt'

    fichier = fopen(nom_temp, "r");
    if (fichier != NULL) {
        printf("Le fichier '%s' existe deja. Voulez-vous le remplacer ? \n1: Oui\n2: Non\n3: Quitter\n4: Retour au menu principal\nVotre choix : ", nom_temp);
        scanf("%c",&reponse_prov); while (getchar() != '\n'){compteur++;};
        reponse = testchoix5(reponse_prov,compteur);    // vérifier le choix à l'utilisateur

        if(reponse == 3){return exit(-1);}      // Quitte si l'utilisateur choisit de quitter
        else if(reponse == 4){affichermenu();}  // Retour au menu principal si l'utilisateur choisit "Retour"
        else if (reponse == 1) {
            fclose(fichier);
            fichier = fopen(nom_temp, "w");
            if (fichier == NULL) {
                printf("Erreur : impossible d'ouvrir le fichier pour ecriture.\n");
                return;
            }
            printf("Fichier '%s' remplace avec succes.\n", nom_temp);
        } else {    // Si l'utilisateur choisit "Non"
            printf("Le fichier '%s' n'a pas ete remplace.\n", nom_temp);
            fclose(fichier);
            affichermenu();
            return;
        }
    } else {    // Si le fichier n'existe pas
        fichier = fopen(nom_temp, "w"); // Crée un nouveau fichier
        if (fichier == NULL) {
            printf("Erreur : impossible de creer le fichier '%s'.\n", nom_temp);
            return;
        }
        printf("Fichier '%s' cree avec succes.\n", nom_temp);
    }
    fclose(fichier);
}

// Fonction qui ajoute un joueur et ses informations (temps, essais, etc.) dans le fichier de la partie.
void ajouter_type_joueur(char *nom_partie, char joueur) {

    char nom_temp[100];
    strcpy(nom_temp,nom_partie);    // Copie du nom de la partie
    strcat(nom_temp, ".txt");       // Ajout de l'extension '.txt'

    float temp = 0; int essais = 0 ; int victoire = -1; int essais_max = 0;
    FILE *fichier = fopen(nom_temp, "r+");  // Ouverture du fichier en mode lecture et écriture
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier '%s'.\n", nom_temp);
        return;
    }
    if (fichier) {
        fseek(fichier, 0, SEEK_SET);                                                    // Positionnement au début du fichier
        fprintf(fichier, "%c %f %d %d %d \n",joueur,temp,essais,essais_max,victoire);   // Écriture des données du joueur dans le fichier
        fclose(fichier);
    } else {
        printf("Erreur lors de l'enregistrement du fichier.\n");
    }
}

// Fonction qui supprime le fichier de la partie.
void supprimer_fichier(char *nom_partie) {

    char nom_temp[100];
    strcpy(nom_temp,nom_partie);    // Copie du nom de la partie
    strcat(nom_temp, ".txt");       // Ajout de l'extension '.txt'

    if (remove(nom_temp) == 0) {    // Suppression du fichier
        printf("La partie '%s' n'a pas ete enregistree.\n", nom_temp);
    } else {
        printf("Le fichier '%s' n'a pas pu etre supprime.\n", nom_temp);
    }
}


// Fonction qui demande à l'utilisateur s'il veut sauvegarder la partie en cours.
void demande_sauvegarde(char *nom_partie)
{
    int choix; char choix_prov; int compteur = 0;

    printf("\nVoulez-vous sauvegarder cette partie ? (pour pouvoir la reprendre, revisualiser)\n1: Oui\n2: Non\n\nVotre choix : ");
    scanf("%c",&choix_prov); while (getchar() != '\n'){compteur++;};
    choix = testchoix6(choix_prov,compteur);// Demande du choix à l'utilisateur
    if (choix == 1)
    {
        return; // Sauvegarde
    }
    else if (choix == 2)
    {
        supprimer_fichier(nom_partie);  // Supprime le fichier si l'utilisateur ne veut pas sauvegarder
        return;
    }
    else
    {
    printf("Choix incorrecte, recommencer !\n");
    demande_sauvegarde(nom_partie);     // Relance la demande si l'utilisateur fait un mauvais choix
    }
}

// Fonction qui ajoute la combinaison secrète dans le fichier de sauvegarde.
void ajouter_combi_secrete(char *nom_partie, char *combinaison)
{
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);            // Copie du nom de la partie
    strcat(nom_temp, ".txt");               // Ajout de l'extension '.txt'
    FILE *fichier = fopen(nom_temp, "a");   // Ouverture du fichier en mode ajout

    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier '%s' en mode ajout.\n", nom_temp);
        return;
    }
    if (fichier) {
        fprintf(fichier, "%c %c %c %c\n", combinaison[0],combinaison[1],combinaison[2],combinaison[3]); // Ajout de la combinaison dans le fichier
        fclose(fichier);
    } else {
        printf("Erreur lors de l'enregistrement du fichier.\n");
    }
}

// Fonction qui ajoute un essai de la partie dans le fichier.
void ajouter_essai(char *nom_partie, int essais, char* proposition, int bonne_place, int mauvaise_place)
{
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);            // Copie du nom de la partie
    strcat(nom_temp, ".txt");               // Ajout de l'extension '.txt'
    FILE *fichier = fopen(nom_temp, "a");   // Ouverture du fichier en mode ajout

    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier '%s' en mode ajout.\n", nom_temp);
        return;
    }
    if (fichier) {
        fprintf(fichier, "%d %c%c%c%c %d %d\n", essais, proposition[0],proposition[1],proposition[2],proposition[3],bonne_place,mauvaise_place);    // Ajout de l'essai dans le fichier
        fclose(fichier);
    } else {
        printf("Erreur lors de l'enregistrement du fichier.\n");
    }
}

// Fonction qui sauvegarde l'état actuel d'un joueur dans le fichier.
void sauvegarderetat(char *nom_partie, char joueur, float temp, int essais, int essais_max, int victoire) {
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);            // Copie du nom de la partie
    strcat(nom_temp, ".txt");               // Ajout de l'extension '.txt'
    FILE *fichier = fopen(nom_temp, "r+");  // Ouvrir en lecture et écriture
    if (fichier) {
        // Replacer uniquement les parties mises à jour dans le fichier
        fseek(fichier, 0, SEEK_SET);    // Positionnement au début du fichier
        fprintf(fichier, "%c %f %d %d %d ",joueur,temp,essais,essais_max,victoire); // Sauvegarde des données
        fclose(fichier);    // Fermeture du fichier après sauvegarde
    } else {
        printf("Erreur lors de l'enregistrement du fichier.\n");
    }
}


// Fonction pour sauvegarder le contenu de la liste dans un fichier
void sauvegarderFile(File *f, char *nom_partie) {
    // Créer le nom du fichier avec l'extension .txt
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp, ".txt");
    FILE *fichier = fopen(nom_temp, "a");  // Ouvrir en mode ajout
    if (fichier == NULL) {
        // Si le fichier ne peut pas être ouvert, afficher un message d'erreur
        printf("Erreur : impossible d'ouvrir le fichier '%s'.\n", nom_temp);
        return;
    }

    // Parcourir chaque élément de la liste et l'écrire dans le fichier
    Element *actuel = f->tete;
    while (actuel != NULL) {
        // Ecrire les données de chaque élément dans le fichier
        fprintf(fichier, "%d %d %d %d ->\n", actuel->color_1, actuel->color_2, actuel->color_3, actuel->color_4);
        actuel = actuel->suivant;   // Passer à l'élément suivant
    }

    // Fermer le fichier
    fclose(fichier);
}

// Reprendre / revisualiser une partie

// Fonction pour demander à l'utilisateur s'il veut recharger ou revisualiser une partie
void charger_reprendre_partie()
{
    char ch_prov; int ch;
    int compteur = 0;

    // Afficher les options à l'utilisateur
    printf("Voulez-vous recharger une partie pour la continuer? Ou bien revisualiser une partie deja jouee ?\n");
    printf("1: Recharger\n");
    printf("2: Revisualiser\n");
    printf("3: Quitter\n");
    printf("4: Retour au menu principal\n");
    separateur();
    printf("Choisir une action : \n");
    // Lire la saisie de l'utilisateur
    scanf("%c", &ch_prov); while (getchar() != '\n'){compteur=0;compteur++;};   // Nettoyer le buffer
    ch = testchoix5(ch_prov,compteur);  // Vérifier la validité du choix
    separateur();

    // Traitement en fonction du choix de l'utilisateur
    switch(ch){
    case 1 :
        afficher_partie_recharger();    // Afficher les parties à recharger
        char nom_partie1[100];          // Demander le nom de la partie à recharger
        printf("Ecrivez le nom de la partie que vous voulez recharger ?\n");
        fgets(nom_partie1,100,stdin);
        char* new_line1 = "\n";         // Supprimer le retour à la ligne dans le nom de la partie
        nom_partie1[strcspn(nom_partie1,new_line1)] = '\0';
        verifier_existence_partie_recharger(nom_partie1);   // Vérifier si la partie existe
        reprendre_partie(nom_partie1);                      // Reprendre la partie
        break;
    case 2 :
        afficher_partie_revisualiser(); // Afficher les parties à revisualiser
        char nom_partie2[100];          // Demander le nom de la partie à revisualise
        printf("Ecrivez le nom de la partie que vous voulez revisualiser ?\n");
        fgets(nom_partie2,100,stdin);
        //scanf("%s",nom_partieB);
        char* new_line2 = "\n";         // Supprimer le retour à la ligne dans le nom de la partie
        nom_partie2[strcspn(nom_partie2,new_line2)] = '\0';
        verifier_existence_partie_revisualiser(nom_partie2);
        revisualiser_partie(nom_partie2);   // Vérifier si la partie existe
    case 3 :
        exit(-1);       // Quitter le programme
        break;
    case 4 :
        affichermenu(); // Retourner au menu principal

    }
}

// Fonction pour afficher les parties sauvegardées que l'utilisateur peut revisualiser
void afficher_partie_revisualiser()
{   // Afficher un message pour indiquer que l'on va lister les parties sauvegardées
    printf("Affichage des parties enregistrees dans le dossier courant :\n");
    DIR * rep = opendir (".");  // Ouvrir le répertoire courant pour lire les fichiers
    int compteur = 0;
    if (rep != NULL)    // Si le répertoire est bien ouvert
    {
        struct dirent * ent;
        // Parcourir les fichiers dans le répertoire
        while ((ent = readdir (rep)) != NULL)
        {
            int taille = strlen(ent->d_name);
            // Vérifier si le fichier est un fichier texte
            if (ent->d_name[taille-1]=='t' && ent->d_name[taille-2]=='x' && ent->d_name[taille-3]=='t')
            {
                char joueur; float temp; int essais, essais_max, victoire;
                // Ouvrir le fichier et lire les données
                FILE *fichier = fopen(ent->d_name, "r");
                fscanf(fichier, "%c %f %d %d %d \n",&joueur,&temp,&essais,&essais_max,&victoire);
                // Si la partie est terminée (victoire = 1 ou 0), l'afficher
                if (victoire == 1 || victoire == 0)
                {
                    for (int i=0;i<taille-4;i++)
                    {
                        printf ("%c", ent->d_name[i]);  // Afficher le nom de la partie sans l'extension
                    }
                    printf ("\n");
                    compteur++;
                }
                fclose(fichier);
            }
        }
        closedir (rep);
        // Si aucune partie n'a été trouvée
        if (compteur == 0) {printf("Aucune partie sauvegarde !");separateur();affichermenu();}
    }
}

// Fonction pour afficher les parties sauvegardées que l'on peut recharger
void afficher_partie_recharger()
{
    // Afficher un message pour indiquer que l'on va lister les parties sauvegardées
    printf("Affichage des parties enregistrees dans le dossier courant :\n");
    // Ouvrir le répertoire courant pour lire les fichiers
    DIR * rep = opendir (".");
    int compteur = 0;
    // Vérifier si le répertoire a pu être ouvert
    if (rep != NULL)
    {
        struct dirent * ent;
        // Parcourir les fichiers dans le répertoire
        while ((ent = readdir (rep)) != NULL)
        {
            // Calculer la taille du nom de fichier
            int taille = strlen(ent->d_name);
            // Vérifier si le fichier est un fichier texte (.txt)
            if (ent->d_name[taille-1]=='t' && ent->d_name[taille-2]=='x' && ent->d_name[taille-3]=='t')
            {
                char joueur; float temp; int essais, victoire;
                // Ouvrir le fichier pour lire les informations de la partie sauvegardée
                FILE *fichier = fopen(ent->d_name, "r");
                // Lire les informations du fichier
                fscanf(fichier, "%c %f %d %d %d \n",&joueur,&temp,&essais,&essais_max,&victoire);
                if (victoire == -1) // Vérifier si la partie est encore en cours (victoire == -1)
                {
                                    // Afficher le nom du fichier sans l'extension .txt
                    for (int i=0;i<taille-4;i++)
                    {
                        printf ("%c", ent->d_name[i]);
                    }
                    printf ("\n");
                    compteur++;     // Incrémenter le compteur des parties affichées
                }
                fclose(fichier);    // Fermer le fichier après lecture
            }
        }
        closedir (rep);             // Fermer le répertoire après avoir parcouru tous les fichiers
        // Si aucune partie n'a été trouvée
        if (compteur == 0) {printf("Aucune partie sauvegarde !");separateur();affichermenu();}  // Retour au menu principal si aucune partie n'est trouvée
    }
}

// Fonction pour vérifier l'existence d'une partie à revisualiser
void verifier_existence_partie_revisualiser(char * nom_partie)
{
    // Ouvrir le répertoire courant pour lire les fichiers
    DIR * rep = opendir(".");
    if (rep == NULL) {
        // Si le répertoire ne peut pas être ouvert, afficher une erreur et quitter
        printf("Erreur lors de l'ouverture du repertoire");
        exit(1);
    }

    int compteur = 0;

    struct dirent * ent;
    while ((ent = readdir(rep)) != NULL)    // Parcourir les fichiers dans le répertoire
    {
        int taille = strlen(ent->d_name);   // Calculer la taille du nom de fichier

        // Vérifie si le fichier se termine par ".txt"
        if (taille > 4 && ent->d_name[taille - 1] == 't' && ent->d_name[taille - 2] == 'x' && ent->d_name[taille - 3] == 't')
        {
            // Extraire le nom du fichier sans l'extension '.txt'
            char nom_sans_extension[taille - 4 + 1];  // Taille - 4 pour enlever '.txt' et ajouter '\0' à la fin
            strncpy(nom_sans_extension, ent->d_name, taille - 4);
            nom_sans_extension[taille - 4] = '\0';  // Ajoute le caractère nul de fin de chaîne

            // Comparer le nom de la partie (sans extension) avec le nom extrait du fichier
            if (strcmp(nom_sans_extension, nom_partie) == 0)
            {
                // Ouvrir le fichier pour lire les informations
                char joueur;
                float temp;
                int essais, victoire;

                FILE * fichier = fopen(ent->d_name, "r");
                if (fichier == NULL) {
                    // Si l'ouverture du fichier échoue, afficher une erreur
                    printf("Erreur lors de l'ouverture du fichier %s\n", ent->d_name);
                    continue;  // Passer au fichier suivant
                }

                // Lire les informations dans le fichier
                if (fscanf(fichier, "%c %f %d %d %d", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
                    // Si la lecture échoue, afficher une erreur
                    printf("Erreur de lecture dans le fichier%s\n", ent->d_name);
                    fclose(fichier);
                    continue;  // Passer au fichier suivant si la lecture échoue
                }

                // Vérifier la victoire
                if (victoire == 1) {
                    compteur++;// Si la partie est gagnée, incrémenter le compteur
                } else if (victoire == 0) {
                    compteur++;// Si la partie est perdue, incrémenter également
                } else {
                    // Si le fichier contient une partie en cours, demander un nouveau nom de partie
                    printf("Aucune partie ne porte ce nom ! Recommencez !\n");
                    fgets(nom_partie, 100, stdin);                          // Lire un nouveau nom de partie
                    nom_partie[strcspn(nom_partie, "\n")] = '\0';           // Supprimer le retour à la ligne
                    verifier_existence_partie_revisualiser(nom_partie);     // Relancer la vérification
                }

                fclose(fichier);    // Fermer le fichier après lecture
                compteur++;         // Incrémenter le compteur
            }
        }
    }

    closedir(rep);                  // Fermer le répertoire après avoir parcouru tous les fichiers

    // Si aucune correspondance n'a été trouvée
    if (compteur == 0) {
        // Afficher un message d'erreur et demander un nouveau nom de partie
        printf("Aucune partie ne porte ce nom ! Recommencez !\n");
        fgets(nom_partie, 100, stdin);
        nom_partie[strcspn(nom_partie, "\n")] = '\0';  // Supprimer le retour à la ligne
        verifier_existence_partie_revisualiser(nom_partie);  // Relancer la vérification
    }
}

// Fonction qui vérifie si une partie peut être rechargée en parcourant les fichiers dans le répertoire courant
void verifier_existence_partie_recharger(char * nom_partie)
{
    // Ouvrir le répertoire courant
    DIR * rep = opendir(".");
    if (rep == NULL) {
        // Si le répertoire ne peut pas être ouvert, afficher une erreur et quitter
        printf("Erreur lors de l'ouverture du repertoire");
        exit(1);
    }

    int compteur = 0;   // Compteur pour suivre le nombre de fichiers correspondants trouvés

    struct dirent * ent;                    // Structure pour parcourir les fichiers du répertoire
    while ((ent = readdir(rep)) != NULL)    // Parcourir chaque fichier du répertoire
    {
        int taille = strlen(ent->d_name);   // Calculer la taille du nom du fichier

        // Vérifie si le fichier se termine par ".txt"
        if (taille > 4 && ent->d_name[taille - 1] == 't' && ent->d_name[taille - 2] == 'x' && ent->d_name[taille - 3] == 't')
        {
            // Extraire le nom du fichier sans l'extension '.txt'
            char nom_sans_extension[taille - 4 + 1];  // Taille - 4 pour enlever '.txt' et ajouter '\0' à la fin
            strncpy(nom_sans_extension, ent->d_name, taille - 4);
            nom_sans_extension[taille - 4] = '\0';  // Ajoute le caractère nul de fin de chaîne

            // Comparer le nom de la partie (sans extension) avec le nom extrait du fichier
            if (strcmp(nom_sans_extension, nom_partie) == 0)
            {
                 // Si les noms correspondent, ouvrir le fichier pour lire les informations
                char joueur;
                float temp;
                int essais, victoire;

                FILE * fichier = fopen(ent->d_name, "r");
                if (fichier == NULL) {
                    // Si l'ouverture du fichier échoue, afficher une erreur et passer au fichier suivant
                    printf("Erreur lors de l'ouverture du fichier %s\n", ent->d_name);
                    continue;  // Passer au fichier suivant
                }

                // Lire les informations du fichier (joueur, température, essais, essais_max, et victoire)
                if (fscanf(fichier, "%c %f %d %d %d", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
                    // Si la lecture échoue, afficher une erreur et passer au fichier suivant
                    printf("Erreur de lecture dans le fichier %s\n", ent->d_name);
                    fclose(fichier);
                    continue;  // Passer au fichier suivant si la lecture échoue
                }

                // Vérifier si la partie est encore en cours (victoire == -1)
                if (victoire == -1) {
                    printf("La partie %s peut-etre reprise !\n", nom_partie);   // Afficher que la partie peut être reprise
                    compteur++;                                                 // Incrémenter le compteur des fichiers trouvés
                }
                fclose(fichier);    // Fermer le fichier après lecture
            }
        }
    }

    closedir(rep);                  // Fermer le répertoire après avoir parcouru tous les fichiers


    // Si aucune correspondance n'a été trouvée
    if (compteur == 0) {
        // Afficher un message d'erreur et demander un nouveau nom de partie
        printf("Aucune partie ne porte ce nom ! Recommencez !\n");
        fgets(nom_partie, 100, stdin);                      // Lire un nouveau nom de partie
        nom_partie[strcspn(nom_partie, "\n")] = '\0';       // Supprimer le retour à la ligne
        verifier_existence_partie_recharger(nom_partie);    // Relancer la vérification
    }
}

// Fonction de validation du choix de l'utilisateur (5 options possibles)
int testchoix5(char ch,int compteur)
{
    if (compteur!=0)    // Si un choix incorrect a été effectué précédemment, demander un nouveau choix
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1; compteur = 0; // Réinitialiser le compteur d'erreur
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};  // Vider le buffer de saisie
        int chprov = testchoix5(ch1,compteur);  // Relancer la fonction pour valider le choix
        return chprov;
    }
    // Vérifier que le choix est compris entre '1' et '4'
    else if (ch<=52 && ch>=49)
    {
        // Selon le choix de l'utilisateur, retourner la valeur correspondante
        switch (ch){
            case 49 : {return 1;}
            case 50 : {return 2;}
            case 51 : {return 3;}
            case 52 : {return 4;}
        };
    }
    // Si le choix est invalide, afficher un message d'erreur et redemander
    else
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1;
        compteur = 0;
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};
        printf("%d",compteur);
        // Relancer la fonction pour valider le choix
        char chprov = testchoix5(ch1,compteur);
        return chprov;
    }
    return 5;   // Retourner une valeur par défaut en cas de problème
}

// Fonction de validation du choix de l'utilisateur (2 options possibles)
int testchoix6(char ch,int compteur)
{
    // Si un choix incorrect a été effectué précédemment, demander un nouveau choix
    if (compteur!=0)
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1; compteur = 0;                                     // Réinitialiser le compteur d'erreur
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};  // Vider le buffer de saisie
        int chprov = testchoix6(ch1,compteur);                      // Relancer la fonction pour valider le choix
        return chprov;
    }
    else if (ch<=50 && ch>=49)      // Vérifier que le choix est compris entre '1' et '2'
    {
        switch (ch){                // Selon le choix de l'utilisateur, retourner la valeur correspondante
            case 49 : {return 1;}
            case 50 : {return 2;}
        };
    }
    else                            // Si le choix est invalide, afficher un message d'erreur et redemander
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1;
        compteur = 0;
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};
        printf("%d",compteur);
        char chprov = testchoix6(ch1,compteur); // Relancer la fonction pour valider le choix
        return chprov;
    }
    return 5;   // Retourner une valeur par défaut en cas de problème
}
