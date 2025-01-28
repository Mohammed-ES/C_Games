#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>

#define BASE_DIR "C:\\Users\\LENOVO\\Desktop\\CodePulse\\Project\\Players\\"
#define MAX_PATH 256

typedef struct {
    char nom[50];
    char sexe[10];
    int age;
    char idJoueur[20];
    int score;
    char remarques[200];
    char dateHeure[30];
} Joueur;

// Prototypes des fonctions
int quiz(int niveau, int langue);
void afficherMessageSelonScore(Joueur *joueur, int totalQuestions, int langue);
void sauvegarderInformationsJoueur(Joueur *joueur, int totalQuestions, int langue);
int poserQuestion(const char *question, const char *options[], int bonneReponse, int nombreOptions, int langue);

// Fonction pour créer le répertoire
void creerRepertoireSiNecessaire() {
    #ifdef _WIN32
        _mkdir(BASE_DIR);
    #else
        mkdir(BASE_DIR, 0777);
    #endif
}

// Fonction pour générer un ID unique
void genererIDJoueur(char *id) {
    time_t t;
    srand((unsigned)time(&t));
    const char *lettres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    sprintf(id, "%c%c%d%d%d", 
            lettres[rand() % 26], 
            lettres[rand() % 26], 
            rand() % 10, 
            rand() % 10, 
            rand() % 10);
}

// Fonction pour obtenir la date et l'heure
void obtenirDateHeure(char *dateHeure) {
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);
    strftime(dateHeure, 30, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Fonction pour poser une question
int poserQuestion(const char *question, const char *options[], int bonneReponse, int nombreOptions, int langue) {
    printf("\n%s\n", question);
    for (int i = 0; i < nombreOptions; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }
    int reponse;
    if (langue == 1) printf("Votre réponse : ");
    else printf("Your answer: ");
    scanf("%d", &reponse);
    return reponse == bonneReponse;
}

// Fonction pour le quiz
int quiz(int niveau, int langue) {
    int score = 0;
    const char *questions[10];
    const char *options[10][4];
    int reponses[10];

    if (langue == 1) { // Français
        if (niveau == 1) {
            printf("\n=== Niveau Facile ===\n");
            questions[0] = "Quelle est la capitale de la France ?";
            options[0][0] = "Paris"; options[0][1] = "Londres"; options[0][2] = "Berlin"; options[0][3] = "Rome";
            reponses[0] = 1;

            questions[1] = "Combien font 5 + 3 ?";
            options[1][0] = "7"; options[1][1] = "8"; options[1][2] = "9"; options[1][3] = "10";
            reponses[1] = 2;

            questions[2] = "Quelle est la couleur du ciel ?";
            options[2][0] = "Rouge"; options[2][1] = "Vert"; options[2][2] = "Bleu"; options[2][3] = "Jaune";
            reponses[2] = 3;
        } else if (niveau == 2) {
            printf("\n=== Niveau Moyen ===\n");
            questions[0] = "Quelle est la capitale de l'Allemagne ?";
            options[0][0] = "Paris"; options[0][1] = "Berlin"; options[0][2] = "Madrid"; options[0][3] = "Rome";
            reponses[0] = 2;
            // Ajoutez d'autres questions...
        } else {
            printf("\n=== Niveau Difficile ===\n");
            questions[0] = "Quelle est la capitale du Japon ?";
            options[0][0] = "Seoul"; options[0][1] = "Beijing"; options[0][2] = "Tokyo"; options[0][3] = "Bangkok";
            reponses[0] = 3;
            // Ajoutez d'autres questions...
        }
    } else { // English
        if (niveau == 1) {
            printf("\n=== Easy Level ===\n");
            questions[0] = "What is the capital of France?";
            options[0][0] = "Paris"; options[0][1] = "London"; options[0][2] = "Berlin"; options[0][3] = "Rome";
            reponses[0] = 1;

            questions[1] = "What is 5 + 3?";
            options[1][0] = "7"; options[1][1] = "8"; options[1][2] = "9"; options[1][3] = "10";
            reponses[1] = 2;

            questions[2] = "What color is the sky?";
            options[2][0] = "Red"; options[2][1] = "Green"; options[2][2] = "Blue"; options[2][3] = "Yellow";
            reponses[2] = 3;
        } else if (niveau == 2) {
            printf("\n=== Medium Level ===\n");
            questions[0] = "What is the capital of Germany?";
            options[0][0] = "Paris"; options[0][1] = "Berlin"; options[0][2] = "Madrid"; options[0][3] = "Rome";
            reponses[0] = 2;
            // Ajoutez d'autres questions...
        } else {
            printf("\n=== Hard Level ===\n");
            questions[0] = "What is the capital of Japan?";
            options[0][0] = "Seoul"; options[0][1] = "Beijing"; options[0][2] = "Tokyo"; options[0][3] = "Bangkok";
            reponses[0] = 3;
            // Ajoutez d'autres questions...
        }
    }

    int questionsParNiveau = 3; // Nombre de questions par niveau
    for (int i = 0; i < questionsParNiveau; i++) {
        score += poserQuestion(questions[i], options[i], reponses[i], 4, langue);
    }
    return score;
}

// Fonction pour afficher le message selon le score
void afficherMessageSelonScore(Joueur *joueur, int totalQuestions, int langue) {
    int pourcentage = (joueur->score * 100) / totalQuestions;

    if (langue == 1) { // Français
        if (pourcentage >= 75) {
            printf("\nExcellent travail, %s ! Votre score est de %d%%\n", joueur->nom, pourcentage);
            strcpy(joueur->remarques, "Excellent score !");
        } else if (pourcentage >= 50) {
            printf("\nBon travail, %s ! Votre score est de %d%%\n", joueur->nom, pourcentage);
            strcpy(joueur->remarques, "Bon score, continuez ainsi !");
        } else {
            printf("\nContinuez à pratiquer, %s ! Votre score est de %d%%\n", joueur->nom, pourcentage);
            strcpy(joueur->remarques, "Plus de pratique nécessaire");
        }
    } else { // English
        if (pourcentage >= 75) {
            printf("\nExcellent work, %s! Your score is %d%%\n", joueur->nom, pourcentage);
            strcpy(joueur->remarques, "Excellent score!");
        } else if (pourcentage >= 50) {
            printf("\nGood work, %s! Your score is %d%%\n", joueur->nom, pourcentage);
            strcpy(joueur->remarques, "Good score, keep it up!");
        } else {
            printf("\nKeep practicing, %s! Your score is %d%%\n", joueur->nom, pourcentage);
            strcpy(joueur->remarques, "More practice needed");
        }
    }
}

// Fonction pour sauvegarder les informations
void sauvegarderInformationsJoueur(Joueur *joueur, int totalQuestions, int langue) {
    char cheminFichier[MAX_PATH];
    char dateHeure[30];
    
    snprintf(cheminFichier, MAX_PATH, "%s%s.md", BASE_DIR, joueur->idJoueur);
    obtenirDateHeure(dateHeure);
    
    FILE *fichier = fopen(cheminFichier, "a");
    if (!fichier) {
        if (langue == 1) printf("Erreur: Impossible de sauvegarder les informations.\n");
        else printf("Error: Unable to save information.\n");
        return;
    }

    fprintf(fichier, "## Session du %s\n", dateHeure);
    fprintf(fichier, "- Nom : %s\n", joueur->nom);
    fprintf(fichier, "- Sexe : %s\n", joueur->sexe);
    fprintf(fichier, "- Âge : %d\n", joueur->age);
    fprintf(fichier, "- ID : %s\n", joueur->idJoueur);
    fprintf(fichier, "- Score : %d/%d\n", joueur->score, totalQuestions);
    fprintf(fichier, "- Remarques : %s\n\n", joueur->remarques);
    
    fclose(fichier);
}

// Fonction principale
int main() {
    Joueur joueur;
    int niveau = 1;
    int totalQuestions = 3; // Nombre de questions par niveau
    int langue;
    int continuer = 1;
    
    creerRepertoireSiNecessaire();

    printf("Choose your language / Choisissez votre langue:\n");
    printf("1. Français\n2. English\n");
    printf("Choice/Choix: ");
    scanf("%d", &langue);

    if (langue == 1) {
        printf("\n=== Bienvenue au Quiz ===\n");
        printf("Avez-vous un ID joueur ? (1: Oui, 0: Non) : ");
    } else {
        printf("\n=== Welcome to the Quiz ===\n");
        printf("Do you have a player ID? (1: Yes, 0: No): ");
    }

    int aUnID;
    scanf("%d", &aUnID);

    if (aUnID) {
        if (langue == 1) printf("Entrez votre ID : ");
        else printf("Enter your ID: ");
        scanf("%s", joueur.idJoueur);
    } else {
        if (langue == 1) {
            printf("Entrez votre nom : ");
            scanf("%s", joueur.nom);
            printf("Entrez votre sexe (H/F) : ");
            scanf("%s", joueur.sexe);
            printf("Entrez votre âge : ");
            scanf("%d", &joueur.age);
        } else {
            printf("Enter your name: ");
            scanf("%s", joueur.nom);
            printf("Enter your gender (M/F): ");
            scanf("%s", joueur.sexe);
            printf("Enter your age: ");
            scanf("%d", &joueur.age);
        }
        genererIDJoueur(joueur.idJoueur);
        if (langue == 1) printf("Votre ID : %s\n", joueur.idJoueur);
        else printf("Your ID: %s\n", joueur.idJoueur);
    }

    while (continuer && niveau <= 3) {
        if (langue == 1) {
            printf("\nNiveau %d\n", niveau);
        } else {
            printf("\nLevel %d\n", niveau);
        }

        joueur.score = quiz(niveau, langue);
        afficherMessageSelonScore(&joueur, totalQuestions, langue);
        sauvegarderInformationsJoueur(&joueur, totalQuestions, langue);

        if (niveau < 3) {
            if (langue == 1) {
                printf("\nVoulez-vous continuer au niveau suivant ? (1: Oui, 0: Non) : ");
            } else {
                printf("\nDo you want to continue to the next level? (1: Yes, 0: No): ");
            }
            scanf("%d", &continuer);
            if (continuer) niveau++;
        } else {
            continuer = 0;
        }
    }

    if (langue == 1) {
        printf("\nMerci d'avoir joué, %s ! À bientôt !\n", joueur.nom);
    } else {
        printf("\nThank you for playing, %s! See you soon!\n", joueur.nom);
    }
    
    return 0;
}