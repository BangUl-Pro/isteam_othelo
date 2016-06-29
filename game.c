//
// Created by ??? on 2016. 6. 29..
//

#include "game.h"

#define LINE 8
#define PLAYER1 'O'
#define PLAYER2 'X'

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
 * TODO 바둑돌 두기
 * @params player 플레이어
 * @params x x좌표
 * @params y y좌표
 * */
void setPin(char player, char x, int y) {
    int curX = x - 'a' + 1;
    COORD position = {(y << 3) + 4, curX << 1};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
    printf("%c", player);
}


/*
 * TODO 기본 세팅
 * */
void baseSetting() {
    system("cls");
    char line = 'a';
    printf("\t   1\t   2\t   3\t   4\t   5\t   6\t   7\t   8\n");
    printHorizontalLine();
    for (int i = 0; i < LINE; ++i) {
        printVerticalLine(line++);
        printHorizontalLine();
    }
    setPin(PLAYER1, 'd', 4);
    setPin(PLAYER1, 'e', 5);
    setPin(PLAYER2, 'd', 5);
    setPin(PLAYER2, 'e', 4);
//    endSetting();
}

void endSetting() {
    COORD position = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
    system("cls");
}