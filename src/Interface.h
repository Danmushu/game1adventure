
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

    // ���ڳ���
    struct Size {
        int width;
        int height;
    } size = {1200, 860};

    void centerWindow() {
        HWND hwnd = GetForegroundWindow();
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, size.width, size.height, 1);
        MoveWindow(hwnd, (screen_width - size.width) / 2, (screen_height - size.height) / 2, size.width, size.height, 1);
    }

    // �ص�����λ�ã�������Ҫ����
    void setPos(int x, int y) {
        COORD coord{static_cast<SHORT>(y), static_cast<SHORT>(x)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  //�ص�����������λ�ý����������
    }

    // ��ȡ��ǰ��׼�����λ��
    void getPos(int &x, int &y) {
        CONSOLE_SCREEN_BUFFER_INFO b;           // ��������̨��Ļ����������Ϣ
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &b);    //  ��ȡ��׼������
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
            cout << "���� ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            cout << "[Tab��] ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            cout << "��������..." << endl << endl;
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
        int x, y; // �����������ͱ���x��y�����ڴ洢����λ��
        Interface::getPos(x, y); // ����Interface���getPos������ȡ��ǰ����λ�ã����洢��x��y
        int spaceLength = std::max((Interface::size.width / 10 - 88) / 2 + 2, 0); // ����ո�ĳ��ȣ�ʹ���ڿ���̨�о�����ʾLogo
        string space(spaceLength, ' '); // ����һ���ɿո��ַ���ɵ��ַ���������Ϊ�������Ŀո񳤶�
        while (true) { // һ������ѭ�������ڳ�����ʾLogoֱ���û�����Enter��
            Interface::setPos(x, y); // ������ƶ�����ʼλ��
            ifstream logoFile("./assets/Logo/.logo"); // ��Logo�ļ�
            string logo; // ����һ���ַ�������logo�����ڴ洢ÿһ�е�Logo�ı�
            while (getline(logoFile, logo)) { // ��ȡLogo�ļ���ÿһ�У�ֱ���ļ�����
                int color = randInt(1, 15); // �������һ����ɫֵ����Χ��1��15
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // ���ÿ���̨�ı�����ɫ
                Sleep(50); // �ȴ�50���룬���ڿ���Logo��ʾ���ٶ�
                cout << space << logo << endl; // ����ո��Logo�ı�
            }
            logoFile.close(); // �ر�Logo�ļ�
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // ���ÿ���̨�ı���ɫΪĬ����ɫ������ɫ��
            cout << endl << "���� "; // �����ʾ��Ϣ�������û�����Enter������
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // ���ÿ���̨�ı���ɫ
            cout << "[Enter��] "; // ��ʾ�û�����Enter��
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // ���ÿ���̨�ı���ɫ
            cout << "����..." << endl; // ���������ʾ��Ϣ

            if (kbhit()) { // ����Ƿ��а�������
                char c; // ����һ���ַ�����c�����ڴ洢����ֵ
                c = getch(); // ��ȡ����
                if (c == '\r' || c == '\n') { // ������µ���Enter����\r�ǻس���\n�ǻ��У������˳�ѭ��
                    Interface::setPos(x + 12, 0); // ������ƶ���ָ��λ�ã�ͨ����Ϊ�������ʾ��Ϣ
                    break; // �˳�ѭ��
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
        cout << endl << "��ʹ�� ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << "[Ctrl] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "+ ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << "���� ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "��������̨�����С��ʹ�����Ϸָ�����ʾ��ͬһ�С�"
             << endl;
        cout << endl << "���� ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << "[Enter��] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "�����..." << endl;
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

        //չʾlogo
        showLogo();
    }


    int switcher(Menu menu[], int length) {
        int x, y;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "��ʹ��";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << " [W] [S] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "��";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << " [��] [��] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "ѡ�񣬰�";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << " [Enter��] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "ȷ��" << endl << endl;

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
            // [43;37m�ǻƵװ���

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
                case 72: // 72���ϼ�ͷ
                    prevChoice = choice;
                    choice = (choice + length - 1) % length;
                    break;
                case 's':
                case 'S':
                case 80: // 80���¼�ͷ
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
