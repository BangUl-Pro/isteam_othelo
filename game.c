//
// Created by ??? on 2016. 6. 29..
//

#include "game.h"

#define LINE 8
#define PLAYER1 'O'
#define PLAYER2 'X'

/*
 * TODO ??? ??
 * */
void printHorizontalLine() {
    printf("\t----------------------------------------------------------------\n");
}

/*
 * TODO ??? ??
 * */
void printVerticalLine(int line) {
    printf("%c\t|\t|\t|\t|\t|\t|\t|\t|\t|\n", line);
}

/*
 * TODO ??? ??
 * @params player ????
 * @params x x??
 * @params y y??
 * */
void setPin(char player, char x, int y) {
    printf("%c", player);
    COORD position = {x, y};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
    printf("%c", player);
}


/*
 * TODO ?? ??
 * */
void baseSetting() {
    char line = 'a';
    printf("\t  1\t  2\t  3\t  4\t  5\t  6\t  7\t  8\n");
    printHorizontalLine();
    for (int i = 0; i < LINE; ++i) {
        printVerticalLine(line++);
        printHorizontalLine();
    }
//    setPin(PLAYER1, 5, 1);
}