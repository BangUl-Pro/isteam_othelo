//
// Created by 이동규 on 2016. 6. 29..
//

#include "game.h"

#define LINE 8

/*
 * TODO 가로줄 출력
 * */
void printHorizontalLine() {
    printf("\t----------------------------------------------------------------\n");
}

/*
 * TODO 세로줄 출력
 * */
void printVerticalLine(int line) {
    printf("%c\t|\t|\t|\t|\t|\t|\t|\t|\t|\n", line);
}


/*
 * TODO 기본 세팅
 * */
void baseSetting() {
    char line = 'a';
    printf("\t  1\t  2\t  3\t  4\t  5\t  6\t  7\t  8\n");
    printHorizontalLine();
    for (int i = 0; i < LINE; ++i) {
        printVerticalLine(line++);
        printHorizontalLine();
    }
}