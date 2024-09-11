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

// ���ָ�����Ƶ������ļ��Ƿ����

class Game{
private:
    Player& player;

public:
    Game(Player& player):player(player){}

    bool dataExist(const string &name) {
        string fileName = name + ".dat";  // ���������ļ�������
        std::ifstream dataFile("./save/"+fileName);  // ���Դ��ļ�
        bool isOpen = dataFile.is_open();  // ����ļ��Ƿ�ɹ���
        dataFile.close();  // �ر��ļ�
        return isOpen;  // �����ļ��Ƿ����
    }

// ����������ݵ��ļ�
    void saveData() {
        // ���������ļ�������ļ��Ѵ����򸲸�
        std::ofstream dataFile("./save/"+player.getName() + ".dat", std::ios::trunc);
        // ������ҵ���Ҫ����
        dataFile << player.getHP() << ' ' << player.getName() << " " <<player.getLevel() << endl;
        // ������ҵ�λ��
        dataFile << player.getPos().line << ' ' << player.getPos().column << endl;
        // ������ҵı�������
        dataFile << "Backpack" << endl;
        player.getBackpack().showItemList(dataFile);

        //player.showWordList(dataFile);
        // ������ҵĵ�ͼ����
        dataFile << "Map" << endl;
        dataFile << player.getMap().getProgress() << endl;
        player.getMap().showMap(dataFile);
    }

// �����������
    void loadData() {
        if (dataExist(player.getName())) {  // ��������ļ�����
            std::ifstream dataFile("./save/"+player.getName() + ".dat");  // ���ļ�
            // ������ҵ���Ҫ����
            int hp, level;
            string name;
            dataFile >> hp >> name >> level;
            player.setHP(hp);
            player.resetCurrHP();
            player.setName(name);
            player.setLevel(level);
            // ������ҵ�λ��
            int line, column;
            dataFile >> line >> column;
            player.setPos(line, column);
            // ������ҵı�������
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
        } else {  // ��������ļ�������
            system("cls");
            cout << "���ݲ����ڣ������´浵" << endl;
            saveData();  // �����ʼ����
            system("pause");
        }
    }

// ��ʼ����Ϸ
    void newGame() {
        system("cls");
        if (dataExist(player.getName())) {
            // if data exists, ask for loading
            cout << "�����Ѵ��ڣ��Ƿ��ȡ��" << endl;
            Menu menu[2]{"��","��"};
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

// ������Ϸ
    void loadGame() {
        loadData();  // �����������
        Map::printMap();  // ��ӡ��ͼ
        run(player);  // �����ͼ�ϵ���Ϊ
        saveData();  // �����������
        goodbye();  // ��ʾ��Ϸ����ҳ��
        system("pause");  // ��ͣ���ȴ��û�����
    }

//    void run();
};



#endif //GAMETOWER_DATA_H
