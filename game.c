//
// Created by 이동규 on 2016. 6. 29..
//

#include "game.h"

#define LINE 8

void printHyphen() {
    printf("\t--------------------------------\n");
}

void printLine(int line) {
    printf("%c\t|\t|\t|\t|\t|\t|\t|\t|\t|\n", line);
}

void baseSetting() {
    char line = 'a';
    printf("\t  1\t  2\t  3\t  4\t  5\t  6\t  7\t  8\n");
    printHyphen();
    for (int i = 0; i < LINE; ++i) {
        printLine(line++);
        printHyphen();
    }
}