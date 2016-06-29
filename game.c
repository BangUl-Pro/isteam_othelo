//
// Created by ??? on 2016. 6. 29..
//

#include "game.h"

int pin[8][8] = {0};

int isSetPinable(char player, int x, char y);
int isAnotherPin(char player, int x, char y);

void gotoxy(int x, int y) {
    COORD position = {x, y};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
}

int getPinCount(char player) {
    int i, j;
    int count = 0;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (pin[i][j] == player)
                count++;
        }
    }
    return count;
}

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
    gotoxy((x << 3) + 4, curY << 1);
    printf("%c", player);
}

/*
 * TODO 핀 놓는 순간 둘러쌓인 핀 뒤집기
 * */
int changePin(char player, int x, char y) {
    int curX = x - 1;
    int curY = y - 'a';
    int count, state, changeCount = 0;
    int j, k;
    for (j = -1; j <= 1; ++j) {
        for (k = -1; k <= 1; ++k) {
            if (j == 0 && k == 0)
                continue;
            int j2 = j;
            int k2 = k;
            count = 0;
            while ((state = isAnotherPin(player, curX + j2, curY + k2)) == 1) {
                j2+=j;
                k2+=k;
                count++;
            }
            if (state == 2 && count > 0) {
                changeCount++;
                while (count--) {
                    j2 -= j;
                    k2 -= k;
                    setPin(player, x + j2, y + k2);
                }
            }
        }
    }
    if (changeCount)
        return 1;
    return 0;
}

/*
 * TODO 바둑돌 둘 곳 입력 받기
 * @params player 플레이어
 * */
void inputPin(char player) {
    gotoxy(0, 20);
    char y;
    int x;
    do {
        printf("input alphabet =   \b\b");
        getchar();
        y = getchar();
        printf("input number =   \b\b");
        scanf("%d", &x);
    }
    while (!changePin(player, x, y));
    setPin(player, x, y);

    gotoxy(PLAYER1_SCORE_X, PLAYER1_SCORE_Y);
    printf("%d", getPinCount(PLAYER1));
    gotoxy(PLAYER2_SCORE_X, PLAYER2_SCORE_Y);
    printf("%d", getPinCount(PLAYER2));
    gotoxy(TURN_X, TURN_Y);
    if (player == PLAYER1)
        printf("PLAYER2");
    else
        printf("PLAYER1");
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
 * TODO player의 돌과 다른 돌인지 확인
 * @param player 플레이어
 * @param x x좌표
 * @param y y좌표
 * @return 0 벽 or 아무 돌도 없음
 * @return 1 다른 돌
 * @return 2 내 돌
 * */
int isAnotherPin(char player, int x, char y) {
//    printf("x = %d\n", x);
//    printf("y = %d\n", y);
    if (x < 0 || y < 0 || x > 7 || y > 7 || !pin[x][y])
        return 0;
    else if (pin[x][y] == player)
        return 2;
    return 1;
}

/*
 * TODO 바둑돌을 놓을 수 있는지
 * @params player 플레이어
 * @params x x좌표
 * @params y y좌표
 * */
int isSetPinable(char player, int x, char y) {
    // 이미 다른 돌이 있음
    int curX = x - 1;
    int curY = y - 'a';
    int count = 0, state = 0;
    if (pin[curX][curY])
        return 0;

    int j, k;
    for (j = -1; j <= 1; ++j) {
        for (k = -1; k <= 1; ++k) {
            if (j == 0 && k == 0)
                continue;
            int j2 = j;
            int k2 = k;
            count = 0;
            while ((state = isAnotherPin(player, curX + j2, curY + k2)) == 1) {
                j2+=j2;
                k2+=k2;
                count++;
            }
            if (state == 2 && count > 0) {
                return 1;
            }
        }
    }
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
//    for (i = 0; i < 8; ++i) {
//        for (j = 0; j < 8; ++j) {
//            if (isSetPinable(PLAYER1, i, j))
//                return 1;
//            if (isSetPinable(PLAYER2, i, j))
//                return 1;
//        }
//    }
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