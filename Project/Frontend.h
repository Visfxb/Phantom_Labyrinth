#include "BaseFunc.h"
#include <string>
#pragma once


void printLogo(int x, int y) {
    printStr(x++, y, " ____  _                 _                     ");
    printStr(x++, y, "|  _ \\| |__   __ _ _ __ | |_ ___  _ __ ___     ");
    printStr(x++, y, "| |_) | '_ \\ / _` | '_ \\| __/ _ \\| '_ ` _ \\    ");
    printStr(x++, y, "|  __/| | | | (_| | | | | || (_) | | | | | |   ");
    printStr(x++, y, "|_|   |_| |_|\\__,_|_| |_|\\__\\___/|_| |_| |_|   ");
    printStr(x++, y, "| |    __ _| |__  _   _ _ __(_)_ __ | |_| |__  ");
    printStr(x++, y, "| |   / _` | '_ \\| | | | '__| | '_ \\| __| '_ \\ ");
    printStr(x++, y, "| |__| (_| | |_) | |_| | |  | | | | | |_| | | |");
    printStr(x++, y, "|_____\\__,_|_.__/ \\__, |_|  |_|_| |_|\\__|_| |_|");
    printStr(x++, y, "                  |___/                        ");
}



void printMap(char arr[16][40], int height, int width, int x = 0, int y = 0) {
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            printStr(x + i, y + j, arr[i][j]);
        cout << endl;
    }
}



void printButton(string str, int width, int x, int y) {
    printStr(x, y, ".");
    for (int i = y + 1; i < y + width - 1; i++)
        printStr(x, i, "-");
    printStr(x++, y + width - 1, ".");

    for (int i = x; i < x + 3; i++)
    {
        printStr(i, y, "|");
        printStr(i, y + width - 1, "|");
    }
    x += 3;
    printStr(x, y, "'");
    for (int i = y + 1; i < y + width - 1; i++)
        printStr(x, i, "-");
    printStr(x++, y + width - 1, "'");
    printStr(x - 3, y + 1 + (width - 2 - str.length()) / 2, str);
}



void buttonAnimation(string str, int width, int x, int y) {
    for (int i = y; i < y + width; i++)
        printStr(x, i, " ");
    x++;
    for (int i = 0; i < 3; i++)
    {
        printStr(x, y, " ");
        for (int i = y + 1; i < y + width - 2; i++)
            printStr(x, i, " ", 0, 0, 0, 7);
        printStr(x++, y + width - 1, " ");
    }
    for (int i = y; i < y + width; i++)
        printStr(x, i, " ");
    printStr(x - 2, y + 1 + (width - 2 - str.length()) / 2, str,0, 0, 0, 7);
    Sleep(200);
}



void loadScreen(int x, int y, bool& isGame) {
    printStr(x    , y, ".------------------------------------------------.");
    printStr(x + 1, y, "|                                                |");
    printStr(x + 2, y, "|                                                |");
    printStr(x + 3, y, "'------------------------------------------------'");

    for (int i = y + 1; i < y + 10; i++)
    {
        printStr(x + 1, i, "#", 0, 0, 10, 10);
        printStr(x + 2, i, "#", 0, 0, 10, 10);
        Sleep(150);
    }
    for (int i = y + 10; i < y + 40; i++)
    {
        printStr(x + 1, i, "#", 0, 0, 10, 10);
        printStr(x + 2, i, "#", 0, 0, 10, 10);
        Sleep(75);
    }
    Sleep(1000);
    for (int i = y + 40; i < y + 49; i++)
    {
        printStr(x + 1, i, "#", 0, 0, 10, 10);
        printStr(x + 2, i, "#", 0, 0, 10, 10);
        Sleep(25);
    }
    Sleep(400);
    for (int i = 0; i < 4; i++)
        printStr(x + i, y, "                                                  ");

    printButton("PLAY", 18, x, y + 12);
    Sleep(200);

    buttonAnimation("PLAY", 18, x, y + 12);
    Sleep(200);
}

/*
void printProfile(bool isActive, int x, int y, char* nick, int record, char* reg_date) {
    if (isActive) {
        printStr(x, y, "NICKNAME - ");
        printStr(x++, y + 11, nick);
        printStr(x, y, "RECORD - ");
        printStr(x++, y + 9, record);
        printStr(x, y, "REGISTRAITION DATE - ");
        printStr(x++, y + 21, reg_date);
    }
    else
}*/


void printMenu(char* str) {
    printLogo(1, 35);
    printButton("1 - NEW GAME", 25, 13, 10);
    printButton("2 - CONTINUE", 25, 13, 43);
    printButton("3 - PROFILES", 25, 13, 76);
    printButton("1 - NEW GAME", 25, 20, 10);
    printButton("2 - CONTINUE", 25, 20, 43);
    printButton("ESC - EXIT", 25, 20, 76);
}



void printGameOver(int x, int y, int coins) {
    printStr(x++, y + 1 + (39 - 15) / 2,    "---------------");
    printStr(x++, y + 1 + (39 - 17) / 2,   "/               \\");
    printStr(x++, y + 1 + (39 - 19) / 2,  "/    GAME OVER    \\");
    printStr(x++, y + 1 + (39 - 21) / 2, "/                   \\");
    printStr(x++, y, "+---------------------------------------+");
    for (int i = x; i < x + 17; i++)
        printStr(i, y, "|                                       |");
    x += 17;
    printStr(x++, y, "+---------------------------------------+");

    
    printStr(x - 17, y + 1 + (39 - (12 + to_string(coins).length())) / 2, "YOUR SCORE: ");
    setCursorPosition(x - 17, y + 1 + (39 + 12 - to_string(coins).length()) / 2);
    cout << coins;
    printStr(x - 15, y + 1, "---------------------------------------");

    printButton("1 - MAIN MENU", 30, x - 13, y + 5);
    printButton("2 - RESTART", 30, x - 7, y + 5);

}



void printPause(int x, int y) {
    printStr(x++, y + 1 + (39 - 15) / 2,    "---------------");
    printStr(x++, y + 1 + (39 - 17) / 2,   "/               \\");
    printStr(x++, y + 1 + (39 - 19) / 2,  "/      PAUSE      \\");
    printStr(x++, y + 1 + (39 - 21) / 2, "/                   \\");
    printStr(x++, y, "+---------------------------------------+");
    for (int i = x; i < x + 13; i++)
        printStr(i, y, "|                                       |");
    x += 13;
    printStr(x++, y, "+---------------------------------------+");

    printButton("1 - CONTINUE", 30, x - 13, y + 5);
    printButton("2 - SAVE AND EXIT", 30, x - 7, y + 5);
}



/*
void printGhost(int x, int y) {
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢶⡒⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠟⡟⠛⠿⢿⣴⣦⣀⡀⠀⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠖⠒⠒⠶⠤⣄⡃⠠⠽⠁⠦    ");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⢤⡀⠀⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⠃⠀⠀⠀⠀⠀⠀⢀⠖⠀⠀⠀⠀⠀⠀⠽⣆⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⠀⠀⣆⡀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠁⠀⠀⠀⠉⠁⠀⠀⣰⣿⣿⣿⣷⡀⠀⣠⣶⣄⠐⠟⡆⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⡇⢠⣿⣿⣿⡆⠀⢳⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⠀⠀⠀⠀⠀⠀⠀⠀⠿⢻⣿⣿⣿⣿⠁⢸⣿⣿⣿⡏⠀⡾⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⠀⢠⠇⠀⠀⠀⢶⣧⣤⡀⠀⠀⢻⣿⣿⠛⢁⣤⡈⢿⣿⣿⡹⠀⡇⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀⠀⠀⠀⠀⠁⠉⠉⠀⠀⠈⢣⠀⠀⠈⠛⠀⠈⠛⠋⠁⠀⡇⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⢀⠴⠃⡴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⠀⠀⠀⠀⠀⠀⢰⠧⢄⠀");
    printStr(x++, y, "⠀⠀⣀⠤⠚⠁⠀⣜⣀⠤⠀⠀⠀⠀⠀⠀⠀⠀⢤⣄⡤⠇⠀⠀⠀⠀⠀⠀⠀⠀⡘⠀⠈⢷");
    printStr(x++, y, "⡖⠉⢀⠀⠀⠀⠀⠀⠀⠀⠀⡶⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⡀⢰⠀⠀⢰⠛⠶⠖⠚");
    printStr(x++, y, "⢹⡀⠀⠈⠑⠂⠄⠀⠀⣠⢞⡅⠀⠀⠀⠀⠀⠀⣤⠀⠀⠀⠀⠀⠀⠧⠞⠀⢠⠋⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠑⠂⠠⠤⠤⠤⢴⠞⢡⠋⠀⢀⠀⠀⣠⠀⠀⠙⠒⠁⠀⢀⡜⠁⠀⠀⢠⠃⠀⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠀⡞⠀⠈⠉⠉⠁⢀⠞⠁⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⡰⠃⠀⠀⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⢰⠁⡀⠀⠀⠀⠀⣸⠀⠀⠀⣀⡤⠴⡋⠀⠀⠀⣠⠞⠀⠀⠀⠀⠀⠀⠀⠀");
    printStr(x++, y, "⠀⠀⠀⠀⠀⠀⠘⣆⣀⠔⠋⠉⠀⠙⠦⠴⠊⠁⠀⠀⠓⠦⠴⠚⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀");
}*/


void printLogIn(int x, int y) {
    printStr(x++, y, " _                     _       ");
    printStr(x++, y, "| |    ___   __ _     (_)_ __  ");
    printStr(x++, y, "| |   / _ \\ / _` |    | | '_ \\ ");
    printStr(x++, y, "| |__| (_) | (_| |    | | | | |");
    printStr(x++, y, "|_____\\___/ \\__, |    |_|_| |_|");
    printStr(x++, y, "            |___/              ");
}


void printLogMenu() {
    printLogIn(1, 42);
    printButton("1 - NICKNAME:                     ", 45, 9, 35);
    printButton("2 - PASSWORD:                     ", 45, 15, 35);
    printStr(24, 31, "DON'T HAVE AN ACCOUNT?");
    printButton("3 - SIGN UP", 24, 22, 60);
}


void printSignUp(int x, int y) {
    printStr(x++, y, " ____  _                              ");
    printStr(x++, y, "/ ___|(_) __ _ _ __       _   _ _ __  ");
    printStr(x++, y, "\\___ \\| |/ _` | '_ \\     | | | | '_ \\ ");
    printStr(x++, y, " ___) | | (_| | | | |    | |_| | |_) |");
    printStr(x++, y, "|____/|_|\\__, |_| |_|     \\__,_| .__/ ");
    printStr(x++, y, "         |___/                 |_|    ");
}

void printSignMenu() {
    printSignUp(0, 40);
    printButton("1 - NICKNAME:                     ", 47, 7, 36);
    printButton("2 - PASSWORD:                     ", 47, 13, 36);
    printButton("3 - CONFIRM PASSWORD:                     ", 47, 19, 36);
    printStr(27, 33, "ALREADY HAVE AN ACCOUNT?");
    printButton("4 - LOG IN", 23, 25, 63);
}