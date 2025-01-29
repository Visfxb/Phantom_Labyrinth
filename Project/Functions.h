#include "ArrayTemplate.h"
#include "Frontend.h"
#pragma once



void movePlayer(char** arr, int& x, int& y, int step_x, int step_y, int& coins, bool& isCoinOnMap, int coin_pos_x, int coin_pos_y, int map_step_x = 0, int map_step_y = 0) {
    if (arr[x + step_x][y + step_y] != '-' && arr[x + step_x][y + step_y] != '|' && arr[x + step_x][y + step_y] != '+') {
        if (x + step_x == coin_pos_x && y + step_y == coin_pos_y) {
            coins++;
            printStr(0, 13, coins);
            isCoinOnMap = false;
        }

        printStr(x, y, ' ', map_step_x, map_step_y);
        x += step_x;
        y += step_y;
        printStr(x, y, '@', map_step_x, map_step_y);
    }
}



char chooseGhostDirection(char** arr, int x, int y, char vector) {
    int size = 0;
    char* rand_direc = new char[size];
    if (arr[x - 1][y] != '|' && arr[x - 1][y] != '-' && arr[x - 1][y] != '+') {
        addItemBack(rand_direc, size, 'w');
        addItemBack(rand_direc, size, 'w');
        addItemBack(rand_direc, size, 'w');
    }
    if (arr[x][y + 1] != '|' && arr[x][y + 1] != '-' && arr[x][y + 1] != '+') {
        addItemBack(rand_direc, size, 'd');
        addItemBack(rand_direc, size, 'd');
        addItemBack(rand_direc, size, 'd');
    }
    if (arr[x + 1][y] != '|' && arr[x + 1][y] != '-' && arr[x + 1][y] != '+') {
        addItemBack(rand_direc, size, 's');
        addItemBack(rand_direc, size, 's');
        addItemBack(rand_direc, size, 's');
    }
    if (arr[x][y - 1] != '|' && arr[x][y - 1] != '-' && arr[x][y - 1] != '+') {
        addItemBack(rand_direc, size, 'a');
        addItemBack(rand_direc, size, 'a');
        addItemBack(rand_direc, size, 'a');
    }

    for (int i = 0; i < size; i++)
        if (rand_direc[i] == vector) {
            delItem(rand_direc, size, i);
            delItem(rand_direc, size, i);
        }

    char out = rand_direc[rand() % size];
    delete[] rand_direc;
    return out;

}



bool isWallNext(char** arr, int x, int y, char vector) {
    switch (vector)
    {
    case 'w':
        if (arr[x - 1][y] != '|' && arr[x - 1][y] != '-' && arr[x - 1][y] != '+') return false;
        else return true;
    case 'd':
        if (arr[x][y + 1] != '|' && arr[x][y + 1] != '-' && arr[x][y + 1] != '+') return false;
        else return true;
    case 's':
        if (arr[x + 1][y] != '|' && arr[x + 1][y] != '-' && arr[x + 1][y] != '+') return false;
        else return true;
    case 'a':
        if (arr[x][y - 1] != '|' && arr[x][y - 1] != '-' && arr[x][y - 1] != '+') return false;
        else return true;
    }
}



void moveGhost(char** arr, int& ghost_x, int& ghost_y, char vector, int player_x, int player_y, bool& game, int coins, int coin_x, int coin_y, int map_step_x = 0, int map_step_y = 0) {

    int distance_x = abs(player_x - ghost_x);
    int distance_y = abs(player_y - ghost_y);

    if (distance_x <= 10 && distance_y <= 10) {
        if (player_x < ghost_x && arr[ghost_x - 1][ghost_y] == ' ')
            vector = 'w';
        else if (player_x > ghost_x && arr[ghost_x + 1][ghost_y] == ' ')
            vector = 's';
        else if (player_y < ghost_y && arr[ghost_x][ghost_y - 1] == ' ')
            vector = 'a';
        else if (player_y > ghost_y && arr[ghost_x][ghost_y + 1] == ' ')
            vector = 'd';
    }

    switch (vector)
    {
    case 'w':
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, ' ', map_step_x, map_step_y);
        ghost_x -= 1;
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, '#', map_step_x, map_step_y);
        break;
    case 'd':
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, ' ', map_step_x, map_step_y);
        ghost_y += 1;
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, '#', map_step_x, map_step_y);
        break;
    case 's':
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, ' ', map_step_x, map_step_y);
        ghost_x += 1;
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, '#', map_step_x, map_step_y);
        break;
    case 'a':
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, ' ', map_step_x, map_step_y);
        ghost_y -= 1;
        if (ghost_x == coin_x && ghost_y == coin_y)
            printStr(ghost_x, ghost_y, '$', map_step_x, map_step_y);
        else
            printStr(ghost_x, ghost_y, '#', map_step_x, map_step_y);
        break;
    }
    if (ghost_x == player_x && ghost_y == player_y){
        printGameOver(3, 25, coins);
        game = false;
    }
}