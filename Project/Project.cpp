#include <conio.h>
#include <ctime>
#include <cstdio>
#include "Structs.h"
using namespace std;


int main()
{
    SetConsoleTitle(TEXT("Phantom Labyrinth"));
    srand(time(0));
    setlocale(0, "");
    visibleCursor(false);


    bool isFirstLine = true;
    bool inGame = true;
    bool isPause = false;
    bool confirm = false;

    int row = 0;
    int col = 0;
    int x = 0;
    int y = 0;
    int pause_x = 3;
    int pause_y = 25;
    int map_step_x = 1;
    int map_step_y = 0;
    int profile_size = 0;
    int active_profile_id = -1;
    int h = -1;

    char p[20] = "";
    char src[20] = "";
    char str[] = "NONE";
    char c;

    FILE* map_file = nullptr;
    profile* profiles = new profile[profile_size];
    profile new_profile;
    savedGame testSave;
    
    fopen_s(&map_file, "map.txt", "r");
    if (map_file == nullptr) {
        cout << "Error: unable to open file!" << endl;
        return 1;
    }

    while (fscanf_s(map_file, "%c", &c, 1) == 1) {
        if (c == '\n') {
            row++;
            isFirstLine = false;
        }
        else if (isFirstLine)
            col++;
    }
    row++;
    
    char** map = new char* [row];
    for (int i = 0; i < row; i++)
        map[i] = new char[col];

    rewind(map_file);
    while (fscanf_s(map_file, "%c", &c, 1) == 1) {
        if (c != '\n') {
            map[x][y++] = c;
        }
        else {
            x++;
            y = 0;
        }
    }
    fclose(map_file);



    /*printLogo(3, 35);
    loadScreen(20, 33, inGame);
    system("cls");*/
    while (inGame)
    {
    mm:
        if (active_profile_id == -1)
            printMenu(str);
        else
            printMenu(profiles[active_profile_id].nickname);
        switch (_getch())
        {

        case '1':   //New game
            buttonAnimation("1 - NEW GAME", 25, 13, 10);
            system("cls");
            testSave.newGame();
            while (!testSave.isCoinOnMap) {
                testSave.coin_pos_x = rand() % 16;
                testSave.coin_pos_y = rand() % 40;
                if (map[testSave.coin_pos_x][testSave.coin_pos_y] == ' ')
                    testSave.isCoinOnMap = true;
            }
        labyrinth:
            printStr(0, 0, "$     COINS: ");
            printStr(0, 13, testSave.coins);

            printMap(map, row, col, map_step_x, map_step_y);
            printStr(testSave.player_pos_x, testSave.player_pos_y, '@', map_step_x, map_step_y);
            printStr(testSave.ghost_pos_x, testSave.ghost_pos_y, '#', map_step_x, map_step_y);
            printStr(testSave.coin_pos_x, testSave.coin_pos_y, '$', map_step_x, map_step_y);

            while (inGame)
            {
                if (_kbhit()) {
                    switch (_getch())
                    {
                    case 72:
                    case 'w':
                        movePlayer(map, testSave.player_pos_x, testSave.player_pos_y, -1, 0, testSave.coins, testSave.isCoinOnMap, testSave.coin_pos_x, testSave.coin_pos_y, map_step_x, map_step_y);
                        break;
                    case 75:
                    case 'a':
                        movePlayer(map, testSave.player_pos_x, testSave.player_pos_y, 0, -1, testSave.coins, testSave.isCoinOnMap, testSave.coin_pos_x, testSave.coin_pos_y, map_step_x, map_step_y);
                        break;
                    case 80:
                    case 's':
                        movePlayer(map, testSave.player_pos_x, testSave.player_pos_y, 1, 0, testSave.coins, testSave.isCoinOnMap, testSave.coin_pos_x, testSave.coin_pos_y, map_step_x, map_step_y);
                        break;
                    case 77:
                    case 'd':
                        movePlayer(map, testSave.player_pos_x, testSave.player_pos_y, 0, 1, testSave.coins, testSave.isCoinOnMap, testSave.coin_pos_x, testSave.coin_pos_y, map_step_x, map_step_y);
                        break;
                    case 27:
                        isPause = true;
                        while (isPause)
                        {
                            printPause(pause_x, pause_y);
                            switch (_getch())
                            {
                            case '1':
                                buttonAnimation("1 - CONTINUE", 30, 9, 30);
                                system("cls");
                                isPause = false;
                                break;
                            case '2':
                                buttonAnimation("2 - SAVE AND EXIT", 30, 15, 30);
                                system("cls");
                                goto mm;
                                break;
                            }
                        }
                        printStr(0, 0, "$     COINS: ");
                        printStr(0, 13, testSave.coins);
                        printMap(map, row, col, map_step_x, map_step_y);
                        printStr(testSave.player_pos_x, testSave.player_pos_y, '@', map_step_x, map_step_y);
                        printStr(testSave.ghost_pos_x, testSave.ghost_pos_y, '#', map_step_x, map_step_y);
                        printStr(testSave.coin_pos_x, testSave.coin_pos_y, '$', map_step_x, map_step_y);
                        break;
                    }
                }
                while (!testSave.isCoinOnMap) {
                    testSave.coin_pos_x = rand() % 16;
                    testSave.coin_pos_y = rand() % 40;
                    if (map[testSave.coin_pos_x][testSave.coin_pos_y] == ' ') {
                        printStr(testSave.coin_pos_x, testSave.coin_pos_y, '$', map_step_x, map_step_y);
                        testSave.isCoinOnMap = true;
                    }
                }
                static clock_t last_ghost_time = clock();
                if (clock() - last_ghost_time >= 250) {
                    last_ghost_time = clock();
                    if (!isWallNext(map, testSave.ghost_pos_x, testSave.ghost_pos_y, testSave.ghost_vector)) {
                        moveGhost(map, testSave.ghost_pos_x, testSave.ghost_pos_y, testSave.ghost_vector, testSave.player_pos_x, testSave.player_pos_y, inGame, testSave.coins, testSave.coin_pos_x, testSave.coin_pos_y, map_step_x, map_step_y);
                    }
                    else {
                        testSave.ghost_vector = chooseGhostDirection(map, testSave.ghost_pos_x, testSave.ghost_pos_y, testSave.ghost_vector);
                        moveGhost(map, testSave.ghost_pos_x, testSave.ghost_pos_y, testSave.ghost_vector, testSave.player_pos_x, testSave.player_pos_y, inGame, testSave.coins, testSave.coin_pos_x, testSave.coin_pos_y, map_step_x, map_step_y);
                    }
                }
                /*
                Dollar animation

                static clock_t last_animation_time = clock();
                if (clock() - last_animation_time >= 500) {
                    last_animation_time = clock();
                    if (dollCymbol) {
                        printStr(0, 0, '|');
                        dollCymbol = false;
                    }
                    else {
                        cout << '$';
                        dollCymbol = true;
                    }
                }*/

            }
            while (!inGame) {
                switch (_getch())
                {
                case '1':
                    buttonAnimation("1 - MAIN MENU", 30, 13, 30);
                    system("cls");
                    inGame = true;
                    goto mm;
                    break;
                case '2':
                    buttonAnimation("2 - RESTART", 30, 19, 30);
                    system("cls");
                    testSave.newGame();
                    inGame = true;
                    goto labyrinth;
                }
            }
            break;
        case '2':    //Continue
            buttonAnimation("2 - CONTINUE", 25, 13, 43);
            system("cls");
            goto labyrinth;
            break;

        case '3':    //Profiles
            buttonAnimation("3 - PROFILES", 25, 13, 76);
            system("cls");
            log:
            printLogMenu();
            strcpy_s(p, "");
            while (true) {
                if (strcmp(src, "") && strcmp(p, "")) {
                    confirm = false;
                    h = -1;
                    for (int i = 0; i < profile_size; i++)
                    {
                        if (!strcmp(profiles[i].nickname, src) && !strcmp(profiles[i].password, p)) {
                            confirm = true;
                            h = i;
                            break;
                        }
                    }
                    if (confirm) {
                        printButton("ENTER", 15, 0, 0);
                        switch (_getch())
                        {
                        case 13:
                            buttonAnimation("ENTER", 15, 0, 0);
                            active_profile_id = h;
                            system("cls");
                            goto mm;
                        }
                    }
                    else {
                        printStr(5, 0, "INCORRECT NICKNAME OF PASSWORD");
                        strcpy_s(src, "");
                        strcpy_s(p, "");
                        printStr(11, 54, "                    ");
                        printStr(17, 54, "                    ");
                    }
                }
                switch (_getch())    //Log in
                {
                case '1':
                    printStr(11, 54, "                    ");
                    printStr(12, 54, "--------------------");
                    setCursorPosition(11, 54);
                    visibleCursor(true);
                    cin.getline(src, 20);
                    visibleCursor(false);
                    printStr(12, 54, "                    ");
                    break;

                case '2':
                    printStr(17, 54, "                    ");
                    printStr(18, 54, "--------------------");
                    setCursorPosition(17, 54);
                    visibleCursor(true);
                    cin.getline(p, 20);
                    visibleCursor(false);
                    printStr(18, 54, "                    ");
                    break;

                case '3':
                    buttonAnimation("3 - SIGN UP", 24, 22, 60);
                    system("cls");
                    printSignMenu();
                    while (true) {
                        if (_kbhit()) {
                            switch (_getch())    // Sign up
                            {
                            case '1':
                                while (true) {
                                    printStr(9, 56, "                    ");
                                    printStr(10, 56, "--------------------");
                                    setCursorPosition(9, 56);
                                    visibleCursor(true);
                                    cin.getline(new_profile.nickname, 20);
                                    visibleCursor(false);
                                    printStr(10, 56, "                    ");

                                    bool isTaken = false;
                                    for (int i = 0; i < profile_size; i++) {
                                        if (!strcmp(profiles[i].nickname, new_profile.nickname)) {
                                            printStr(8, 12, "! THIS NAME IS TAKEN");
                                            printStr(9, 12, "   CHOOSE ANOTHER");
                                            printStr(9, 56, "                    ");
                                            strcpy_s(new_profile.nickname, "");
                                            isTaken = true;
                                            break;
                                        }
                                    }
                                    if (!isTaken) break;
                                }
                                break;

                            case '2':
                                printStr(15, 56, "                    ");
                                printStr(16, 56, "--------------------");
                                setCursorPosition(15, 56);
                                visibleCursor(true);
                                cin.getline(new_profile.password, 20);
                                visibleCursor(false);
                                printStr(16, 56, "                    ");
                                break;

                            case '3':
                                while (true) {
                                    printStr(21, 60, "                    ");
                                    printStr(22, 60, "--------------------");
                                    setCursorPosition(21, 60);
                                    visibleCursor(true);
                                    cin.getline(p, 20);
                                    visibleCursor(false);
                                    printStr(22, 60, "                    ");

                                    if (strcmp(new_profile.password, p) != 0) {
                                        printStr(21, 12, "! INCORRECT PASSWORD");
                                        strcpy_s(p, "");
                                        printStr(21, 60, "                    ");
                                    }
                                    else {
                                        printButton("ENTER", 16, 13, 90);
                                        printStr(21, 12, "                    ");
                                        break;
                                    }
                                }
                                break;

                            case '4':
                                buttonAnimation("4 - LOG IN", 23, 25, 63);
                                system("cls");
                                goto log;
                                break;

                            case 27:
                                system("cls");

                            }
                        }

                        if (strcmp(new_profile.nickname, "") && strcmp(new_profile.password, "")) {
                            if (_kbhit()) {
                                switch (_getch()) {
                                case 13:
                                    buttonAnimation("ENTER", 16, 13, 90);
                                    addItemBack(profiles, profile_size, new_profile);
                                    strcpy_s(new_profile.nickname, "");
                                    strcpy_s(new_profile.password, "");
                                    active_profile_id = profile_size - 1;
                                    system("cls");
                                    goto mm;
                                    break;
                                }
                            }
                        }
                    }
                    break;

                case 27:
                    system("cls");
                    goto mm;
                }

            }
            break;

        case 27:    //Close game
            inGame = false;
            break;
        }
        if (!inGame) break;
    }
    system("cls");


    

    
        

    for (int i = 0; i < row; i++)
        delete[] map[i];
    delete[] map;
    return 0;
}