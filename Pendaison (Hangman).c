#include <stdio.h>
#include <string.h>

int main() {
    char mot[20] = "programmation";
    char devine[20] = "______________";
    int essais = 10;
    char lettre;
    int trouve = 0;

    printf("Bienvenue au jeu du Pendu !\n");

    while (essais > 0 && trouve < strlen(mot)) {
        printf("Mot actuel : %s\n", devine);
        printf("Entrez une lettre : ");
        scanf(" %c", &lettre);

        int correct = 0;
        for (int i = 0; i < strlen(mot); i++) {
            if (mot[i] == lettre && devine[i] == '_') {
                devine[i] = lettre;
                trouve++;
                correct = 1;
            }
        }

        if (!correct) {
            essais--;
            printf("Faux ! Il vous reste %d essais.\n", essais);
        }
    }

    if (trouve == strlen(mot))
        printf("Bravo ! Vous avez trouvé le mot : %s\n", mot);
    else
        printf("Dommage, vous avez perdu ! Le mot était : %s\n", mot);

    return 0;
}
