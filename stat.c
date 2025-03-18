#include "header.h"
#include "affichagetxt.h"
#include "jeuA.h"
#include "jeuB.h"
#include "reprendre_partie.h"
#include "revisualiser_partie.h"
#include "sauvegarde.h"
#include "stat.h"

// Fonction permettant de demander et saisir le pseudo du joueur
void demanderPseudo(char *pseudo) {
    printf("Entrez votre pseudo (pseudo existant ou nouveau pseudo) : ");
    fgets(pseudo, MAX_PSEUDO, stdin);   // Lecture du pseudo depuis l'entrée standard
    // Enlever le caractère '\n' à la fin si présent
    if (strlen(pseudo) > 0 && pseudo[strlen(pseudo)-1] == '\n') {
       pseudo[strlen(pseudo)-1] = '\0';
    }
}

// Fonction pour vérifier si un fichier avec le pseudo existe déjà
int verifierFichier(char *pseudo) {
    FILE *fichier = fopen(pseudo, "r"); // Ouvrir le fichier en mode lecture
    if (fichier) {
        fclose(fichier);
        return 1;                       // Fichier existe
    }
    return 0; // Fichier n'existe pas
}

// Fonction pour créer un fichier pour un nouveau joueur avec ses statistiques initiales
void creerFichier(char *pseudo, Statistiques *stats) {
    FILE *fichier = fopen(pseudo, "w");                                 // Ouvrir le fichier en mode écriture
    if (fichier) {
        fprintf(fichier, "%d %d %d %f %f %d %d", stats->partiesJouees,  // Écrire les statistiques du joueur dans le fichier
                stats->victoires, stats->defaites, stats->pourcentage_Victoires,
                stats->pourcentage_Defaites, stats->temps_De_JeuTotal, stats->tentatives_Totales);
        fclose(fichier);    // Fermer le fichier après l'écriture
    } else {
        printf("Erreur lors de la création du fichier.\n"); // Afficher une erreur si le fichier ne peut pas être créé
    }
}

// Fonction pour charger les statistiques d'un joueur depuis un fichier
void chargerFichier(char *pseudo, Statistiques *stats) {
    FILE *fichier = fopen(pseudo, "r");     // Ouvrir le fichier en mode lecture
    if (fichier) {
        if (fscanf(fichier, "%d %d %d %f %f %d %d", // Lire les statistiques du joueur depuis le fichier
                   &stats->partiesJouees, &stats->victoires, &stats->defaites,
                   &stats->pourcentage_Victoires, &stats->pourcentage_Defaites,
                   &stats->temps_De_JeuTotal, &stats->tentatives_Totales) != 7) {
            printf("Erreur lors de la lecture du fichier.\n");  // Si la lecture échoue, afficher une erreur
        }
        fclose(fichier);                                    // Fermer le fichier après la lecture
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n"); // Afficher une erreur si le fichier n'existe pas
    }
}

// Fonction pour sauvegarder les statistiques mises à jour dans le fichier
void sauvegarderFichier(char *pseudo, Statistiques *stats) {
    FILE *fichier = fopen(pseudo, "r+");  // Ouvrir en lecture et écriture
    if (fichier) {
        // Replacer uniquement les parties mises à jour dans le fichier
        fseek(fichier, 0, SEEK_SET);  // Remettre le curseur au début du fichier
        fprintf(fichier, "%d %d %d %f %f %d %d", stats->partiesJouees,      // Réécrire les statistiques mises à jour dans le fichier
                stats->victoires, stats->defaites, stats->pourcentage_Victoires,
                stats->pourcentage_Defaites, stats->temps_De_JeuTotal, stats->tentatives_Totales);
        fclose(fichier);    // Fermer le fichier après l'écriture
    } else {
        printf("Erreur lors de l'enregistrement du fichier.\n");    // Afficher une erreur si l'ouverture échoue
    }
}

// Fonction pour mettre à jour les statistiques d'un joueur après une partie
void mettreAJourStatistiques(char *pseudo, int victoire) {
    Statistiques stats;

    // Charger les statistiques existantes du fichier
    chargerFichier(pseudo, &stats);

    // Mise à jour du nombre de parties jouées
    stats.partiesJouees++;

    // Mise à jour des victoires et des défaites en fonction du résultat
    if (victoire == 1) {
        stats.victoires++;  // Incrémenter les victoires si le joueur a gagné
    } else {
        stats.defaites++;   // Incrémenter les défaites si le joueur a perdu
    }

    // Calcul du pourcentage de victoires
    if (stats.partiesJouees > 0) {
        stats.pourcentage_Victoires = (float)stats.victoires / stats.partiesJouees * 100;
    }

    // Calcul du pourcentage de défaites
    if (stats.partiesJouees > 0) {
        stats.pourcentage_Defaites = (float)stats.defaites / stats.partiesJouees * 100;
    }

    // Sauvegarder les statistiques mises à jour dans le fichier
    sauvegarderFichier(pseudo, &stats);
}

// Fonction pour ajouter les résultats d'une partie à un fichier
void ajouterResultatPartie(char role,char *pseudo,char nompartie[],float tempsmoyen_reponse,int tentatives_partie, int partiegagne) {
    ResultatPartie * partie = malloc(sizeof(ResultatPartie));   // Allouer dynamiquement une structure pour stocker les résultats de la partie
    partie->role_joueur = role;                         // Affecter le rôle du joueur (par exemple 'H' ou 'A')
    strcpy(partie->nomPartie, nompartie);               // Copier le nom de la partie
    partie->tempsMoyenReponse = tempsmoyen_reponse;     // Enregistrer le temps moyen de réponse
    partie->tentatives = tentatives_partie;             // Enregistrer le nombre de tentatives
    partie->partieGagnee = partiegagne;                 // Enregistrer si la partie a été gagnée ou non

    FILE *fichier = fopen(pseudo, "a+");     // Ouvrir le fichier en mode ajout (a+)
    if (fichier) {
        // Écrire la structure dans le fichier
        fprintf(fichier, "\n%c %s %f %d %d", partie->role_joueur, partie->nomPartie,partie->tempsMoyenReponse,partie->tentatives,partie->partieGagnee);
        fclose(fichier);// Fermer le fichier après l'écriture
    } else {
        printf("Erreur lors de l'ouverture du fichier pour ajouter les résultats.\n");  // Afficher une erreur si l'ouverture échoue
    }
}

// Fonction de création ou de chargement du joueur
void creation_joueur() {
    // Initialisation des statistiques du joueur avec des valeurs par défaut
    Statistiques stats = {0, 0, 0, 0.0, 0.0, 0.0, 0};

    // Demander le pseudo du joueur via la fonction demanderPseudo
    demanderPseudo(pseudo);

    // Vérifier si le fichier du joueur existe
    if (!verifierFichier(pseudo)) {
        // Si le fichier n'existe pas, créer le fichier
        printf("Bienvenue, nouveau joueur !\n\n");
        creerFichier(pseudo, &stats);   // Création du fichier et écriture des statistiques initiales
    } else {
        // Si le fichier existe, charger les données du fichier
        printf("Re-bonjour, %s !\n", pseudo);
        chargerFichier(pseudo, &stats); // Charger les statistiques depuis le fichier
    }

    // Affichage des statistiques du joueur
    printf("Statistiques du joueur %s :\n", pseudo);
    printf("Parties jouees: %d\n", stats.partiesJouees);
    printf("Victoires: %d\n", stats.victoires);
    printf("Defaites: %d\n", stats.defaites);
    printf("Pourcentage de victoires: %f\n\n", stats.pourcentage_Victoires);

    // Appel de la fonction affichermenu pour afficher le menu du jeu
    affichermenu();
}

// Fonction pour lire et afficher les statistiques à partir d'un fichier
void lire_statistiques(char * nomFichier) {
    FILE *fichier = fopen(nomFichier, "r"); // Ouvrir le fichier en mode lecture
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichier);  // Si le fichier ne peut pas être ouvert, afficher un message d'erreur
        return;
    }
    // Affichage du titre pour les statistiques du joueur
    printf("Affichage des statistiques pour le joueur %s :\n\n",pseudo);

    // Lecture de la première ligne (Statistiques)
    Statistiques * stats = malloc(sizeof(Statistiques));
    fscanf(fichier, "%d %d %d %f %f %d %d\n",
           &stats->partiesJouees,
           &stats->victoires,
           &stats->defaites,
           &stats->pourcentage_Victoires,
           &stats->pourcentage_Defaites,
           &stats->temps_De_JeuTotal,
           &stats->tentatives_Totales);

    // Affichage des informations de la première ligne (Statistiques)
    printf("Statistiques Globales :\n");
    printf("Parties Jouees: %d\n", stats->partiesJouees);
    printf("Victoires: %d\n", stats->victoires);
    printf("Defaites: %d\n", stats->defaites);
    printf("Pourcentage de Victoires: %f\n", stats->pourcentage_Victoires);
    printf("Pourcentage de Defaites: %f\n", stats->pourcentage_Defaites);
    //printf("Temps de Jeu Total: %d\n", stats.temps_De_JeuTotal);
    //printf("Tentatives Totales: %d\n", stats.tentatives_Totales);

    // Lecture des lignes suivantes (ResultatPartie)
    printf("\nStatistiques partie par partie :\n");
    ResultatPartie * resultat = malloc(sizeof(ResultatPartie)); // Allouer de la mémoire pour une structure ResultatPartie
    // Lecture des résultats des parties successives dans le fichier
    while (fscanf(fichier, "%c %s %f %d %d\n",
                  &resultat->role_joueur,
                  resultat->nomPartie,
                  &resultat->tempsMoyenReponse,
                  &resultat->tentatives,
                  &resultat->partieGagnee) != EOF) {
        // Affichage des résultats de chaque partie
        printf("Role du joueur : Joueur %c\n", resultat->role_joueur);
        printf("Nom de la Partie: %s\n", resultat->nomPartie);
        printf("Temps Moyen de Reponse: %f\n", resultat->tempsMoyenReponse);
        printf("Tentatives: %d\n", resultat->tentatives);
        printf("Partie Gagnee: %d\n", resultat->partieGagnee);
        printf("\n");
    }
    fclose(fichier);
}
