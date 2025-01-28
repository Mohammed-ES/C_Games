#include <stdio.h>

char grille[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void afficherGrille() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", grille[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

int verifierVictoire() {
    for (int i = 0; i < 3; i++) {
        if (grille[i][0] == grille[i][1] && grille[i][1] == grille[i][2] && grille[i][0] != ' ')
            return 1;
        if (grille[0][i] == grille[1][i] && grille[1][i] == grille[2][i] && grille[0][i] != ' ')
            return 1;
    }
    if (grille[0][0] == grille[1][1] && grille[1][1] == grille[2][2] && grille[0][0] != ' ')
        return 1;
    if (grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0] && grille[0][2] != ' ')
        return 1;
    return 0;
}

int main() {
    int joueur = 1, ligne, colonne, coups = 0;

    printf("Bienvenue au jeu du Morpion !\n");
    while (1) {
        afficherGrille();
        printf("Joueur %d, entrez la ligne et la colonne (1-3) : ", joueur);
        scanf("%d%d", &ligne, &colonne);

        if (grille[ligne - 1][colonne - 1] == ' ') {
            grille[ligne - 1][colonne - 1] = (joueur == 1) ? 'X' : 'O';
            coups++;
            if (verifierVictoire()) {
                afficherGrille();
                printf("Joueur %d gagne !\n", joueur);
                break;
            }
            if (coups == 9) {
                afficherGrille();
                printf("Match nul !\n");
                break;
            }
            joueur = (joueur == 1) ? 2 : 1;
        } else {
            printf("Case déjà occupée, réessayez.\n");
        }
    }

    return 0;
}
