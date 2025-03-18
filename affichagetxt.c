#include "header.h"
#include "affichagetxt.h"
#include "jeuA.h"
#include "jeuB.h"
#include "reprendre_partie.h"
#include "revisualiser_partie.h"
#include "sauvegarde.h"
#include "stat.h"

// Fonction pour afficher un séparateur visuel dans le terminal (ligne de tirets)
void separateur()
{
    printf("\n______________________________________________\n\n");
}

// Fonction pour afficher les règles du jeu MasterMind
void afficherregles()
{
    // Titre des règles du jeu en texte souligné
    printf("\033[4m              Regles du Jeu :              \033[0m \n \n");

    // Description du principe du jeu
    printf("--> Principe du Jeu :\n\n");
    printf("Ce jeu se joue a deux personnes / joueurs, un qui cree la combinaison secrete\n"
           "a faire deviner et l autre joueur qui doit trouver cette combinaison secrete\n"
           "en un nombre limite de tentatives. Le mastermind se joue sur une grande grille \n"
           "composee de 8 a 12 lignes. Chaque rangee represente une tentative pour deviner \n"
           "la combinaison secrete. Il est egalement compose de 4 colonnes. \n");

    // Explication de la création de la combinaison secrète
    printf("\n--> La combinaison secrete :\n\n");
    printf("Pour creer la combinaison secrete, le joueur a la posibiltee d utiliser 6 couleurs \n"
           "parmis le " R "rouge" RESET " / " B "bleu" RESET " / " V "vert" RESET " / " J "jaune"
           RESET " / " P "rose" RESET " / blanc. Il doit choisir 4 couleurs et \n"
           "il peut egalement utiliser plusieurs couleurs identiques sur la meme combinaison. \n"
           "Cette derniere peut donc etre" R " rouge " RESET "/" R " rouge " RESET "/" V " vert "
           RESET "/ blanc ou encore " B "bleu " RESET "/" B " bleu " RESET "/ \n" B " bleu " RESET
           "/" B " bleu\n" RESET);

    // Explication des indices fournis pour aider à deviner la combinaison
    printf("\n--> Les indices :\n\n");
    printf("Afin d aider le joueur qui cherche la combinaison, le second peut indiquer si une couleur \n"
           "est : \n"
           "\t- Bonne couleur et bien place (1)\n"
           "\t- Bonne couleur mais mauvais placement (2) \n"
           "\t- Mauvaise couleur (3) \n \n"

           "Pour cela sur le cote de la grille le joueur va indiquer des couleurs entre " R "Rouge" RESET ", Blanc, et noir.\n"
           "\t-" R " Rouge " RESET "pour la premiere indication (1) \n"
           "\t- Blanc pour la seconde indication (2) \n"
           "\t- Rien ou noir pour la troisieme indication (3)\n");
}

// Fonction pour afficher le menu principal du jeu
void affichermenu()
{
    char ch;
    int choix;
    char ChoisirJoueur;
    int compteur;
    compteur = 0;

    // Titre du menu principal
    printf("\033[4m               MasterMind               \033[0m \n \n");

    // Affichage des options disponibles dans le menu
    printf("1: Nouvelle Partie \n");
    printf("2: Charger une Partie \n");
    printf("3: Statistiques \n");
    printf("4: Regles du Jeu \n");
    printf("5: Quitter le jeu");

    // Affichage d'un séparateur visuel
    separateur();

    // Demander à l'utilisateur de choisir une action parmi celles proposées
    printf("Choisir une action : \n");
    scanf("%c", &ch); while (getchar() != '\n'){compteur++;};   // Lecture de l'entrée utilisateur et nettoyage du buffer
    choix = testchoix(ch,compteur);                             // Appel de la fonction pour valider le choix

    // Action en fonction du choix de l'utilisateur
    switch(choix){
        case 1:     // Nouvelle Partie
            printf("\033[4m              Nouvelle Partie :              \033[0m \n \n");
            printf("Choisir Joueur : \n");
            printf("1: JoueurA (devine la combinaison secrete grace aux indices)\n");
            printf("2: JoueurB (choisi et fait deviner combinaison secrete)\n");
            printf("3: Quitter le jeu\n");
            printf("4: Retour menu principal");

            // Affichage d'un séparateur visuel
            separateur();

            // Demander à l'utilisateur de choisir quel joueur il souhaite être
            printf("Choisis ton joueur :\n");
            compteur = 0;
            scanf(" %c",&ChoisirJoueur); while (getchar() != '\n'){compteur++;};    // Lecture de l'entrée et nettoyage du buffer
            ChoisirJoueur = testchoix2(ChoisirJoueur, compteur);                    // Valider le choix du joueur

            // Démarrer la partie en fonction du joueur choisi
            if (ChoisirJoueur == '1'){
                separateur();
                printf("Tu es le JoueurA, a toi de deviner la combinaison secrete grace aux indices ! \n");
                choix_niveau_joueurA(); // Fonction pour choisir le niveau du joueur A
            }
            else if (ChoisirJoueur == '2'){
                separateur();
                printf("Tu es le JoueurB, a toi de choisir une combinaison secrete et de la faire deviner ! \n");
                jouerB();   // Fonction pour jouer en tant que Joueur B
            }
            else if (ChoisirJoueur == '3'){
                exit(-1);
            }
            else if (ChoisirJoueur == '4'){
                affichermenu(); // Retour au menu principal
            }
            break;

        case 2: // Charger une Partie

           separateur();
           charger_reprendre_partie();  // Charger une partie sauvegardée
           break;

        case 3: {   // Afficher les statistiques
            separateur();
            lire_statistiques(pseudo);      // Afficher les statistiques du joueur
            affichermenu();                 // Retour au menu principal
            break;
        }
        case 4:{    // Afficher les règles du jeu
            afficherregles();               // Appeler la fonction pour afficher les règles
            separateur();
            affichermenu();
            break;
        }
        case 5:{    //Quitter le jeu
                exit(-1);
            // important pour quitter le jeu à tout moment
        }
    }
}

// Definition : fonction d'affichage en couleur

void printf_rouge(char carac_couleur)
{
    printf(R " %c " RESET,carac_couleur);
}

void printf_bleu(char carac_couleur)
{
    printf(B " %c " RESET,carac_couleur);
}

void printf_vert(char carac_couleur)
{
    printf(V " %c " RESET,carac_couleur);
}

void printf_jaune(char carac_couleur)
{
    printf(J " %c " RESET,carac_couleur);
}

void printf_rose(char carac_couleur)
{
    printf(P " %c " RESET,carac_couleur);
}

void printf_blanc(char carac_couleur)
{
    printf(W " %c " RESET,carac_couleur);
}

void printf_couleur(char carac_couleur)
{
    if (carac_couleur == 'R')
    {
        printf(R "%c" RESET, carac_couleur);
    }
    else if (carac_couleur == 'V')
    {
        printf(V "%c" RESET, carac_couleur);
    }
    else if (carac_couleur == 'B')
    {
        printf(B "%c" RESET, carac_couleur);
    }
    else if (carac_couleur == 'J')
    {
        printf(J "%c" RESET, carac_couleur);
    }
    else if (carac_couleur == 'P')
    {
        printf(P "%c" RESET, carac_couleur);
    }
    else if (carac_couleur == 'W')
    {
        printf(W "%c" RESET, carac_couleur);
    }
}

// Fonction de validation pour un choix d'action
int testchoix(char ch,int compteur)
{
    // Vérifie si le compteur est différent de zéro
    if (compteur!=0)
    {
        // Si l'entrée est invalide, afficher un message d'erreur et redemander l'entrée
        printf("Choix non conforme ! Veuillez recommencer !\n");
        printf("Choisir une action : \n");
        char ch1;
        compteur = 0;   // Réinitialiser le compteur d'erreur
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};  // Nettoyer le buffer d'entrée
        // Appeler la fonction récursivement pour valider le nouveau choix
        int chprov = testchoix(ch1,compteur);
        return chprov;// Retourner la valeur validée
    }
    // Vérifie que le choix (ch) est un chiffre entre 1 et 5 inclus
    if (ch<=53 && ch>=49)
    {
        // Selon la valeur du choix, retourner un numéro correspondant à une action spécifique
        switch (ch){
            case 49 : {return 1;}
            case 50 : {return 2;}
            case 51 : {return 3;}
            case 52 : {return 4;}
            case 53 : {return 5;}
        };
    }
    else
    {
        // Si l'entrée n'est pas conforme (en dehors de la plage 1-5), afficher un message d'erreur
        printf("Choix non conforme ! Veuillez recommencer !\n");
        printf("Choisir une action : \n");
        char ch1;
        compteur = 0;                                               // Réinitialiser le compteur
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};  // Nettoyer le buffer d'entrée
        printf("%d",compteur);                                      // Afficher le nombre d'entrées invalides
        // Appeler récursivement la fonction pour obtenir un choix valide
        int chprov = testchoix(ch1,compteur);
        return chprov;
    }
    return 5;
}

// Fonction de validation pour le choix du joueur (choisir entre '1', '2', '3' ou '4')
char testchoix2(char ch,int compteur)
{
    // Vérifie si le compteur est différent de zéro (indiquant que l'entrée précédente n'était pas correcte)
    if (compteur!=0)
    {
        // Si l'entrée est invalide, afficher un message d'erreur et redemander l'entrée
        printf("Choix non conforme ! Veuillez recommencer !\n");
        printf("Choisis ton joueur : \n");
        char ch1;
        compteur = 0;                                               // Réinitialiser le compteur d'erreur
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};  // Nettoyer le buffer d'entrée
        // Appeler la fonction récursivement pour valider le nouveau choix
        char chprov = testchoix2(ch1,compteur);
        return chprov;
    }
    // Vérifie que le choix (ch) est un chiffre entre 1 et 4 inclus
    if (ch<=52 && ch>=49)
    {
        // Selon la valeur du choix, retourner un caractère correspondant au joueur choisi
        switch (ch){
            case 49 : {return '1';}
            case 50 : {return '2';}
            case 51 : {return '3';}
            case 52 : {return '4';}
        };
    }
    else
    {
        // Si l'entrée n'est pas conforme (en dehors de la plage 1-4), afficher un message d'erreur
        printf("Choix non conforme ! Veuillez recommencer !\n");
        printf("Choisis ton joueur : \n");
        char ch1;
        compteur = 0;                                               // Réinitialiser le compteur
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};  // Nettoyer le buffer d'entrée
        printf("%d",compteur);                                      // Afficher le nombre d'entrées invalides
        // Appeler récursivement la fonction pour obtenir un choix valide
        char chprov = testchoix2(ch1,compteur);
        return chprov;
    }
    return 5;
}

// Fonction pour valider et modifier le nom de la partie
void test_nompartie(char * nom_partie)
{
    // Vérifie si le nom de la partie contient un espace
    if (strchr(nom_partie, ' ') != NULL){
        // Si un espace est trouvé, afficher un message d'erreur et demander un nouveau nom
        printf("Donne un nom a ta partie qui ne contient pas d'espace : ");
        fgets(nom_partie,100,stdin);                        // Lire le nouveau nom de la partie
        char* new_line = "\n";                              // Définir le caractère de nouvelle ligne
        nom_partie[strcspn(nom_partie,new_line)] = '\0';    // Supprimer le caractère de nouvelle ligne
        // Appeler récursivement la fonction pour vérifier à nouveau le nom
        test_nompartie(nom_partie);
    }
}
