
#ifndef GAMETOWER_BEHAVIOR_H
#define GAMETOWER_BEHAVIOR_H
// 定义宏，用于判断地图(x, y)位置是否可进入
#define ifAccessible(x, y) dynamic_cast<Road*>(map.getLocation(x,y))->getIsAccessible()

// 定义宏，用于获取地图(x, y)位置的地点名称
#define getPlaceName(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getName()

// 定义宏，生成终端光标移动到(x, y)位置的转义序列
#define gotoPlace(x, y) "\33["<<(dynamic_cast<Place*>(map.getLocation(x, y))->getX())<<";"<<(dynamic_cast<Place*>(map.getLocation(x, y))->getY())<<"H"

// 定义宏，用于判断地图(x, y)位置是否为障碍物（非道路且非地点）
#define isBarrier(x, y) !(map.getLocation(x,y)->isRoad() || map.getLocation(x,y)->isPlace())

// 定义宏，用于获取地图(x, y)位置的任务是否已完成
#define getHasDone(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getHasDone()

// 定义宏，用于判断地图(x, y)位置的地点是否被锁定
#define getIsLocked(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getIsLocked()

#include <iostream>
#include "Player.h"
#include "Interface.h"
#include "Map.h"
#include "Fight.h"

using std::cout, std::endl;

void run(Player &player) {
    // 获取玩家当前和上一次的位置以及地图对象
    MapPosition &pos = player.getPos();
    MapPosition &lastPos = player.getLastPos();
    Map &map = player.getMap();
    char c;

    // 无限循环等待玩家输入
    while (true) {
        // 更新地图进度
        map.setProgress(map.getProgress());

        // 打印玩家当前状态
        player.printStatus();

        // 清空一些终端显示内容（刷新）
        cout << "\33[2;10H                    \33[0m";
        cout << "\33[2;0H当前位置：" << getPlaceName(pos.line, pos.column) << endl;

        // 设置终端文字颜色为黄色（代码14）
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

        // 在上一个位置显示地点名称
        cout << gotoPlace(lastPos.line, lastPos.column) << getPlaceName(lastPos.line, lastPos.column) << "\33[0m";

        // 在当前位置显示地点名称并标黄
        cout << gotoPlace(pos.line, pos.column) << "\33[43;37m" << getPlaceName(pos.line, pos.column) << "\33[0m";

        // 获取用户输入
        c = getch();

        switch (c) {
            // 按键'w'，向上移动
            case 'w':
            case 'W':
            case 72: {
                pos.line--; // 试图向上移动

                // 检查新位置是否在合法范围内
                if (pos.line > 0 && pos.line < 9) {
                    if (isBarrier(pos.line, pos.column)) { // 若新位置是障碍物，取消移动
                        pos.line++;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // 若新位置可进入，则更新位置
                        lastPos.line = pos.line + 1;
                        lastPos.column = pos.column;
                        pos.line--;
                    } else {
                        pos.line++; // 若不可进入，恢复原位
                    }
                } else {
                    pos.line++; // 若超出范围，恢复原位
                }
                break;
            }
                // 按键'a'，向左移动
            case 'a':
            case 'A':
            case 75: {
                pos.column--; // 试图向左移动

                if (pos.column > 0 && pos.column < 9) {
                    if (isBarrier(pos.line, pos.column)) { // 若新位置是障碍物，取消移动
                        pos.column++;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // 若新位置可进入，则更新位置
                        lastPos.column = pos.column + 1;
                        lastPos.line = pos.line;
                        pos.column--;
                    } else {
                        pos.column++; // 若不可进入，恢复原位
                    }
                } else {
                    pos.column++; // 若超出范围，恢复原位
                }
                break;
            }
                // 按键's'，向下移动
            case 's':
            case 'S':
            case 80: {
                pos.line++; // 试图向下移动

                if (pos.line < 9 && pos.line > 0) {
                    if (isBarrier(pos.line, pos.column)) { // 若新位置是障碍物，取消移动
                        pos.line--;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // 若新位置可进入，则更新位置
                        lastPos.line = pos.line - 1;
                        lastPos.column = pos.column;
                        pos.line++;
                    } else {
                        pos.line--; // 若不可进入，恢复原位
                    }
                } else {
                    pos.line--; // 若超出范围，恢复原位
                }
                break;
            }
                // 按键'd'，向右移动
            case 'd':
            case 'D':
            case 77: {
                pos.column++; // 试图向右移动

                if (pos.column < 9 && pos.column > 0) {
                    if (isBarrier(pos.line, pos.column)) { // 若新位置是障碍物，取消移动
                        pos.column--;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) { // 若新位置可进入，则更新位置
                        lastPos.column = pos.column - 1;
                        lastPos.line = pos.line;
                        pos.column++;
                    } else {
                        pos.column--; // 若不可进入，恢复原位
                    }
                } else {
                    pos.column--; // 若超出范围，恢复原位
                }
                break;
            }
                // 按键'q'，退出当前地图
            case 'q':
            case 'Q': {
                return;
            }
                // 按键F5，重新打印地图
            case 63: {
                Map::printMap();
                break;
            }
                // 按键'b'，打开背包
            case 'b':
            case 'B': {
                system("cls"); // 清屏
                player.getBackpack().printItemList(false); // 打印背包内容
                system("pause");
                Map::printMap(); // 重新打印地图
                break;
            }
                // 按键'e'，查看帮助信息
            case 'e':
            case 'E': {
                system("cls"); // 清屏
                printMsg("./Assets/.help"); // 打印帮助信息
                system("pause");
                Map::printMap(); // 重新打印地图
                break;
            }
                // 按键'n'，查看怪物描述
            case 'u':
            case 'U': {
                system("cls"); // 清屏
                printMsg("./Assets/Enemies/.enemyDescription"); // 打印怪物描述
                system("pause");
                Map::printMap(); // 重新打印地图
                break;
            }
                // 按键'回车'，触发地点事件
            case '\r':
            case '\n': {
                system("cls"); // 清屏

                // 检查当前位置是否被锁定
                if (getIsLocked(pos.line, pos.column)) {
                    // 根据地图进度显示不同的内容
                    if (map.getProgress() < 3 && pos.line == 6 && pos.column == 2) {//秘境空间夹层
                        printMsg("./Assets/Scene/Other/locked.txt");
                    } else if (map.getProgress() == 4 || map.getProgress() == 5) {
                        printMsg("./Assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                    } else {
                        printMsg(map.getDefaultMsgDir());
                    }
                    system("pause");
                } else {
                    // 若任务已完成，显示默认场景
                    if (getHasDone(pos.line, pos.column)) {
                        printMsg("./Assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                        system("pause");
                    } else {
                        // 根据进度触发不同的场景或战斗
                        if (map.getProgress() == 2 && pos.line == 6 && pos.column == 4) {// 宝光阁
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                            system("pause");
                            system("cls");
                            lastPos = {6, 4}; // 宝光阁
                            pos = {4, 4}; // 秘境二层
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() == 2 && pos.line == 4 && pos.column == 4) {// 秘境二层
                            lastPos = {6, 4};// 宝光阁
                            pos = {6, 4};// 宝光阁
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                            system("pause");
                            system("cls");
                            pos = {4, 4};// 秘境二层
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() == 3 && pos.line != 2 && pos.column != 4) {// 秘境三层
                            printMsg("./Assets/Scene/Other/Faith.txt");
                        } else if (map.getProgress() >= 4 && pos.line == 6 && pos.column == 4) {// 宝光阁
                            if (getIsLocked(0, 4)) // 秘境核心
                                printMsg("./Assets/Scene/Other/Final.txt");
                            else printMsg("./Assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() < 4 && pos.line == 0 && pos.column == 4) {// 秘境核心
                            printMsg("./Assets/Scene/Other/check.txt");
                        } else printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        system("pause");

                        // 特定情节推进和状态更新
                        if (map.getProgress() == 4 && pos.line == 6 && pos.column == 2 && !getHasDone(6, 2)) {
                            player.getBackpack().progress4();// 秘境空间夹层
                            dynamic_cast<Place *>(map.getLocation(6, 2))->setHasDone(true);// 秘境空间夹层
                            dynamic_cast<Place *>(map.getLocation(0, 4))->setIsLocked(true);// 秘境核心
                            dynamic_cast<Place *>(map.getLocation(6, 4))->setIsLocked(true);// 宝光阁
                        }

                        // 判断是否进入战斗场景
                        if ((pos.line == 6 && pos.column == 2) || (pos.line == 6 && pos.column == 4)) {
                            // 特定条件下无需进入战斗场景 // 秘境空间夹层 // 宝光阁位置
                        } else { // 进入战斗场景
                            Backpack backupBackpack = player.getBackpack();
                            int backupCurrHP = player.getCurrHP();

                            // 创建战斗场景
                            auto *currFightScene = new Fight(getPlaceName(pos.line, pos.column), map.getProgress());
                            currFightScene->loadScene(player); // 加载场景

                            // 检查战斗结果
                            if (Fight::checkWin(player)) {
                                system("cls");
                                int level = player.getLevel();
                                level++;
                                player.setLevel(level);
                                map.setHasDone(pos.line, pos.column); // 更新任务完成状态
                                cout << "我";
                                printMsg("./Assets/Scene/Other/victory.txt");
                                system("cls");
                                cout << "我";
                                printMsg("./Assets/Scene/AfterFight/" + getPlaceName(pos.line, pos.column) + ".txt");
                                system("pause");
                            } else {
                                system("cls");
                                printMsg("./Assets/Scene/Other/Failed.txt");
                                player.setCurrHP(backupCurrHP); // 恢复玩家状态
                                player.setBackpack(backupBackpack);

                                system("pause");
                            }
                            delete currFightScene; // 释放内存
                        }
                    }
                }
                Map::printMap(); // 重新打印地图
                break;
            }
            default:
                break;
        }
    }
}

#endif //GAMETOWER_BEHAVIOR_H
