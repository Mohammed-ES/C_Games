#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int nombreMystere, nombreEntre, essais = 0;
    srand(time(NULL));  // Initialisation pour générer un nombre aléatoire
    nombreMystere = rand() % 100 + 1;  // Nombre aléatoire entre 1 et 100

    printf("Bienvenue au jeu 'Devine le Nombre' !\n");
    do {
        printf("Entrez un nombre entre 1 et 100 : ");
        scanf("%d", &nombreEntre);
        essais++;

        if (nombreEntre < nombreMystere)
            printf("C'est plus grand !\n");
        else if (nombreEntre > nombreMystere)
            printf("C'est plus petit !\n");
        else
            printf("Bravo ! Vous avez trouvé en %d essais.\n", essais);
    } while (nombreEntre != nombreMystere);

    return 0;
}
