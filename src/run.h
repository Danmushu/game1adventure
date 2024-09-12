
#ifndef GAMETOWER_BEHAVIOR_H
#define GAMETOWER_BEHAVIOR_H
// ����꣬�����жϵ�ͼ(x, y)λ���Ƿ�ɽ���
#define ifAccessible(x, y) dynamic_cast<Road*>(map.getLocation(x,y))->getIsAccessible()

// ����꣬���ڻ�ȡ��ͼ(x, y)λ�õĵص�����
#define getPlaceName(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getName()

// ����꣬�����ն˹���ƶ���(x, y)λ�õ�ת������
#define gotoPlace(x, y) "\33["<<(dynamic_cast<Place*>(map.getLocation(x, y))->getX())<<";"<<(dynamic_cast<Place*>(map.getLocation(x, y))->getY())<<"H"

// ����꣬�����жϵ�ͼ(x, y)λ���Ƿ�Ϊ�ϰ���ǵ�·�ҷǵص㣩
#define isBarrier(x, y) !(map.getLocation(x,y)->isRoad() || map.getLocation(x,y)->isPlace())

// ����꣬���ڻ�ȡ��ͼ(x, y)λ�õ������Ƿ������
#define getHasDone(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getHasDone()

// ����꣬�����жϵ�ͼ(x, y)λ�õĵص��Ƿ�����
#define getIsLocked(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getIsLocked()

#include <iostream>
#include <memory>
#include "Player.h"
#include "Interface.h"
#include "Map.h"
#include "Fight.h"

using std::cout, std::endl;

void run(Player &player) {
    // ��ȡ��ҵ�ǰ����һ�ε�λ���Լ���ͼ����
    MapPosition &pos = player.getPos();
    MapPosition &lastPos = player.getLastPos();
    Map &map = player.getMap();
    char c;

    // ����ѭ���ȴ��������
    while (true) {
        // ���µ�ͼ����
        map.setProgress(map.getProgress());

        // ��ӡ��ҵ�ǰ״̬
        player.printStatus();

        // ���һЩ�ն���ʾ���ݣ�ˢ�£�
        cout << "\33[2;10H                    \33[0m";
        cout << "\33[2;0H��ǰλ�ã�" << getPlaceName(pos.line, pos.column) << endl;

        // �����ն�������ɫΪ��ɫ������14��
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

        // ����һ��λ����ʾ�ص�����
        cout << gotoPlace(lastPos.line, lastPos.column) << getPlaceName(lastPos.line, lastPos.column) << "\33[0m";

        // �ڵ�ǰλ����ʾ�ص����Ʋ����
        cout << gotoPlace(pos.line, pos.column) << "\33[43;37m" << getPlaceName(pos.line, pos.column) << "\33[0m";

        // ��ȡ�û�����
        c = getch();

        switch (c) {
            // ����'w'�������ƶ�
            case 'w':
            case 'W':
            case 72: {
                pos.line--; // ��ͼ�����ƶ�

                // �����λ���Ƿ��ںϷ���Χ��
                if (pos.line > 0 && pos.line < 9) {
                    if (isBarrier(pos.line, pos.column)) { // ����λ�����ϰ��ȡ���ƶ�
                        pos.line++;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // ����λ�ÿɽ��룬�����λ��
                        lastPos.line = pos.line + 1;
                        lastPos.column = pos.column;
                        pos.line--;
                    } else {
                        pos.line++; // �����ɽ��룬�ָ�ԭλ
                    }
                } else {
                    pos.line++; // ��������Χ���ָ�ԭλ
                }
                break;
            }
                // ����'a'�������ƶ�
            case 'a':
            case 'A':
            case 75: {
                pos.column--; // ��ͼ�����ƶ�

                if (pos.column > 0 && pos.column < 9) {
                    if (isBarrier(pos.line, pos.column)) { // ����λ�����ϰ��ȡ���ƶ�
                        pos.column++;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // ����λ�ÿɽ��룬�����λ��
                        lastPos.column = pos.column + 1;
                        lastPos.line = pos.line;
                        pos.column--;
                    } else {
                        pos.column++; // �����ɽ��룬�ָ�ԭλ
                    }
                } else {
                    pos.column++; // ��������Χ���ָ�ԭλ
                }
                break;
            }
                // ����'s'�������ƶ�
            case 's':
            case 'S':
            case 80: {
                pos.line++; // ��ͼ�����ƶ�

                if (pos.line < 9 && pos.line > 0) {
                    if (isBarrier(pos.line, pos.column)) { // ����λ�����ϰ��ȡ���ƶ�
                        pos.line--;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // ����λ�ÿɽ��룬�����λ��
                        lastPos.line = pos.line - 1;
                        lastPos.column = pos.column;
                        pos.line++;
                    } else {
                        pos.line--; // �����ɽ��룬�ָ�ԭλ
                    }
                } else {
                    pos.line--; // ��������Χ���ָ�ԭλ
                }
                break;
            }
                // ����'d'�������ƶ�
            case 'd':
            case 'D':
            case 77: {
                pos.column++; // ��ͼ�����ƶ�

                if (pos.column < 9 && pos.column > 0) {
                    if (isBarrier(pos.line, pos.column)) { // ����λ�����ϰ��ȡ���ƶ�
                        pos.column--;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // ����λ�ÿɽ��룬�����λ��
                        lastPos.column = pos.column - 1;
                        lastPos.line = pos.line;
                        pos.column++;
                    } else {
                        pos.column--; // �����ɽ��룬�ָ�ԭλ
                    }
                } else {
                    pos.column--; // ��������Χ���ָ�ԭλ
                }
                break;
            }
                // ����'q'���˳���ǰ��ͼ
            case 'q':
            case 'Q': {
                return;
            }
                // ����F5�����´�ӡ��ͼ
            case 63: {
                Map::printMap();
                break;
            }
                // ����'b'���򿪱���
            case 'b':
            case 'B': {
                system("cls"); // ����
                player.getBackpack().printItemList(false); // ��ӡ��������
                system("pause");
                Map::printMap(); // ���´�ӡ��ͼ
                break;
            }
                // ����'e'���鿴������Ϣ
            case 'e':
            case 'E': {
                system("cls"); // ����
                Interface::printMsg("./assets/.help"); // ��ӡ������Ϣ
                system("pause");
                Map::printMap(); // ���´�ӡ��ͼ
                break;
            }
                // ����'n'���鿴��������
            case 'u':
            case 'U': {
                system("cls"); // ����
                Interface::printMsg("./assets/Enemies/.enemyDescription"); // ��ӡ��������
                system("pause");
                Map::printMap(); // ���´�ӡ��ͼ
                break;
            }
                // ����'�س�'�������ص��¼�
            case '\r':
            case '\n': {
                system("cls"); // ����

                // ��鵱ǰλ���Ƿ�����
                if (getIsLocked(pos.line, pos.column)) {
                    // ���ݵ�ͼ������ʾ��ͬ������
                    if (map.getProgress() < 3 && pos.line == 6 && pos.column == 2) {//�ؾ��ռ�в�
                        Interface::printMsg("./assets/Scene/Other/locked.txt");
                    } else if (map.getProgress() == 4 || map.getProgress() == 5) {
                        Interface::printMsg("./assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                    } else {
                        Interface::printMsg(map.getDefaultMsgDir());
                    }
                    system("pause");
                } else {
                    // ����������ɣ���ʾĬ�ϳ���
                    if (getHasDone(pos.line, pos.column)) {
                        Interface::printMsg("./assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                        system("pause");
                    } else {
                        // ���ݽ��ȴ�����ͬ�ĳ�����ս��
                        if (map.getProgress() == 2 && pos.line == 6 && pos.column == 4) {// �����
                            Interface::printMsg("./assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                            system("pause");
                            system("cls");
                            lastPos = {6, 4}; // �����
                            pos = {4, 4}; // �ؾ�����
                            Interface::printMsg("./assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() == 2 && pos.line == 4 && pos.column == 4) {// �ؾ�����
                            lastPos = {6, 4};// �����
                            pos = {6, 4};// �����
                            Interface::printMsg("./assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                            system("pause");
                            system("cls");
                            pos = {4, 4};// �ؾ�����
                            Interface::printMsg("./assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() == 3 && pos.line != 2 && pos.column != 4) {// �ؾ�����
                            Interface::printMsg("./assets/Scene/Other/Faith.txt");
                        } else if (map.getProgress() >= 4 && pos.line == 6 && pos.column == 4) {// �����
                            if (getIsLocked(0, 4)) // �ؾ�����
                                Interface::printMsg("./assets/Scene/Other/Final.txt");
                            else Interface::printMsg("./assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() < 4 && pos.line == 0 && pos.column == 4) {// �ؾ�����
                            Interface::printMsg("./assets/Scene/Other/check.txt");
                        } else Interface::printMsg("./assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        system("pause");

                        // �ض�����ƽ���״̬����
                        if (map.getProgress() == 4 && pos.line == 6 && pos.column == 2 && !getHasDone(6, 2)) {
                            player.getBackpack().progress4();// �ؾ��ռ�в�
                            dynamic_cast<Place *>(map.getLocation(6, 2))->setHasDone(true);// �ؾ��ռ�в�
                            dynamic_cast<Place *>(map.getLocation(0, 4))->setIsLocked(true);// �ؾ�����
                            dynamic_cast<Place *>(map.getLocation(6, 4))->setIsLocked(true);// �����
                        }

                        // �ж��Ƿ����ս������
                        if ((pos.line == 6 && pos.column == 2) || (pos.line == 6 && pos.column == 4)) {
                            // �ض��������������ս������ // �ؾ��ռ�в� // �����λ��
                        } else { // ����ս������
                            Backpack backupBackpack = player.getBackpack();
                            int backupCurrHP = player.getCurrHP();

                            // ����ս������
                            shared_ptr<Fight> curFight(new Fight(getPlaceName(pos.line, pos.column), map.getProgress())); //= new Fight(getPlaceName(pos.line, pos.column), map.getProgress());

//                            auto *currFightScene = new Fight(getPlaceName(pos.line, pos.column), map.getProgress());
//                            currFightScene->loadScene(player); // ���س���
                            curFight->loadScene(player);

                            // ���ս�����
                            if (Fight::checkWin(player)) {
                                system("cls");
                                int level = player.getLevel();
                                level++;
                                player.setLevel(level);
                                map.setHasDone(pos.line, pos.column); // �����������״̬
                                cout << "��";
                                Interface::printMsg("./assets/Scene/Other/victory.txt");
                                system("cls");
                                cout << "��";
                                Interface::printMsg("./assets/Scene/AfterFight/" + getPlaceName(pos.line, pos.column) + ".txt");
                                system("pause");
                            } else {
                                system("cls");
                                Interface::printMsg("./assets/Scene/Other/Failed.txt");
                                player.setCurrHP(backupCurrHP); // �ָ����״̬
                                player.setBackpack(backupBackpack);

                                system("pause");
                            }
                            //delete currFightScene; // �ͷ��ڴ�
                        }
                    }
                }
                Map::printMap(); // ���´�ӡ��ͼ
                break;
            }
            default:
                break;
        }
    }
}

#endif //GAMETOWER_BEHAVIOR_H
