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