#include <iostream>
#include <Windows.h>
#pragma once
using namespace std;

void visibleCursor(bool isVisible) {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = isVisible;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setCursorPosition(int x, int y) {
    cout << "\033[" << x + 1 << ";" << y + 1 << "H";
}

void setColor(int textColor, int backgroundColor) {
    int color = textColor + (backgroundColor * 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

template <typename T>
void printStr(int x, int y, T symb, int step_x = 0, int step_y = 0, int color = 7, int background = 0) {
    setColor(color, background);
    setCursorPosition(x + step_x, y + step_y);
    cout << symb;
    setColor(7, 0);
}