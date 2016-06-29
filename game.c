//
// Created by ??? on 2016. 6. 29..
//

#include "game.h"

int pin[8][8] = {0};

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
void setPin(char player, int x, char y) {
    pin[x - 1][y - 'a'] = player;
    int curY = y - 'a' + 2;
    COORD position = {(x << 3) + 4, curY << 1};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
    printf("%c", player);
}

/*
 * TODO 바둑돌 둘 곳 입력 받기
 * @params player 플레이어
 * */
void inputPin(char player) {
    COORD position = {0, 25};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);

    char x;
    int y;
    printf("input alphabet =   \b\b");
    getchar();
    x = getchar();
    printf("input number =   \b\b");
    scanf("%d", &y);
    setPin(player, y, x);
}

/*
 * TODO 꽉 찼는지 확인
 * */
int isFull() {
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (!pin[i][j])
                break;
        }
        if (!pin[i][j])
            break;
    }

    if (i == 8 && j == 8)
        return 1;
    return 0;
}

/*
 * TODO 한 쪽이 다 먹었을 때
 * */
int isNoPin() {
    int i, j, temp = 0;
    for (i = 0; i < 8; ++i) {
        int state = 0;
        for (j = 0; j < 8; ++j) {
            if (!pin[i][j])
                continue;

            printf("%d\n", pin[i][j]);
            if (!temp)
                temp = pin[i][j];
            else if (pin[i][j] != temp) {
                state = 1;
                break;
            }
        }
        if (state)
            break;
    }
    if (i == 8 && j == 8)
        return 1;
    return 0;
}

/*
 * TODO 바둑돌을 놓을 수 있는지
 * @params player 플레이어
 * @params x x좌표
 * @params y y좌표
 * */
int isSetPinable(char player, int x, char y) {
    // 이미 다른 돌이 있음
    if (pin[x - 1][y - 'a'])
        return 0;
    
}

/*
 * TODO 게임 지속 가능한지 체크
 * */
int checkGameable() {
    int i, j;
    if (isFull())
        return 0;
    if (isNoPin())
        return 0;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (isSetPinable(PLAYER1, i, j))
                return 1;
            if (isSetPinable(PLAYER2, i, j))
                return 1;
        }
    }
    if (i == 8 && j == 8)
        return 0;
    return 1;
}


/*
 * TODO 기본 세팅
 * */
void baseSetting() {
    int i, j;

    system("cls");
    printf("PLAYER1 = %c / %d\t\t\t", PLAYER1, 2);
    printf("w/d/l = %d/%d/%d\n", 0, 0, 0);
    printf("PLAYER2 = %c / %d\t\t\t", PLAYER2, 2);
    printf("TURN = PLAYER1\n");

    char line = 'a';
    printf("\t   1\t   2\t   3\t   4\t   5\t   6\t   7\t   8\n");
    printHorizontalLine();
    for (i = 0; i < LINE; ++i) {
        printVerticalLine(line++);
        printHorizontalLine();
    }
    setPin(PLAYER1, 4, 'd');
    setPin(PLAYER1, 5, 'e');
    setPin(PLAYER2, 5, 'd');
    setPin(PLAYER2, 4, 'e');

//    for (i = 0; i < 8; ++i) {
//        for (j = 0; j < 8; ++j) {
//            printf("%d\t", pin[i][j]);
//        }
//        printf("\n");
//    }
//    endSetting();
}

void endSetting() {
    COORD position = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
    system("cls");
}