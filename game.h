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

void baseSetting();
int checkGameable();
void setPin(char player, int x, char y);
void inputPin(char player);
#endif //OTHELO_GAME_H
