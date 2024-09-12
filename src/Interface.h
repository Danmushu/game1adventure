
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


namespace Interface {

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
        MoveWindow(hwnd, (screen_width - size.width) / 2, (screen_height - size.height) / 2, size.width, size.height, 1);
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

    struct Menu {
        string name;
    };

    int randInt(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    void printMsg(const string &msgDir, bool singleLine = false, bool noCD = false) {
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
            Interface::getPos(x, y);
        }
        int x1 = x, y1 = y;
        while (getline(msgFile, msg)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            if (singleLine) {
                Interface::setPos(x, y);
                for (int i = x; i <= x1; i++) {
                    cout << "\33[2K" << endl;
                }
                Interface::setPos(x, y);
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
            Interface::getPos(x1, y1);
            cout << endl;
        }
        msgFile.close();
    }

    void showLogo() {
        int x, y; // 定义两个整型变量x和y，用于存储光标的位置
        Interface::getPos(x, y); // 调用Interface类的getPos方法获取当前光标的位置，并存储到x和y
        int spaceLength = std::max((Interface::size.width / 10 - 88) / 2 + 2, 0); // 计算空格的长度，使其在控制台中居中显示Logo
        string space(spaceLength, ' '); // 创建一个由空格字符组成的字符串，长度为上面计算的空格长度
        while (true) { // 一个无限循环，用于持续显示Logo直到用户按下Enter键
            Interface::setPos(x, y); // 将光标移动到初始位置
            ifstream logoFile("./assets/Logo/.logo"); // 打开Logo文件
            string logo; // 定义一个字符串变量logo，用于存储每一行的Logo文本
            while (getline(logoFile, logo)) { // 读取Logo文件的每一行，直到文件结束
                int color = randInt(1, 15); // 随机生成一个颜色值，范围从1到15
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // 设置控制台文本的颜色
                Sleep(50); // 等待50毫秒，用于控制Logo显示的速度
                cout << space << logo << endl; // 输出空格和Logo文本
            }
            logoFile.close(); // 关闭Logo文件
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // 重置控制台文本颜色为默认颜色（亮灰色）
            cout << endl << "按下 "; // 输出提示信息，告诉用户按下Enter键继续
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // 设置控制台文本颜色
            cout << "[Enter键] "; // 提示用户按下Enter键
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // 重置控制台文本颜色
            cout << "继续..." << endl; // 输出继续提示信息

            if (kbhit()) { // 检查是否有按键输入
                char c; // 定义一个字符变量c，用于存储按键值
                c = getch(); // 读取按键
                if (c == '\r' || c == '\n') { // 如果按下的是Enter键（\r是回车，\n是换行），则退出循环
                    Interface::setPos(x + 12, 0); // 将光标移动到指定位置，通常是为了清空提示信息
                    break; // 退出循环
                }
            }
        }
    }

    void welcomePage() {
        Interface::centerWindow();
        Interface::HideCursor();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout
                << "|-----------------------------------------------------------------------------------------------------|"
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
                    Interface::setPos(0, 0);
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
                    Interface::setPos(0, 0);
                    break;
                }
            }
        }

        printMsg("./assets/.welcomePage");

        cout << endl << endl;
        for (int i = 0; i < 103; i++) {
            Sleep(5);
            cout << "=";
        }
        cout << endl << endl;

        //展示logo
        showLogo();
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

        Interface::getPos(x, y);
        Interface::setPos(x, 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

        for (int i = 0; i < length; i++) {
            cout << "    > " << menu[i].name << endl;
        }
        cout << endl;
        cout
                << "======================================================================================================="
                << endl;

        char c;
        int choice = 0;
        int prevChoice = 0;

        while (true) {

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            Interface::setPos(x + prevChoice, y);
            cout << "    > " << menu[prevChoice].name;

            Interface::setPos(x + choice, y);
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
        ifstream creditsLogoFile("./assets/Logo/.credit_logo");
        string logo;
        while (getline(creditsLogoFile, logo)) {
            cout << logo << endl;
            Sleep(randInt(20, 50));
        }
        creditsLogoFile.close();
        ifstream creditsFile("./assets/Logo/.credit");
        string credits;
        while (getline(creditsFile, credits)) {
            cout << credits << endl;
            Sleep(randInt(20, 50));
        }
        creditsFile.close();
    }

}
#endif //GAMETOWER_INTERFACE_H
