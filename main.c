#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
