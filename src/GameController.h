//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_DATA_H
#define GAMETOWER_DATA_H

#include <iostream>
#include <fstream>
#include "Map.h"
#include "Player.h"
#include "run.h"

// 检查指定名称的数据文件是否存在

class Game{
private:
    Player& player;

public:
    Game(Player& player):player(player){}

    bool dataExist(const string &name) {
        string fileName = name + ".dat";  // 构造数据文件的名称
        std::ifstream dataFile("./save/"+fileName);  // 尝试打开文件
        bool isOpen = dataFile.is_open();  // 检查文件是否成功打开
        dataFile.close();  // 关闭文件
        return isOpen;  // 返回文件是否存在
    }

// 保存玩家数据到文件
    void saveData() {
        // 创建数据文件，如果文件已存在则覆盖
        std::ofstream dataFile("./save/"+player.getName() + ".dat", std::ios::trunc);
        // 保存玩家的主要属性
        dataFile << player.getHP() << ' ' << player.getName() << " " <<player.getLevel() << endl;
        // 保存玩家的位置
        dataFile << player.getPos().line << ' ' << player.getPos().column << endl;
        // 保存玩家的背包内容
        dataFile << "Backpack" << endl;
        player.getBackpack().showItemList(dataFile);

        //player.showWordList(dataFile);
        // 保存玩家的地图进度
        dataFile << "Map" << endl;
        dataFile << player.getMap().getProgress() << endl;
        player.getMap().showMap(dataFile);
    }

// 加载玩家数据
    void loadData() {
        if (dataExist(player.getName())) {  // 如果数据文件存在
            std::ifstream dataFile("./save/"+player.getName() + ".dat");  // 打开文件
            // 加载玩家的主要属性
            int hp, level;
            string name;
            dataFile >> hp >> name >> level;
            player.setHP(hp);
            player.resetCurrHP();
            player.setName(name);
            player.setLevel(level);
            // 加载玩家的位置
            int line, column;
            dataFile >> line >> column;
            player.setPos(line, column);
            // 加载玩家的背包内容
            string type;
            dataFile >> type;
            if (type == "Backpack") {
                string itemName;
                while (dataFile >> itemName) {
                    if (itemName == "#") {
                        break;
                    }
                    int effect, cooldown, num;
                    dataFile >> effect >> cooldown >> num;
                    player.getBackpack().loadItemList(itemName, effect, cooldown, num);
                }
            }
            dataFile.clear();
//            if (type == "WordList") {
//                int length;
//                string word;
//                int effect;
//                while (dataFile >> length) {
//                    if (length == 0) {
//                        break;
//                    }
//                    dataFile >> word >> effect;
//                    player.loadWordList(length, word, effect);
//                }
//            }
            dataFile.clear();
            dataFile >> type;
            if (type == "Map") {
                int progress;
                dataFile >> progress;
                player.getMap().setProgress(progress);
                player.getMap().loadMap(dataFile);
            }
        } else {  // 如果数据文件不存在
            system("cls");
            cout << "数据不存在，创建新存档" << endl;
            saveData();  // 保存初始数据
            system("pause");
        }
    }

// 开始新游戏
    void newGame() {
        system("cls");
        if (dataExist(player.getName())) {
            // if data exists, ask for loading
            cout << "数据已存在，是否读取？" << endl;
            Menu menu[2]{"是","否"};
            switch (switcher(menu, 2)) {
                case 0:
                    break;
                case 1:
                    player.getBackpack().progress0();
                    player.setLevel(1);
//                    player.playerWordlist(player.getMap().getProgress() + 1);
                    saveData();
            }
        } else {
            player.getBackpack().progress0();
            player.setLevel(1);
//            player.playerWordlist(player.getMap().getProgress() + 1);
            saveData();
        }
        system("cls");
        loadGame();
    }

// 加载游戏
    void loadGame() {
        loadData();  // 加载玩家数据
        Map::printMap();  // 打印地图
        run(player);  // 处理地图上的行为
        saveData();  // 保存玩家数据
        goodbye();  // 显示游戏结束页面
        system("pause");  // 暂停，等待用户操作
    }

//    void run();
};



#endif //GAMETOWER_DATA_H
