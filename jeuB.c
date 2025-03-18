#include "header.h"
#include "affichagetxt.h"
#include "jeuA.h"
#include "jeuB.h"
#include "reprendre_partie.h"
#include "revisualiser_partie.h"
#include "sauvegarde.h"
#include "stat.h"

// Tableau des couleurs possibles (R, B, V, J, P, W)
char letters[] = {'R','B','V','J','P','W'};

// Fonction basique pour l'utilisation de File
File * creerFile()
{
    File * f = malloc(sizeof(File));    // Allocation dynamique d'une nouvelle file
    f -> tete = NULL;                   // Initialisation de la t�te de la file � NULL
    f -> queue = NULL;                  // Initialisation de la queue de la file � NULL
    return f;
}

// Fonction pour ajouter un �l�ment � la fin de la file
File * enfiler(File * f, int w,int x,int y,int z)
{
    Element * p = malloc(sizeof(Element));// Allocation d'un nouvel �l�ment
    p -> color_1 = w;                     // Assignation de la couleur 1
    p -> color_2 = x;                     // Assignation de la couleur 2
    p -> color_3 = y;                     // Assignation de la couleur 3
    p -> color_4 = z;                     // Assignation de la couleur 4
    p -> suivant = NULL;                  // L'�l�ment suivant est NULL car c'est le dernier �l�ment

    if(f -> tete == NULL)                 // Si la file est vide
    {
        f -> tete = p;      // L'�l�ment devient la t�te de la file
        f -> queue = p;     // L'�l�ment devient �galement la queue de la file
    }
    else
    {
        f -> queue -> suivant = p;  // L'�l�ment est ajout� � la fin de la file
        f -> queue = p;             // L'�l�ment devient la nouvelle queue de la file
    }
    return f;
}

// Fonction pour retirer un �l�ment du d�but de la file
File * defiler(File * f,int * coul1,int * coul2,int * coul3, int * coul4)
{
    if(f -> tete == NULL)
    {
        printf("File Vide");    // Si la file est vide, afficher un message
        return f;               // Retourner la file inchang�e
    }
    Element * p = f -> tete;            // Pointer l'�l�ment � la t�te de la file
    f -> tete = f -> tete -> suivant;   // Avancer la t�te de la file
    *coul1 = p -> color_1;              // R�cup�rer la couleur 1 de l'�l�ment
    *coul2 = p -> color_2;              // R�cup�rer la couleur 2
    *coul3 = p -> color_3;              // R�cup�rer la couleur 3
    *coul4 = p -> color_4;              // R�cup�rer la couleur 4

    if(f -> tete == NULL)               // Si la file est maintenant vide
    {
        f -> queue = NULL;              // La queue est �galement NULL
    }
    free(p);
    return f;
}

// Fonction pour afficher le contenu de la file
void afficherFile(File * f)
{
	Element * p = f->tete;  // Pointer le d�but de la file
	printf("\n");
	while (p!=NULL)         // Tant que la file n'est pas vide
	{
		printf("%d %d %d %d --> ", p->color_1, p->color_2, p->color_3, p->color_4); // Afficher les couleurs de l'�l�ment
		p=p->suivant;           // Passer � l'�l�ment suivant
	}
}

// Fonction pour g�n�rer toutes les combinaisons possibles de couleurs et les ajouter � la file
File * generer_file_combinaisons()
{
    File * allcombin = creerFile();                         // Cr�er une nouvelle file
    for (int i=0;i<6;i++){                                  // Boucle sur toutes les couleurs possibles
        for (int j=0;j<6;j++){
            for (int k=0;k<6;k++){
                for (int l=0;l<6;l++){
                    allcombin = enfiler(allcombin,i,j,k,l); // Ajouter chaque combinaison � la file
                }
            }
        }
    }
    return allcombin;
}

// Fonction pour proposer une combinaison en d�filant la file et la transformant en tableau de caract�res
File * proposer_combinaison(File * f,char combi[])
{
    int couleur1; int couleur2; int couleur3; int couleur4;
    f = defiler(f,&couleur1,&couleur2,&couleur3,&couleur4); // Retirer un �l�ment de la file
    combi[0] = letters[couleur1]; combi[1] = letters[couleur2]; combi[2] = letters[couleur3]; combi[3] = letters[couleur4]; // Convertir l'indice en lettre correspondante
    printf_couleur(letters[couleur1]);// Afficher la couleur sous forme de texte
    printf_couleur(letters[couleur2]);
    printf_couleur(letters[couleur3]);
    printf_couleur(letters[couleur4]);
    return f;
}

// Fonction pour �liminer les combinaisons de la file qui ne sont pas compatibles avec les indices donn�s
File * eliminer_comb(File * f, char combi_depile[], int bonne_place, int mauvaise_place) {
    File * new_allcombin = creerFile();// Cr�er une nouvelle file pour stocker les combinaisons valides
    while (f->tete != NULL) {
        int couleur1, couleur2, couleur3, couleur4;
        f = defiler(f, &couleur1, &couleur2, &couleur3, &couleur4);                                         // Retirer un �l�ment de la file
        char a_comparer[5] = {letters[couleur1], letters[couleur2], letters[couleur3], letters[couleur4]};  // Conversion en tableau de caract�res
        int bonne_place_comp = 0, mauvaise_place_comp = 0;

        evaluer_proposition_joueurB(combi_depile, a_comparer, &bonne_place_comp, &mauvaise_place_comp);     // �valuer la proposition

        // Si les indices de bonne et mauvaise place correspondent, garder la combinaison dans la nouvelle file
        if (bonne_place_comp == bonne_place && mauvaise_place_comp == mauvaise_place) {
            new_allcombin = enfiler(new_allcombin, couleur1, couleur2, couleur3, couleur4);
        }
    }
    free(f);                // Lib�rer la m�moire de l'ancienne file
    return new_allcombin;   // Retourner la nouvelle file avec les combinaisons valides
}


// Le code du jeu, dans lequel le joueur (joueur B) propose des combinaisons et re�oit des indices
void jouerB() {
    File *toutes_les_combi = generer_file_combinaisons();   // G�n�rer toutes les combinaisons possibles
    int bonne_place = 0, mauvaise_place = 0;
    int essais = 0; float moytemps ; int compteur;

    // Initialisation du nom de la partie et autres param�tres
    printf("Donne un nom a ta partie : ");
    char nom_partieB[100];
    fgets(nom_partieB,100,stdin);
    char* new_line = "\n";
    nom_partieB[strcspn(nom_partieB,new_line)] = '\0';  // Supprimer le saut de ligne � la fin du nom
    test_nompartie(nom_partieB);                        // V�rifier la validit� du nom de la partie

    creer_ou_remplacer_fichier(nom_partieB);            // Cr�er ou remplacer le fichier de la partie
    ajouter_type_joueur(nom_partieB,'B');               // Ajouter l'indication que c'est un joueur B

    // Demander au joueur B de choisir une combinaison secr�te
    printf("Le jeu va commencer ! Choisi une combinaison  ");
    printf("\npour rappel : "R "Rouge = R " RESET "|" B " Bleu = B " RESET "|" V " Vert = V " RESET
            "|" J " Jaune = J " RESET "|" P " Rose = P " RESET "(comme Pink)|" W " Blanc = W " RESET "(Comme White)");
    printf("\nEcrit ta combinaison ici pour l avoir sous les yeux (elle ne sera pas utilisee) : ");
    char x[100];
    scanf("%s",x); while (getchar() != '\n');   // Lire la combinaison secr�te sans sauter de ligne
    ajouter_combi_secrete(nom_partieB,x);       // Ajouter la combinaison secr�te dans le fichier

    printf("\nMaintenant a mon tour de faire des propositions et a toi de me donner des indices !");
    printf("\nProposition de combinaison : ");
    char combi_defile[4]; char bonne_place_prov, mauvaise_place_prov;
    toutes_les_combi = proposer_combinaison(toutes_les_combi, combi_defile);    // Proposer une combinaison au joueur B

    // Boucle principale du jeu o� le joueur doit donner des indices
    while (bonne_place != 4 && toutes_les_combi->tete != NULL) {
        essais++;
        clock_t debut = clock();// D�marrer le chronom�tre

        printf("\nCombien de couleurs sont a la bonne place ?\nVotre reponse (Q pour quitter / M retour menu) : ");
        scanf("%c", &bonne_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};
        bonne_place = testchoix3(bonne_place_prov,compteur);    // V�rifier la r�ponse de l'utilisateur

        // Si l'utilisateur veut quitter ou revenir au menu
        if (bonne_place == -1){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);    // Sauvegarder l'�tat de la partie
            sauvegarderFile(toutes_les_combi,nom_partieB);              // Sauvegarder la file des combinaisons
            demande_sauvegarde(nom_partieB);                            // Demander si l'utilisateur veut sauvegarder
            return exit(-1);}

        else if (bonne_place == -2){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partieB);
            demande_sauvegarde(nom_partieB);
            affichermenu();}// Revenir au menu principal

        // Demander combien de couleurs sont � la mauvaise place
        printf("Combien de couleurs sont correctes mais a la mauvaise place ?\nVotre reponse (Q pour quitter / M pour menu) : ");
        scanf("%c", &mauvaise_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};
        mauvaise_place = testchoix3(mauvaise_place_prov,compteur);  // V�rifier la r�ponse de l'utilisateur

        // Si l'utilisateur veut quitter ou revenir au menu
        if (mauvaise_place == -1){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);    // Sauvegarder l'�tat de la partie
            sauvegarderFile(toutes_les_combi,nom_partieB);              // Sauvegarder la file des combinaisons
            demande_sauvegarde(nom_partieB);
            return exit(-1);}
        if (mauvaise_place == -2){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partieB);
            demande_sauvegarde(nom_partieB);
            affichermenu();}

        clock_t fin = clock();                              // Arr�ter le chronom�tre
        float temps = ((float)(fin-debut))/CLOCKS_PER_SEC;  // Calculer le temps �coul�
        moytemps = moyenne_temps(temps,essais,moytemps);    // Mettre � jour le temps moyen

        ajouter_essai(nom_partieB, essais, combi_defile, bonne_place, mauvaise_place);  // Ajouter l'essai dans l'historique

        // �liminer les combinaisons qui ne correspondent pas aux indices donn�s
        toutes_les_combi = eliminer_comb(toutes_les_combi, combi_defile, bonne_place, mauvaise_place);
        if (toutes_les_combi->tete != NULL) {
            printf("Proposition suivante : ");
            toutes_les_combi = proposer_combinaison(toutes_les_combi, combi_defile);    // Proposer une nouvelle combinaison
        }
    }

    // Si la solution est trouv�e
    if (bonne_place == 4) {
        printf("\nSolution trouvee !\n");
        int victoire = 0;
        mettreAJourStatistiques(pseudo,victoire);                                   // Mettre � jour les statistiques
        ajouterResultatPartie('B',pseudo,nom_partieB,moytemps,essais,victoire);     // Ajouter le r�sultat de la partie
        sauvegarderetat(nom_partieB,'B',moytemps,essais,0,victoire);                // Sauvegarder l'�tat de la partie
        demande_sauvegarde(nom_partieB);                                            // Demander si l'utilisateur veut sauvegarder
        separateur();                                                               // Afficher un s�parateur
        affichermenu();
    } else {
        essais++;                   // Incr�menter le nombre d'essais
        clock_t debut = clock();    // D�marrer le chronom�tre

        // Demander � nouveau les indices
        printf("\nCombien de couleurs sont a la bonne place ?\nVotre reponse (Q pour quitter / M retour menu) : ");
        scanf("%c", &bonne_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};
        bonne_place = testchoix3(bonne_place_prov,compteur);

        // V�rifier si l'utilisateur veut quitter ou revenir au menu
        if (bonne_place == -1){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partieB);
            demande_sauvegarde(nom_partieB);
            return exit(-1);}
        else if (bonne_place == -2){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partieB);
            demande_sauvegarde(nom_partieB);
            affichermenu();}

        // Demander � nouveau les indices pour les couleurs mal plac�es
        printf("Combien de couleurs sont correctes mais a la mauvaise place ?\nVotre reponse (Q pour quitter / M retour menu) : ");
        scanf("%c", &mauvaise_place_prov); compteur = 0; while (getchar() != '\n'){compteur++;};
        mauvaise_place = testchoix3(mauvaise_place_prov,compteur);

        // V�rifier si l'utilisateur veut quitter ou revenir au menu
        if (mauvaise_place == -1){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);
            sauvegarderFile(toutes_les_combi,nom_partieB);
            demande_sauvegarde(nom_partieB);
            return exit(-1);}
        else if (mauvaise_place == -2){
            toutes_les_combi = enfiler(toutes_les_combi,convert_char_int(combi_defile[0]),convert_char_int(combi_defile[1]),
                                       convert_char_int(combi_defile[2]),convert_char_int(combi_defile[3]));
            sauvegarderetat(nom_partieB,'B',moytemps,essais-1,0,-1);    // Sauvegarder l'�tat
            sauvegarderFile(toutes_les_combi,nom_partieB);              // Sauvegarder la file des combinaisons
            demande_sauvegarde(nom_partieB);
            affichermenu();}

        // Arr�ter le chronom�tre et calculer le temps
        clock_t fin = clock();
        float temps = ((float)(fin-debut))/CLOCKS_PER_SEC;
        moytemps = moyenne_temps(temps,essais,moytemps);

        // Ajouter l'essai dans l'historique
        ajouter_essai(nom_partieB, essais, combi_defile, bonne_place, mauvaise_place);

        // Si la solution a �t� trouv�e
        if(bonne_place == 4) {
        printf("\nSolution trouvee !\n");
        int victoire = 0;
        mettreAJourStatistiques(pseudo,victoire);
        ajouterResultatPartie('B',pseudo,nom_partieB,moytemps,essais,victoire);
        sauvegarderetat(nom_partieB,'B',moytemps,essais,0,victoire);
        demande_sauvegarde(nom_partieB);
        separateur();
        affichermenu();
        }
        // Sinon, afficher que la solution n'a pas �t� trouv�e
        else {
        printf("\nPerdu ! Aucune solution trouvee !\n");
        int victoire = 1;
        mettreAJourStatistiques(pseudo,victoire);
        ajouterResultatPartie('B',pseudo,nom_partieB,moytemps,essais,victoire);
        sauvegarderetat(nom_partieB,'A',moytemps,essais,0,victoire);
        demande_sauvegarde(nom_partieB);
        separateur();
        affichermenu();}
    }
}


// Fonction pour �valuer la proposition du joueur par rapport � la combinaison secr�te
void evaluer_proposition_joueurB(const char proposition[], const char comparaison[], int *bonne_place, int *mauvaise_place) {
    *bonne_place = 0;               // Initialisation du compteur de bonnes places
    *mauvaise_place = 0;            // Initialisation du compteur de mauvaises places
    int verif_combinaison[4] = {0}; // Tableau pour v�rifier les couleurs d�j� compt�es dans la combinaison
    int verif_proposition[4] = {0}; // Tableau pour v�rifier les couleurs d�j� compt�es dans la proposition

    // V�rification des positions bien plac�es
    for (int i = 0; i < 4; i++) {
        if (comparaison[i] == proposition[i]) { // Si la couleur est bien plac�e
            (*bonne_place)++;                   // Incr�menter le compteur de bonnes places
            verif_combinaison[i] = 1;           // Marquer la couleur comme trouv�e dans la combinaison
            verif_proposition[i] = 1;           // Marquer la couleur comme trouv�e dans la proposition
        }
    }

    // V�rification des couleurs pr�sentes mais mal plac�es
    for (int i = 0; i < 4; i++) {
        if (verif_proposition[i] == 0) {                                                // Si la couleur n'a pas �t� compt�e dans les bonnes places
            for (int j = 0; j < 4; j++) {
                if (verif_combinaison[j] == 0 && comparaison[i] == proposition[j]) {    // Si la couleur est pr�sente mais mal plac�e
                    (*mauvaise_place)++;                                                // Incr�menter le compteur de mauvaises places
                    verif_combinaison[j] = 1;                                           // Marquer comme trouv�
                    break;
                }
            }
        }
    }
}

// Fonction pour convertir un caract�re repr�sentant une couleur en un entier correspondant
int convert_char_int(char lettre)
{
    if (lettre=='R') {return 0;}
    else if (lettre=='B') {return 1;}
    else if (lettre=='V') {return 2;}
    else if (lettre=='J') {return 3;}
    else if (lettre=='P') {return 4;}
    else {return 5;}
}

// Fonction pour tester un choix fait par l'utilisateur (v�rifie la validit� de l'entr�e)
int testchoix3(char ch,int compteur)
{
    if (compteur!=0)                                                // Si le compteur n'est pas z�ro, l'entr�e n'est pas valide
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1; compteur = 0;
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};
        int chprov = testchoix3(ch1,compteur);                      // Appeler r�cursivement la fonction pour r�cup�rer un choix valide
        return chprov;                                              // Retourner le choix valide
    }
    else if (ch=='Q'){return -1;}       // Si l'utilisateur entre 'Q', quitter
    else if (ch=='M'){return -2;}       // Si l'utilisateur entre 'M', retour menu
    else if (ch<=52 && ch>=48)          // V�rifier si le caract�re est un chiffre entre '0' et '4'
    {
        switch (ch){                    // Retourner la valeur correspondant � la couleur
            case 48 : {return 0;}
            case 49 : {return 1;}
            case 50 : {return 2;}
            case 51 : {return 3;}
            case 52 : {return 4;}
        };
    }
    else    // Si le choix n'est pas valide
    {
        printf("Choix non conforme ! Veuillez recommencer !\n");
        char ch1;
        compteur = 0;
        scanf("%c", &ch1); while (getchar() != '\n'){compteur++;};
        printf("%d",compteur);
        char chprov = testchoix3(ch1,compteur); // Appeler r�cursivement la fonction pour obtenir un choix valide
        return chprov;                          // Retourner le choix valide
    }
    return 5;       // Retourner une valeur par d�faut si aucune des conditions n'est remplie
}
