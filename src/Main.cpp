//
// Created by Jiarong on 2023/8/21.
//

// A MUD Game

#define NOMINMAX  // ��ֹ Windows.h ͷ�ļ����� min �� max �꣬�������׼���е� std::min/std::max ��ͻ

#include <iostream>  // �ṩ��׼�����������
#include <csignal>  // �ṩ�źŴ�����
#include "Interface.h"  // ������Ϸ������صĺ�������
#include "GameController.h"  // ������Ϸ������ص���ͺ���

using std::cout, std::cin, std::endl, std::ifstream, std::string;

void checkValidation(string name, int x) {
    // ��֤�������������Ƿ�Ϸ�
    while (name.length() > 15 || name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != string::npos) {
        // ������ֲ��Ϸ����������ù�겢��ʾ�����������
        PosControl::setPos(x, 0);
        // �����ǰ������
        cout << "\33[2K" << endl;
        // ��������Ƿ�����Ƿ��ַ������ֳ����Ƿ񳬹�15���ַ�
        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != string::npos) {
            // ��������Ƿ��ַ�����ʾ�����������Ϸ�����
            cout << "�����к��зǷ��ַ������������룺";
        } else {
            // ������ֹ�������ʾ������������һ�������
            cout << "���ֹ��������������룺";
        }
        cin >> name;  // ���»�ȡ������������
    }
    // ���������ʾ��
    PosControl::setPos(x, 0);
}

void helloPlayer(const string& name){
    // ����Ҵ��к�����ʾ������
    cout << "    ��ã���Ϊ ";
    // ��������ɫ����Ϊ��ɫ
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << name;
    // �ָ�������ɫΪĬ��ֵ����ɫ��
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << " �ĵ��ѣ�" << endl;

    // ������п��У��Ӿ��������������
    string spaceLine(100, ' ');

    cout << spaceLine << endl << spaceLine << endl;
}

int main() {
    //setDPI();  // �����Ҫ���������� DPI ���ţ���ʱע�͵�
    PosControl::centerWindow();
    PosControl::HideCursor();
    Player player1("123");
    Game game1(player1);
    game1.newGame();
    return 0;
    // ��ʾ��ӭҳ��
    welcomePage();

    int x, y;  // ���ڴ洢���λ�õı���
    string name;  // �洢������������

    // ��ȡ��ǰ���λ��
    PosControl::getPos(x, y);
    // ���ù��λ�õ���ǰ�е���ʼλ��
    PosControl::setPos(x, 0);
    // �����ǰ�е�����
    cout << "\33[2K";
    // ��ʾ�����������
    cout << "������������մ�����";
    cin >> name;
    checkValidation(name, x);
    helloPlayer(name);
    Player player(name);
    Game game(player);
    // ������Ϸ���˵���ѡ��
    Menu menu[3]{
            "����Ϸ",  // ����Ϸѡ��
            "������Ϸ",  // ������Ϸѡ��
            "�˳���Ϸ"  // �˳���Ϸѡ��
    };

    // ���� switcher ������ʾ���˵������������ѡ��ִ����Ӧ�Ĳ���
    switch (switcher(menu, 3)) {
        case 0:
            // ������ѡ���ˡ�����Ϸ��������������Ϸ
            game.newGame();
            break;
        case 1:
            // ������ѡ���ˡ�������Ϸ�����������Ϸ����
            game.loadGame();
            break;
        case 2:
            // ������ѡ���ˡ��˳���Ϸ��������ʾ�˳�ҳ�棬���˳�����
            goodbye();
            system("pause");  // ��ͣ�ȴ��û�����
            return 0;  // �˳�����
    }

    return 0;  // ������������
}

