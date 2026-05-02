// Author: Abby Voss
// date: 05-01-26
// Reason: project 10

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ROWS 6
#define COLS 6   // 5 letters + '\0'

void printLine(){
    int i;
    	for (i = 0; i < 30; i++)
        	printf("=");
    	printf("\n");
}

int existsInWord(char letter, char answer[]){
    int i;
    for (i = 0; i < 5; i++){
        if (letter == answer[i])
            return 1;
    }
    return 0;
}

void printBoard(char guesses[ROWS][COLS], int count, char answer[]){
    int i, j;

    for (i = 0; i < count; i++){
        for (j = 0; j < 5; j++){
            char letter = guesses[i][j];

            if (letter == answer[j])
                printf("%c", toupper(letter));   
            else if (existsInWord(letter, answer))
                printf("%c", toupper(letter));   
            else
                printf("%c", tolower(letter));   
        }

        printf("\n");

        for (j = 0; j < 5; j++){
            if (guesses[i][j] == answer[j])
                printf("^");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int main(){
    char answer[COLS];
    char guesses[ROWS][COLS];
    int guessCount = 0;
    int won = 0;

    FILE *fp = fopen("mystery.txt", "r");

    if (fp == NULL){
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(fp, "%s", answer);
    fclose(fp);

    int i;
    for (i = 0; i < 5; i++)
        answer[i] = tolower(answer[i]);

    while (guessCount < ROWS && won == 0){
        if (guessCount == ROWS - 1)
            printf("FINAL GUESS : ");
        else
            printf("GUESS %d! Enter your guess: ", guessCount + 1);

        scanf("%s", guesses[guessCount]);

        for (i = 0; i < 5; i++)
            guesses[guessCount][i] = tolower(guesses[guessCount][i]);

        printLine();

        if (strcmp(guesses[guessCount], answer) == 0){
            printf("   ");

            for (i = 0; i < 5; i++)
                printf("%c", toupper(answer[i]));

            printf("\n");

            if (guessCount == 0)
                printf("You won in 1 guess!\nGOATED!\n");
            else
                printf("You won in %d guesses!\nAmazing!\n", guessCount + 1);

            won = 1;
        }
        else{
            printBoard(guesses, guessCount + 1, answer);
        }

        guessCount++;
    }

    if (won == 0){
        printf("You lost, better luck next time!\n");
    }

    return 0;
}

