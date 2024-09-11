
#ifndef GAMETOWER_INTERFACE_H
#define GAMETOWER_INTERFACE_H


#include <ctime>

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <random>


using std::cout, std::cin, std::endl, std::ifstream, std::string;


namespace PosControl {

    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    // 窗口长宽
    struct Size {
        int width;
        int height;
    } size = {1200, 860};

    void centerWindow() {
        HWND hwnd = GetForegroundWindow();
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, size.width, size.height, 1);
        MoveWindow(hwnd, (screen_width - size.width) / 2, (screen_height - size.height) / 2, size.width, size.height,
                   1);
    }

// 回到坐标位置，坐标需要给定
    void setPos(int x, int y) {
        COORD coord{static_cast<SHORT>(y), static_cast<SHORT>(x)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  //回到给定的坐标位置进行重新输出
    }


// 获取当前标准输出流位置
    void getPos(int &x, int &y) {
        CONSOLE_SCREEN_BUFFER_INFO b;           // 包含控制台屏幕缓冲区的信息
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &b);    //  获取标准输出句柄
        y = b.dwCursorPosition.X;
        x = b.dwCursorPosition.Y;
    }


    void HideCursor() {
        CONSOLE_CURSOR_INFO cursor;
        cursor.bVisible = FALSE;
        cursor.dwSize = sizeof(cursor);
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorInfo(handle, &cursor);
    }
}

struct Menu {
    string name;
};

int randInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void printMsg(const string& msgDir, bool singleLine = false, bool noCD = false) {
    if (!singleLine) {
        cout << "按下 ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << "[Tab键] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "跳过本段..." << endl << endl;
    }
    ifstream msgFile(msgDir);
    string msg;
    int x, y;
    if (singleLine) {
        PosControl::getPos(x, y);
    }
    int x1 = x, y1 = y;
    while (getline(msgFile, msg)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        if (singleLine) {
            PosControl::setPos(x, y);
            for (int i = x; i <= x1; i++) {
                cout << "\33[2K" << endl;
            }
            PosControl::setPos(x, y);
        }
        bool flagTab = false;
        for (char c: msg) {

            if (c == '(') // set color to grey
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            else if (c == ')') {// set color to white
                cout << c;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                continue;
            }
            cout << c;
            if (!flagTab) Sleep(5);
            if (!noCD && kbhit()) {

                c = getch();
                if (c == '\t') {
                    flagTab = true;
                }
            }
        }
        if (singleLine) {
            cout << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            system("pause");
        }
        Sleep(100);
        PosControl::getPos(x1, y1);
        cout << endl;
    }
    msgFile.close();
}

void welcomePage() {

    PosControl::centerWindow();
    PosControl::HideCursor();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "|-----------------------------------------------------------------------------------------------------|"
//    cout << "======================================================================================================="
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << endl << "请使用 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "[Ctrl] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "+ ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "滚轮 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "调整控制台字体大小，使得以上分割线显示在同一行。"
         << endl;
    cout << endl << "按下 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "[Enter键] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "请继续..." << endl;
    while (true) {
        if (kbhit()) {
            char c;
            c = getch();
            if (c == '\r' || c == '\n') {
                PosControl::setPos(0, 0);
                cout << string(104, ' ')
                     << endl;
                cout << string(104, ' ')
                     << endl;
                cout << string(104, ' ')
                     << endl;
                cout << string(104, ' ')
                     << endl;
                cout << string(104, ' ')
                     << endl;
                PosControl::setPos(0, 0);
                break;
            }
        }
    }

    printMsg("./Assets/.welcomePage");

    cout << endl << endl;
    for (int i = 0; i < 103; i++) {
//        Sleep(5);
        cout << "=";
    }
    cout << endl << endl;

    int x, y;
    PosControl::getPos(x, y);
    int spaceLength = std::max((PosControl::size.width / 10 - 88) / 2 + 2, 0);
    string space(spaceLength, ' ');
    while (true) {
        PosControl::setPos(x, y);
        ifstream logoFile("./Assets/Logo/.logo");
        string logo;
        while (getline(logoFile, logo)) {
            int color = randInt(1, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            Sleep(50);
            cout << space << logo << endl;
        }
        logoFile.close();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << endl << "按下 ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << "[Enter键] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "继续..." << endl;

        if (kbhit()) {
            char c;
            c = getch();
            if (c == '\r' || c == '\n') {
                PosControl::setPos(x + 12, 0);
                break;
            }
        }
    }
}

int switcher(Menu menu[], int length) {

    int x, y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "请使用";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << " [W] [S] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "或";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << " [↑] [↓] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "选择，按";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << " [Enter键] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "确认" << endl << endl;

    PosControl::getPos(x, y);
    PosControl::setPos(x, 0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

    for (int i = 0; i < length; i++) {
        cout << "    > " << menu[i].name << endl;
    }
    cout << endl;
    cout << "======================================================================================================="
         << endl;

    char c;
    int choice = 0;
    int prevChoice = 0;

    while (true) {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        PosControl::setPos(x + prevChoice, y);
        cout << "    > " << menu[prevChoice].name;

        PosControl::setPos(x + choice, y);
        // [43;37m是黄底白字

        cout << "    ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
                                                                 FOREGROUND_GREEN | FOREGROUND_BLUE |
                                                                 BACKGROUND_RED | BACKGROUND_GREEN);
        cout << "> " << menu[choice].name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        c = getch();
        switch (c) {
            case 'w':
            case 'W':
            case 72: // 72是上箭头
                prevChoice = choice;
                choice = (choice + length - 1) % length;
                break;
            case 's':
            case 'S':
            case 80: // 80是下箭头
                prevChoice = choice;
                choice = (choice + 1) % length;
                break;
            case '\r':
            case '\n':
                return choice;
            default:
                prevChoice = choice;
                break;
        }
    }
}

void goodbye() {
    system("cls");
    ifstream creditsLogoFile("./Assets/Logo/.credit_logo");
    string logo;
    while (getline(creditsLogoFile, logo)) {
        cout << logo << endl;
        Sleep(randInt(20, 50));
    }
    creditsLogoFile.close();
    ifstream creditsFile("./Assets/Logo/.credit");
    string credits;
    while (getline(creditsFile, credits)) {
        cout << credits << endl;
        Sleep(randInt(20, 50));
    }
    creditsFile.close();
}


#endif //GAMETOWER_INTERFACE_H
