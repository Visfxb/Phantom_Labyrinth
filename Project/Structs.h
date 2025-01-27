#include "Functions.h"
#pragma once

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
	char str[50] = "";

	const char* toString(const char* format = "%d %B %Y") {
		tm dateInfo = { 0, 0, 0, day, month - 1, year - 1900 };
		strftime(str, 50, format, &dateInfo);
		return str;
	}

	void getNowDate() {
		time_t seconds = time(NULL);
		tm dateInfo = { 0 };
		localtime_s(&dateInfo, &seconds);

		year = dateInfo.tm_year + 1900;
		month = dateInfo.tm_mon + 1;
		day = dateInfo.tm_mday;
	}
};

struct savedGame
{
    bool isGameSaved = false;
    int player_pos_x = 13;
    int player_pos_y = 37;
    bool isCoinOnMap = false;
    int coins = 0;
    int coin_pos_x = 0;
    int coin_pos_y = 0;
    int ghost_pos_x = 6;
    int ghost_pos_y = 13;
    char ghost_vector = 'd';

    void newGame() {
        player_pos_x = 13;
        player_pos_y = 37;
        isCoinOnMap = false;
        coins = 0;
        coin_pos_x = 0;
        coin_pos_y = 0;
        ghost_pos_x = 6;
        ghost_pos_y = 13;
        ghost_vector = 'd';
    }
};

struct achievment {
    char name_achiev[50] = "";
    Date date_add;

    void addAchievment() {
        cout << "Enter achiev: ";
        cin.ignore();
        cin.getline(name_achiev, 50);
        date_add.getNowDate();
    }

    void printAchiev() {
        cout << "Achiev name: " << name_achiev << endl;
        cout << "Date achiev: " << date_add.toString();
    }
};

struct profile {
    char nickname[20] = "";
    char password[20] = "";
    int record = 0;
    Date date_reg;
    int achiev_arr_size = 0;
    achievment* achiev_arr = nullptr;
    savedGame profileSave;

    void addProfileInfo() {
        cout << "Enter nickname: ";
        cin.getline(nickname, 20);
        cout << "Enter password: ";
        cin.getline(password, 20);
        date_reg.getNowDate();
    }

    void printProfile() {
        cout << endl << "Name: " << nickname << endl;
        cout << "Password: " << password << endl;
        cout << "Date reg: " << date_reg.toString() << endl;
        for (int i = 0; i < achiev_arr_size; i++)
        {
            achiev_arr[i].printAchiev();
            cout << endl;
        }
        cout << "\n\n\n";
    }
};