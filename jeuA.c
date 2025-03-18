#include "header.h"
#include "affichagetxt.h"
#include "jeuA.h"
#include "jeuB.h"
#include "reprendre_partie.h"
#include "revisualiser_partie.h"
#include "sauvegarde.h"
#include "stat.h"

// Couleurs possibles
const char COULEURS[]={'R','B','V','J','P','W'};

// Génère une combinaison secrète aléatoire
void generer_code(char code[]){
    for (int i = 0; i < taille_code; i++){
        // Choisir une couleur au hasard parmi les 6 disponibles
        code[i] = COULEURS[rand()%6];
    }
}

// Récupère la proposition du joueur et calcule le temps qu'il met pour entrer sa réponse
void obtenir_proposition_du_joueur(char proposition[],float * tmps)
{
    clock_t debut = clock();        // Enregistre l'heure de départ pour calculer le temps
    printf("Entrez votre proposition, il s'agira d'une suite de %d couleurs (" R "R" RESET ","B "B" RESET ","
           V "V" RESET "," J "J" RESET "," P "P" RESET "," W "W" RESET ") (Q pour quitter/M pour menu) : ", taille_code);
    fgets(proposition,taille_code+100,stdin);       // Lecture de la proposition du joueur
    char* new_line = "\n";                          // Retire le saut de ligne à la fin de la chaîne
    proposition[strcspn(proposition,new_line)] = '\0';
    // Vérifie la validité de la proposition et mesure le temps
    testchar(proposition,tmps);
    clock_t fin = clock();                          // Enregistre l'heure de fin pour calculer le temps passé
    *tmps = ((float)(fin-debut))/CLOCKS_PER_SEC;    // Calcule le temps écoulé en secondes
}

// Evalue la proposition du joueur
void evaluer_proposition(const char code[], const char proposition[], int *bonne_place, int *mauvaise_place) {
    *bonne_place = 0;
    *mauvaise_place = 0;
    int verif_combinaison[taille_code] = {0};   // Tableau pour suivre les couleurs déjà vérifiées de la combinaison
    int verif_proposition[taille_code] = {0};   // Tableau pour suivre les couleurs déjà vérifiées de la proposition



    // Vérification des positions bien placées
    for (int i = 0; i < taille_code; i++) {
        if (proposition[i] == code[i]) {
            (*bonne_place)++;
            verif_combinaison[i]=1;
            verif_proposition[i]=1;
            }
        }

    // Vérification des couleurs présentes mais mal placées
    for (int i = 0; i < taille_code; i++){
        if (verif_proposition[i]==0) {
            for (int j = 0; j < taille_code; j++){
                if ((verif_combinaison[j]==0) && (proposition[i]==code[j])) {
                    (*mauvaise_place)++;
                    verif_combinaison[j] =1;    // Marque cette couleur comme déjà utilisée
                    break;
                }
            }
        }
    }
}

// Vérifie que la proposition du joueur est conforme (couleurs valides et longueur correcte)
void testchar(char proposition[],float * tmps)
{
    // Si le joueur souhaite quitter ou revenir au menu
    if (proposition[0] == 'Q' || proposition[0] == 'M')
    {
        return;
    }
    // Vérifie si la longueur de la proposition est correcte
    if (strlen(proposition)!=4)
    {
        printf("Votre proposition n'est pas conforme ! Veuillez recommencer !\n");
        obtenir_proposition_du_joueur(proposition,tmps);    // Redemande une proposition
        return;
    }
    // Vérifie que chaque caractère de la proposition est une couleur valide
    for (int i=0; i<strlen(proposition);i++)
    {
        if (proposition[i]!=('R') && proposition[i]!=('B') && proposition[i]!=('V') && proposition[i]!=('J') &&
            proposition[i]!=('P') && proposition[i]!=('W'))
        {
            printf("Votre proposition n'est pas conforme ! Veuillez recommencer !\n");
            obtenir_proposition_du_joueur(proposition,tmps);    // Redemande une proposition
        }
    }
}

// Affiche le menu de sélection du niveau de difficulté
void choix_niveau_joueurA()
{
    printf("\nPour commencer, veuillez choisir votre niveau de difficulte !");
    printf("\n1: Facile (30 essais)\n2: Intermediaire (20 essais)\n3: Difficile (10 essais)");
    printf("\n4: Personalise (a vous de choisir votre nombre d'essais !)\n5: Quitter\n6: Retour au menu principal");
    separateur();   // Séparateur pour afficher un espace
    printf("Votre choix :\n");
    int choix; char choix_prov; int compteur = 0;
    scanf("%c", &choix_prov); while (getchar() != '\n'){compteur++;};   // Nettoie le buffer
    choix = testchoix4(choix_prov, compteur);                           // Vérifie le choix du joueur
    switch(choix)
    {
        case 1 :
            essais_max = 30;
            jouer_A();
            break;
        case 2 :
            essais_max = 20;
            jouer_A();
            break;
        case 3 :
            essais_max = 10;
            jouer_A();
            break;
        case 4 :
            {
                int essais;
                separateur();
                printf("\nNombre d'essais :\n");
                scanf("%d",&essais);    // Demande à l'utilisateur de choisir le nombre d'essais
                char new_line2;
                scanf("%c",&new_line2);
                essais_max = essais;
                jouer_A();
                break;
            }
        case 5 : exit(-1);
        case 6 : affichermenu();
        default :
            {
                separateur();
                printf("Vous n'avez pas choisi l'une des propositions du menu, veillez recommencer!\n");
                choix_niveau_joueurA();
                break;
            }
    }
}

// Calcule la moyenne des temps du joueur
float moyenne_temps(float temps_jA, int nbessais, float moyenne_temps)
{
        float result = ((float)(nbessais-1)*moyenne_temps + temps_jA)/nbessais;
        return result;  // Renvoie la moyenne mise à jour
}

// Fonction principale de jeu pour le joueur A
void jouer_A(){
    char code[taille_code], proposition[taille_code+100];
    int essais = 0, bonne_place = 0, mauvaise_place = 0;

    printf("Donne un nom a ta partie : ");
    char nom_partie[100];
    fgets(nom_partie,100,stdin);
    char* new_line = "\n";
    nom_partie[strcspn(nom_partie,new_line)] = '\0';    // Retire le saut de ligne
    test_nompartie(nom_partie);

    creer_ou_remplacer_fichier(nom_partie);
    ajouter_type_joueur(nom_partie,'A');        // Enregistre le type de joueur

    // Code aléatoire
    srand(time(NULL));                          // Initialise le générateur de nombres aléatoires
    generer_code(code);                         // Génère la combinaison secrète
    ajouter_combi_secrete(nom_partie, code);    // Ajoute la combinaison secrète au fichier
    printf("\n");
    // Pour voir le code
    /*for (int i=0; i<4;i++)
    {
        printf("%c ",code[i]);
    }
    printf("\n");*/
    printf("Devinez la combinaison secrete.\n");

    float moytemps;
    float temps_joueurA;

    // Boucle principale
    while (essais < essais_max) {
            obtenir_proposition_du_joueur(proposition,&temps_joueurA);
        if (proposition[0]=='Q')
        {
            sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,-1);  // Sauvegarde la partie avant de quitter
            demande_sauvegarde(nom_partie);                                 // Demande si le joueur souhaite sauvegarder
            return(exit(-1));                                               // Quitte le jeu
        }
        else if (proposition[0]=='M')
        {
            sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,-1);  // Sauvegarde la partie avant de quitter
            demande_sauvegarde(nom_partie);
            affichermenu(); // Affiche le menu principal
        }
            evaluer_proposition(code, proposition, &bonne_place, &mauvaise_place);  // Évalue la proposition
            essais++;                                                               // Incrémente le nombre d'essais
        if (bonne_place == taille_code) {                                           // Vérifie tout est correct
            printf("BRAVO ! Vous avez gagne en %d essais.", essais);
            ajouter_essai(nom_partie, essais, proposition, bonne_place, mauvaise_place);
            int victoire = 1;
            moytemps = moyenne_temps(temps_joueurA,essais,moytemps);
            mettreAJourStatistiques(pseudo,victoire);
            ajouterResultatPartie('A',pseudo,nom_partie,moytemps,essais,victoire);
            sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,victoire);    // Sauvegarde la partie avant de quitter
            demande_sauvegarde(nom_partie);
            separateur();
            affichermenu(); // Retourne au menu principal
        }
        else {
            printf("Resultat : " R "%d bonne place" RESET ", %d mauvaise place\n", bonne_place, mauvaise_place);
            moytemps = moyenne_temps(temps_joueurA,essais,moytemps);
            ajouter_essai(nom_partie, essais, proposition, bonne_place, mauvaise_place);
        }
    }

    // Si le joueur n'a pas trouvé la combinaison après le nombre maximum d'essais
    printf("\nC'est perdu ! La combinaison secrete etait : ");
    for (int i = 0; i < taille_code; i++) {
        printf("%c ", code[i]);
    }
    printf("\n");
    printf("Peut-etre la prochaine fois !\n");
    int victoire = 0;
    mettreAJourStatistiques(pseudo,victoire);
    ajouterResultatPartie('A',pseudo,nom_partie,moytemps,essais,victoire);
    sauvegarderetat(nom_partie,'A',moytemps,essais,essais_max,victoire);    // Sauvegarde la partie avant de quitter
    demande_sauvegarde(nom_partie);
    separateur();
    affichermenu(); // Retourne au menu principal
}

// Vérifie et valide le choix du joueur pour le niveau de difficulté
int testchoix4(char ch,int compteur)
{
    if (compteur!=0)
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1; compteur = 0;
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};
        int chprov = testchoix4(ch1,compteur);  // Recursion pour valider le choix
        return chprov;
    }
    else if (ch<=54 && ch>=49)      // Vérifie que le choix est un chiffre entre 1 et 6
    {
        switch (ch){
            case 49 : {return 1;}
            case 50 : {return 2;}
            case 51 : {return 3;}
            case 52 : {return 4;}
            case 53 : {return 5;}
            case 54 : {return 6;}
        };
    }
    else
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1;
        compteur = 0;
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};
        printf("%d",compteur);
        char chprov = testchoix4(ch1,compteur); // Redemande un choix valide
        return chprov;
    }
    return 5;
}
