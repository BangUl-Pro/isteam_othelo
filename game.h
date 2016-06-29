//
// Created by 이동규 on 2016. 6. 29..
//

#ifndef OTHELO_GAME_H
#define OTHELO_GAME_H

#include "stdio.h"
#include "windows.h"

#define LINE 8
#define PLAYER1 'O'
#define PLAYER2 'X'
#define ANOTER 1
#define MINE 2
#define PLAYER1_SCORE_X 14
#define PLAYER1_SCORE_Y 0
#define PLAYER2_SCORE_X 14
#define PLAYER2_SCORE_Y 1
#define TURN_X 39
#define TURN_Y 1
#define SCORE_X 35
#define SCORE_Y 0

void baseSetting(int playerWin1, int playerWin2, int draw, int playCount);
int checkGameable();
int getPinCount(char player);
void setPin(char player, int x, char y);
void inputPin(char player);
#endif //OTHELO_GAME_H
