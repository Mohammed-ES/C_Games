#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int choixUtilisateur, choixOrdinateur;
    srand(time(0));

    printf("Bienvenue à Pierre-Papier-Cisseaux !\n");
    printf("Choisissez : 1. Pierre, 2. Papier, 3. Ciseaux\n");
    printf("Votre choix : ");
    scanf("%d", &choixUtilisateur);

    choixOrdinateur = rand() % 3 + 1; // Génère un choix aléatoire

    printf("Ordinateur a choisi : %d\n", choixOrdinateur);

    if (choixUtilisateur == choixOrdinateur)
        printf("Égalité !\n");
    else if ((choixUtilisateur == 1 && choixOrdinateur == 3) || 
             (choixUtilisateur == 2 && choixOrdinateur == 1) || 
             (choixUtilisateur == 3 && choixOrdinateur == 2))
        printf("Vous gagnez !\n");
    else
        printf("Vous perdez !\n");

    return 0;
}