#include "header.h"
#include "affichagetxt.h"
#include "jeuA.h"
#include "jeuB.h"
#include "reprendre_partie.h"
#include "revisualiser_partie.h"
#include "sauvegarde.h"
#include "stat.h"

// Fonction pour reprendre une partie précédemment sauvegardée
void reprendre_partie(char * nom_partie)
{
    // Création du nom temporaire de fichier à partir du nom de la partie
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);    // Copie du nom de la partie
    strcat(nom_temp, ".txt");       // Ajout de l'extension ".txt" pour le fichier

    // Ouverture du fichier correspondant pour lire l'état de la partie
    FILE * fichier = fopen(nom_temp, "r");
    char joueur;            // Variable pour stocker l'identifiant du joueur
    float temp;             // Variable pour stocker le temps moyen de réponse
    int essais, victoire;   // Variables pour stocker le nombre d'essais et le statut de victoire

    // Lecture des données du fichier : joueur, temps, essais, essais max et victoire
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        printf("Erreur de lecture dans le fichier1 %s\n", nom_partie);  // En cas d'erreur de lecture, afficher un message et fermer le fichier
        fclose(fichier);
        exit(-1);
    }
    // Selon le joueur (A ou B), reprendre la partie correspondante
    if (joueur == 'A')
    {
        // Si c'est le joueur A, on revisualise les essais précédents et on reprend la partie A
        revisualiser_essai_precedentA(nom_partie);
        reprendre_partieA(nom_partie);
    }
    else if (joueur == 'B')
    {
        // Si c'est le joueur B, on revisualise les essais précédents et on reprend la partie B
        revisualiser_essai_precedentB(nom_partie);
        reprendre_partieB(nom_partie);
    }
}

// Fonction pour reprendre la partie du joueur B
void reprendre_partieB(char * nom_partie)
{
    printf("\nCi-dessus se trouve les essais precedents !\n");
    printf("Maintenant reprenons la partie :\n");

    // Création du nom temporaire de fichier à partir du nom de la partie
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp, ".txt");
    // Ouverture du fichier contenant l'état de la partie
    FILE * fichier = fopen(nom_temp, "r");
    // Variables pour suivre le nombre de bonnes et mauvaises couleurs
    int bonne_place = 0, mauvaise_place = 0, compteur;
    char bonne_place_prov, mauvaise_place_prov;
    char joueur;
    float temp;
    int essais, victoire;
    float moytemps;

    // Lecture des informations du fichier : joueur, temps, essais, etc.
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        printf("Erreur de lecture dans le fichier1 %s\n", nom_partie);
        exit(-1);
    }

    // Assignation du temps moyen à partir du fichier
    moytemps = temp;

    // Création et régénération de la file pour contenir toutes les combinaisons possibles
    File *toutes_les_combi = creerFile();
    toutes_les_combi = regenererFile(toutes_les_combi,nom_partie);

    // Demande au joueur de donner des indices pour chaque proposition
    printf("\nMaintenant a mon tour de faire des propositions et a toi de me donner des indices !");
    printf("\nProposition de combinaison : ");
    char combi_defile[4];
    toutes_les_combi = proposer_combinaison(toutes_les_combi, combi_defile);

    // Boucle tant que la combinaison n'est pas correcte ou que toutes les combinaisons ne sont pas testées
    while (bonne_place != 4 && toutes_les_combi->tete != NULL) {
        essais++;                   // Incrémentation du nombre d'essais
        clock_t debut = clock();    // Démarrer le chronomètre pour calculer le temps de réponse

        printf("\nCombien de couleurs sont a la bonne place ?\nVotre reponse (Q pour quitter / M retour menu) : ");
        scanf("%c", &bonne_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};   // Nettoyer le buffer
        bonne_place = testchoix3(bonne_place_prov,compteur);                                    // Test de la réponse
        if (bonne_place == -1){
            // Si l'utilisateur veut quitter, sauvegarder l'état et sortir
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            return exit(-1);}
        else if (bonne_place == -2){
            // Si l'utilisateur veut revenir au menu, sauvegarder et revenir au menu
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            affichermenu();}

        // Demande du nombre de couleurs correctes mais mal placées
        printf("Combien de couleurs sont correctes mais a la mauvaise place ?\nVotre reponse (Q pour quitter / M pour menu) : ");
        scanf("%c", &mauvaise_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};    // Nettoyer le buffer
        mauvaise_place = testchoix3(mauvaise_place_prov,compteur);
        if (mauvaise_place == -1){
            // Si l'utilisateur veut quitter, sauvegarder et sortir
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            return exit(-1);}
        else if (bonne_place == -2){
            // Si l'utilisateur veut revenir au menu, sauvegarder et revenir au menu
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            affichermenu();}

        // Calcul du temps écoulé pour cet essai
        clock_t fin = clock();
        float temps = ((float)(fin-debut))/CLOCKS_PER_SEC;  // Temps en secondes
        moytemps = moyenne_temps(temps,essais,moytemps);    // Calcul du temps moyen

        // Ajout des informations de l'essai actuel
        ajouter_essai(nom_partie, essais, combi_defile, bonne_place, mauvaise_place);

        // Mise à jour de la file de combinaisons possibles
        toutes_les_combi = eliminer_comb(toutes_les_combi, combi_defile, bonne_place, mauvaise_place);
        // Si des combinaisons possibles restent, proposer une nouvelle combinaison
        if (toutes_les_combi->tete != NULL) {
            printf("Proposition suivante : ");
            toutes_les_combi = proposer_combinaison(toutes_les_combi, combi_defile);
        }
    }
    // Si la combinaison correcte est trouvée
    if (bonne_place == 4) {
        printf("\nSolution trouvee !\n");
        int victoire = 0;                                                       // Le joueur B a gagné
        mettreAJourStatistiques(pseudo,victoire);                               // Met à jour les statistiques du joueur
        ajouterResultatPartie('B',pseudo,nom_partie,moytemps,essais,victoire);  // Sauvegarde les résultats de la partie
        sauvegarderetat(nom_partie,'B',moytemps,essais,0,victoire);             // Sauvegarde l'état de la partie finale
        demande_sauvegarde(nom_partie);                                         // Demande si le joueur veut sauvegarder la partie
        separateur();
        affichermenu();
    } else {
        // Si aucune solution n'est trouvée, le joueur perd
        essais++;                   // Incrémentation du nombre d'essais
        clock_t debut = clock();    // Démarre un nouveau chronomètre

        // Demande à nouveau le nombre de couleurs à la bonne place
        printf("\nCombien de couleurs sont a la bonne place ?\nVotre reponse (Q pour quitter / M retour menu) : ");
        scanf("%c", &bonne_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};
        bonne_place = testchoix3(bonne_place_prov,compteur);

        if (bonne_place == -1){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            return exit(-1);}

        if (bonne_place == -2){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            affichermenu();}

        // Demande du nombre de couleurs correctes mais mal placées
        printf("Combien de couleurs sont correctes mais a la mauvaise place ?\nVotre reponse (Q pour quitter / M retour menu) : ");
        scanf("%c", &mauvaise_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};
        mauvaise_place = testchoix3(mauvaise_place_prov,compteur);

        if (mauvaise_place == -1){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            return exit(-1);}

        if (bonne_place == -2){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partie,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partie);
            demande_sauvegarde(nom_partie);
            affichermenu();}

        // Calcul du temps écoulé pour cet essai et mise à jour du temps moyen
        clock_t fin = clock();
        float temps = ((float)(fin-debut))/CLOCKS_PER_SEC;
        moytemps = moyenne_temps(temps,essais,moytemps);    // Calcul du nouveau temps moyen

        // Ajout de l'essai actuel dans l'enregistrement de la partie
        ajouter_essai(nom_partie, essais, combi_defile, bonne_place, mauvaise_place);

        // Si la combinaison est correcte, le joueur a gagné
        if(bonne_place == 4) {
        printf("\nSolution trouvee !\n");
        int victoire = 0;
        mettreAJourStatistiques(pseudo,victoire);
        ajouterResultatPartie('B',pseudo,nom_partie,moytemps,essais,victoire);
        sauvegarderetat(nom_partie,'B',moytemps,essais,0,victoire);
        demande_sauvegarde(nom_partie);
        separateur();
        affichermenu();
        }
        // Si aucune solution n'est trouvée après avoir épuisé les tentatives
        else {
        printf("\nPerdu ! Aucune solution trouvee !\n");
        int victoire = 1;
        mettreAJourStatistiques(pseudo,victoire);
        ajouterResultatPartie('B',pseudo,nom_partie,moytemps,essais,victoire);
        sauvegarderetat(nom_partie,'A',moytemps,essais,0,victoire);
        demande_sauvegarde(nom_partie);
        separateur();
        affichermenu();}
    }
}

// Fonction pour reprendre une partie en cours pour le joueur A
void reprendre_partieA(char * nom_partie)
{
    // Affichage des informations sur la partie à reprendre
    printf("\nCi-dessus se trouve les essais precedents !\n");
    printf("Maintenant reprenons la partie :\n");

    // Construction du nom du fichier de la partie à partir du nom donné
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp, ".txt");               // Ajout de l'extension .txt au nom du fichier
    FILE * fichier = fopen(nom_temp, "r");  // Ouverture du fichier en mode lecture
    char code[taille_code], proposition[taille_code+100];
    int bonne_place = 0, mauvaise_place = 0;
    char joueur;
    float temp;
    int essais, victoire;

    // Lecture des informations de la partie (joueur, temps, essais, essais max, victoire) depuis le fichier
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        // Si la lecture échoue, afficher un message d'erreur et quitter le programme
        printf("Erreur de lecture dans le fichier1 %s\n", nom_partie);
        exit(-1);
    }
    // Affichage d'un message pour démarrer la devinette de la combinaison secrète
    printf("\nDevinez la combinaison secrete.\n");


    float moytemps = temp ;
    float temps_joueurA;

    // Boucle principale du jeu, où les essais sont effectués jusqu'à ce que le joueur dépasse le nombre d'essais max
    while (essais < essais_max) {
            // Demander au joueur de faire une proposition et de donner un temps
            obtenir_proposition_du_joueur(proposition,&temps_joueurA);
        // Si le joueur souhaite quitter
        if (proposition[0]=='Q')
        {
            // Sauvegarder l'état de la partie avant de quitter
            sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,-1);
            demande_sauvegarde(nom_partie);
            return(exit(-1));
        }
        // Si le joueur souhaite revenir au menu
        else if (proposition[0]=='M')
        {
            // Sauvegarder l'état de la partie avant de revenir au menu
            sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,-1);
            demande_sauvegarde(nom_partie);
            affichermenu();
        }
            // Evaluation de la proposition du joueur
            evaluer_proposition(code, proposition, &bonne_place, &mauvaise_place);
            essais++;   // Incrémentation du nombre d'essais

        // Si la combinaison est correcte (bonne place == taille du code)
        if (bonne_place == taille_code) {  // Vérifie tout est correct
            // Affichage d'un message de victoire et sauvegarde du résultat
            printf("BRAVO ! Vous avez gagne en %d essais.", essais);
            ajouter_essai(nom_partie, essais, proposition, bonne_place, mauvaise_place);
            victoire = 1;
            moytemps = moyenne_temps(temps_joueurA,essais,moytemps);                // Calcul du temps moyen
            mettreAJourStatistiques(pseudo,victoire);                               // Mise à jour des statistiques
            ajouterResultatPartie('A',pseudo,nom_partie,moytemps,essais,victoire);  // Enregistrement du résultat
            sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,victoire);    // Sauvegarde de l'état
            demande_sauvegarde(nom_partie);
            separateur();                                                           // Affichage d'une ligne de séparation
            affichermenu();
        }
        else {
            // Affichage du résultat pour l'essai actuel (bonnes et mauvaises places)
            printf("Resultat : " R "%d bonne place" RESET ", %d mauvaise place\n", bonne_place, mauvaise_place);
            moytemps = moyenne_temps(temps_joueurA,essais,moytemps);                        // Mise à jour du temps moyen
            ajouter_essai(nom_partie, essais, proposition, bonne_place, mauvaise_place);    // Enregistrement de l'essai
        }
    }

    // Si IL a pas trouvé la combinaison
    printf("\nC'est perdu ! La combinaison secrete etait : ");
    for (int i = 0; i < taille_code; i++) {
        // Affichage de la combinaison secrète
        printf("%c ", code[i]);
    }
    printf("\n");
    printf("Peut-etre la prochaine fois !\n");
    victoire = 0;                                                           // Définition de la victoire à 0 (échec)
    mettreAJourStatistiques(pseudo,victoire);                               // Mise à jour des statistiques
    ajouterResultatPartie('A',pseudo,nom_partie,moytemps,essais,victoire);  // Enregistrement du résultat
    sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,victoire);    // Sauvegarde de l'état
    demande_sauvegarde(nom_partie);
    separateur();                                                           // Affichage d'une ligne de séparation
    affichermenu();
}

// Fonction pour revoir les essais précédents dans une partie pour le joueur A
void revisualiser_essai_precedentA(char * nom_partie)
{
    // Construction du nom du fichier contenant les informations de la partie
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp,".txt");

    separateur();   // Affichage d'une ligne de séparation
    printf("Nom de la partie : %s\n", nom_temp);

    // Ouverture du fichier de la partie en mode lecture
    FILE * fichier = fopen(nom_temp, "r");
    char joueur;
    float temp;
    int essais, victoire;

    // Lecture des informations initiales de la partie depuis le fichier
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        // Si la lecture échoue, afficher un message d'erreur et quitter le programme
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        exit(-1);
    }

    // Affichage des informations lues à partir du fichier
    printf("Role du joueur : Joueur %c\n", joueur);
    printf("Nombres d'essais : %d essais\n",essais);
    printf("Nombres d'essais max : %d essais\n",essais_max);
    printf("Victoire : %d\n",victoire);

    // Lecture de la combinaison secrète dans le fichier
    char combinaison[4];


    if (fscanf(fichier, "%c %c %c %c\n",&combinaison[0],&combinaison[1],&combinaison[2],&combinaison[3]) != 4){
        // Si la lecture échoue, afficher un message d'erreur et quitter le programme
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        fclose(fichier);
        exit(-1);
    }

    char proposition[5];
    int bonne_place, mauvaise_place;

    // Boucle pour lire chaque essai précédent
    while(fscanf(fichier, "%d %c%c%c%c %d %d\n",&essais,&proposition[0],&proposition[1],
                  &proposition[2],&proposition[3],&bonne_place,&mauvaise_place)!=EOF)
    {
        // Affichage des informations de chaque essai
        printf("\nEssai numero : %d\n",essais);
        printf("Entrez votre proposition, il s'agira d'une suite de 4 couleurs (" R "R" RESET ","B "B" RESET ","
           V "V" RESET "," J "J" RESET "," P "P" RESET "," W "W" RESET ") (Q pour quitter) : ");
        printf("%c%c%c%c",proposition[0], proposition[1],proposition[2], proposition[3]);
        printf("\nResultat : " R "%d bonne place" RESET ", %d mauvaise place\n", bonne_place, mauvaise_place);
    }
}

// Fonction permettant de visualiser les essais précédents pour le joueur B dans une partie spécifique
void revisualiser_essai_precedentB(char * nom_partie)
{
    // Création du nom du fichier à partir du nom de la partie
    char nom_temp[100];
    strcpy(nom_temp,nom_partie);
    strcat(nom_temp, ".txt");

    // Affichage d'une ligne de séparation et du nom de la partie
    separateur();
    printf("Nom de la partie : %s\n", nom_temp);

    // Ouverture du fichier contenant les informations de la partie
    FILE * fichier = fopen(nom_temp, "r");
    char joueur;
    float temp;
    int essais, victoire;

    // Lecture des informations générales de la partie (joueur, temps, essais, etc.)
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        exit(-1);
    }

    // Affichage des informations du joueur et des essais
    printf("Role du joueur : Joueur %c\n", joueur);
    printf("Nombres d'essais : %d essais\n",essais);
    printf("Victoire : %d\n",victoire);

    // Lecture de la combinaison secrète à faire deviner par le joueur
    char combinaison[4];

    if (fscanf(fichier, "%c %c %c %c\n",&combinaison[0],&combinaison[1],&combinaison[2],&combinaison[3]) != 4){
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        fclose(fichier);
        exit(-1);
    }
    printf("\nRappel : La combinaison secrete que vous voulez faire deviner est : %c%c%c%c\n\n",combinaison[0], combinaison[1], combinaison[2], combinaison[3]);

    char proposition[5];
    int bonne_place, mauvaise_place;
    // Lecture des essais précédents dans une boucle, affichage des résultats
    while(1) {
        // Lecture de chaque essai (proposition et résultat) du fichier
        if (fscanf(fichier, "%d %c%c%c%c %d %d\n",&essais,&proposition[0],&proposition[1],
                  &proposition[2],&proposition[3],&bonne_place,&mauvaise_place)==7)
                  {
                      // Affichage des détails de l'essai (proposition et résultats)
                      printf("\nEssai numero : %d\n",essais);
                      printf("Proposition de combinaison de l'ordinateur : %c%c%c%c\n",proposition[0],
                             proposition[1], proposition[2], proposition[3]);
                      printf("\nCombien de couleurs sont a la bonne place ?\nVotre reponse (-1 pour quitter) : "
                             R "%d bonne place" RESET, bonne_place);
                      printf("\nCombien de couleurs sont a la mauvaise place ?\nVotre reponse (-1 pour quitter) : "
                             "%d mauvaise place \n", mauvaise_place);
                  }
        else
        {
            // Si la lecture échoue (fin du fichier), on sort de la boucle
            break;
        }
    }
    // Fermeture du fichier après avoir terminé la visualisation des essais
    fclose(fichier);
}

// Fonction pour régénérer la file des combinaisons possibles après avoir lu une partie sauvegardée
File * regenererFile(File * toutes_les_combi, char *nom_partie)
{
    // Création du nom du fichier de la partie et du fichier temporaire
    char nom_temp[100];
    strcpy(nom_temp, nom_partie);
    strcat(nom_temp, ".txt");
    char nom_temp2[100] = "Fichier_Provisoire.txt";

    // Ouverture des fichiers en lecture et en écriture
    FILE * fichier = fopen(nom_temp, "r");
    FILE * fichier2 = fopen(nom_temp2, "w");

    if (fichier == NULL || fichier2 == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        exit(-1);
    }

    char joueur;
    float temp;
    int essais, victoire;
    int couleur1, couleur2, couleur3, couleur4;

    // Lecture des informations initiales de la partie (joueur, temps, essais, etc.)
    if (fscanf(fichier, "%c %f %d %d %d \n", &joueur, &temp, &essais, &essais_max, &victoire) != 5) {
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        fclose(fichier);
        fclose(fichier2);
        exit(-1);
    }
    fprintf(fichier2, "%c %f %d %d %d \n", joueur, temp, essais, essais_max, victoire);

    char combinaison[4];
    if (fscanf(fichier, "%c %c %c %c\n", &combinaison[0], &combinaison[1], &combinaison[2], &combinaison[3]) != 4) {
        printf("Erreur de lecture dans le fichier %s\n", nom_partie);
        fclose(fichier);
        fclose(fichier2);
        exit(-1);
    }
    // Écriture des informations initiales dans le fichier provisoire
    fprintf(fichier2, "%c %c %c %c\n", combinaison[0], combinaison[1], combinaison[2], combinaison[3]);

    char proposition[5];
    int bonne_place, mauvaise_place;
    int nb_essais = essais;

    // Copier les essais précédents
    for (int i = 0; i < nb_essais; i++) {
        if (fscanf(fichier, "%d %c%c%c%c %d %d\n", &essais, &proposition[0], &proposition[1],
                  &proposition[2], &proposition[3], &bonne_place, &mauvaise_place) != 7) {
            printf("Erreur de lecture dans le fichier %s\n", nom_partie);
            fclose(fichier);
            fclose(fichier2);
            exit(-1);
        }
        // Écriture des essais dans le fichier provisoire
        fprintf(fichier2, "%d %c%c%c%c %d %d\n", essais, proposition[0], proposition[1],
                proposition[2], proposition[3], bonne_place, mauvaise_place);
    }

    // Copier les combinaisons restantes
    while (fscanf(fichier, "%d %d %d %d ->\n", &couleur1, &couleur2, &couleur3, &couleur4) != EOF) {
        toutes_les_combi = enfiler(toutes_les_combi, couleur1, couleur2, couleur3, couleur4);
    }

    // Fermeture des fichiers après la copie des données
    fclose(fichier2);
    fclose(fichier);

    // Réouverture du fichier provisoire pour la réécriture dans le fichier final
    fichier2 = fopen(nom_temp2, "r");
    FILE *fichier_final = fopen(nom_temp, "w");

    if (fichier2 == NULL || fichier_final == NULL) {
        printf("Erreur lors de l'ouverture des fichiers pour la réécriture.\n");
        exit(-1);
    }

    // Copier le contenu du fichier provisoire dans le fichier final
    char c;
    while ((c = fgetc(fichier2)) != EOF) {
        fputc(c, fichier_final);
    }

    // Fermeture des fichiers après la réécriture
    fclose(fichier_final);
    fclose(fichier2);

    // Suppression du fichier provisoire après usage
    if (remove(nom_temp2) != 0) {
        perror("Erreur lors de la suppression du fichier provisoire\n");
        exit(-1);
    }

    // Retourner la file mise à jour
    return toutes_les_combi;
}

