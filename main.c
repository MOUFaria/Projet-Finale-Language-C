#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char secretWord[50];
    char showWord[50];
    char usedLetters[26];
    int nbUsed;
    int maxErr;
    int madeErr;
    int nbHint;
    char category[30];
    int difficulty;
} Game;

void initGame(Game *g, char *word, char *cat, int diff) {
    strcpy(g->secretWord, word);
    strcpy(g->category, cat);
    g->madeErr = 0;
    g->nbUsed = 0;
    g->difficulty = diff;

    if (diff == 1) { g->maxErr = 10; g->nbHint = 3; } 
    else { g->maxErr = 6; g->nbHint = 1; }           

    int len = strlen(word);
    for (int i = 0; i < len; i++) g->showWord[i] = '_';
    g->showWord[len] = '\0';
}

int checkLetter(Game *g, char letter) {
    int trouve = 0;
    for (int i = 0; i < strlen(g->secretWord); i++) {
        if (g->secretWord[i] == letter) {
            g->showWord[i] = letter;
            trouve = 1;
        }
    }
    if (!trouve) g->madeErr++;
    return trouve;
}

int loadWord(Game *g, int diff) {
    FILE* file = fopen("mots.txt", "r");
    if (file == NULL) return 0;

    char line[100];
    char pickedWord[50] = "";
    char pickedCat[30] = "";
    int count = 0;

    srand(time(NULL));

    while (fgets(line, sizeof(line), file)) {
        char cat[30], word[50];
        sscanf(line, "%[^:]:%s", cat, word);

        int len = strlen(word);
        int valid = 0;

        if (diff == 1 && len >= 4 && len <= 6) valid = 1;
        else if (diff == 2 && len > 6 && len <= 8) valid = 1;
        else if (diff == 3 && len > 8) valid = 1;

        if (valid) {
            count++;
            if (rand() % count == 0) {
                strcpy(pickedWord, word);
                strcpy(pickedCat, cat);
            }
        }
    }

    fclose(file);

    if (count > 0) {
        strcpy(g->secretWord, pickedWord);
        strcpy(g->category, pickedCat);
        return 1;
    }
    return 0;
}


int main() {
    Game myGame;
    int diffChoice;
    char letter;

    printf("=== PROTOTYPE JEU DU PENDU ===\n");
    printf("1: Facile (4-6 lettres)\n2: Moyen (6-8 lettres)\n3: Difficile (8+ lettres)\n");
    printf("Votre choix : ");
    scanf("%d", &diffChoice);

    if (!loadWord(&myGame, diffChoice)) {
        printf("Erreur : Fichier 'mots.txt' absent ou aucun mot trouve.\n");
        return 1;
    }

    initGame(&myGame, myGame.secretWord, myGame.category, diffChoice);

    while (myGame.madeErr < myGame.maxErr && strcmp(myGame.showWord, myGame.secretWord) != 0) {
        printf("\n------------------------------");
        printf("\nCategorie : %s", myGame.category);
        printf("\nMot : %s", myGame.showWord);
        printf("\nErreurs : %d/%d", myGame.madeErr, myGame.maxErr);
        
        printf("\nEntrez une lettre : ");
        scanf(" %c", &letter);

        if (checkLetter(&myGame, letter)) {
            printf("-> Bien joue !\n");
        } else {
            printf("-> Rate !\n");
        }
    }

    if (strcmp(myGame.showWord, myGame.secretWord) == 0)
        printf("\nBRAVO ! Le mot etait : %s\n", myGame.secretWord);
    else
        printf("\nPENDU ! Le mot etait : %s\n", myGame.secretWord);

    return 0;
}