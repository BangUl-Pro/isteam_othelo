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
    printf("%d\t|\t|\t|\t|\t|\t|\t|\t|\t|\n", line);
}

/*
 * TODO 바둑돌 두기
 * @params player 플레이어
 * @params x x좌표
 * @params y y좌표
 * */
void setPin(char player, int x, char y) {
    pin[x - 1][y - 'a'] = player;
    int curY = y - 'a' + 1;
    gotoxy((curY << 3) + 4, (x << 1) + 2);
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

    if ((curX < 0 && curX > 7) || (curY < 0 && curY > 7))
        return 0;

    // 이미 다른 돌이 있음
    if (pin[curX][curY])
        return 0;

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
int inputPin(char player) {
    char y;
    int x;
    int temp;
    do {
        gotoxy(0, 20);
        printf("input (x, y) = \t\t\t\t\t");
        gotoxy(15, 20);
        while ((x = getchar()) == '\n');
        if (x == 'r')
            return 0;
        while ((y = getchar()) == '\n');
        if (y == 'r') {
            return 0;
        }
        if (x >= 'a' && x <= 'z') {
            temp = x;
            x = y;
            y = temp;
        }
        x -= '0';
    }
    while (!changePin(player, x, y));
    setPin(player, x, y);

    // 바둑돌 수
    gotoxy(PLAYER1_SCORE_X, PLAYER1_SCORE_Y);
    printf("%d  \b\b", getPinCount(PLAYER1));
    gotoxy(PLAYER2_SCORE_X, PLAYER2_SCORE_Y);
    printf("%d  \b\b", getPinCount(PLAYER2));

    // 누구 차례인지 변경
    gotoxy(TURN_X, TURN_Y);
    if (player == PLAYER1)
        printf("PLAYER2");
    else
        printf("PLAYER1");
    return 1;
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
//        if (!pin[i][j])
//            break;
    }

    if (i == 8 && j == 8)
        return 1;				// true means It's full.
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
            if (!pin[i][j])				// If Pin doesn't exist.
                continue;
            if (!temp)					// If Pin exist, then check. If temp = 0, then do.
                temp = pin[i][j];
            else if (pin[i][j] != temp) {	// else temp != 0, then check.
                state = 1;				// each player have pin.
                break;
            }
        }
        if (state)
            break;
    }
    if (i == 8 && j == 8)
        return 1;				// true means one player have no pin.
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
    int curX = x ;
    int curY = y - 'a';
    int count, state, changeCount = 0;
    int j, k;

    // 이미 다른 돌이 있음
    if (pin[curX][curY])
        return 0;

    for (j = -1; j <= 1; ++j) {
        for (k = -1; k <= 1; ++k) {
            if (j == 0 && k == 0)
                continue;
            int j2 = j;
            int k2 = k;
			int iX = curX + j2 ;
			int iY = curY + k2 ;
	            count = 0;
//            while ((state = isAnotherPin(player, curX + j2, curY + k2)) == 1) {
			while ( ( state = isAnotherPin ( player , iX , iY ) ) == 1 )
			{
//                j2+=j;
				iX += j ;
//                k2+=k;
				iY += k ;
                count++;
            }

			if ( ! ( count && ( iX >= 0 ) && ( iX <= 7 ) && ( iY >= 0 ) && ( iY <= 7 ) && ( 2 == state ) ) )		// If that place isn't empty then find another way.
			{
				continue ;
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
int checkGameable( int iTurn ) {
    int i, j;
//	int iCheck = 0 ;
    if ( isFull () || isNoPin () )
        return 0;
//    if (isNoPin())
//        return 0;

	if ( iTurn )				// Player1 Turn
	{
		for ( i = 0 ; i < 8 ; ++i )
		{
			for ( j = 0 ; j < 8 ; ++j )
			{
				if ( isSetPinable ( PLAYER1 , i , j + 'a' ) )
				return 1 ;
			}
		}
	}
	else						// Player2 Turn
	{
		for ( i = 0 ; i < 8 ; ++i )
		{
			for ( j = 0 ; j < 8 ; ++j )
			{
				if ( isSetPinable ( PLAYER2 , i , j + 'a' ) )
				return 1 ;
			}
		}
	}
    /*for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if ( ( iCheck != 1 ) && isSetPinable(PLAYER1, i, j + 'a'))
                iCheck += 1 ;
            if ( ( iCheck != 2 ) && isSetPinable(PLAYER2, i, j + 'a'))
                iCheck += 2;
			if ( 3 == iCheck )
				return 3 ;
        }
    }*/
//    if (i == 8 && j == 8)
//        return 0;
    return 0;
}


/*
 * TODO 기본 세팅
 * */
void baseSetting(int playerWin1, int playerWin2, int draw, int playCount) {
    int i, j;

    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            pin[i][j] = 0;
        }
    }

    system("cls");
    printf("PLAYER1 = %c / %d\t\t", PLAYER1, 2);
    printf("PLAYER1 %d VS %d PLAYER2 \t DRAW %d\n", playerWin1, playerWin2, draw);
    printf("PLAYER2 = %c / %d\t\t\t", PLAYER2, 2);
    if (playCount % 2)
        printf("TURN = PLAYER1\n");
    else
        printf("TURN = PLAYER2\n");

    char line = 1;
    printf("\t    a\t    b\t    c\t    d\t    e\t    f\t    g\t    h\n");
    printHorizontalLine();
    for (i = 0; i < LINE; ++i) {
        printVerticalLine(line++);
        printHorizontalLine();
    }
    setPin(PLAYER1, 4, 'd');
    setPin(PLAYER1, 5, 'e');
    setPin(PLAYER2, 5, 'd');
    setPin(PLAYER2, 4, 'e');

    gotoxy(50, 21);
    printf("재시작은 r");
}

void endSetting() {
    COORD position = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
    system("cls");
}