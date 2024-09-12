#ifndef GAMETOWER1_HERO_H
#define GAMETOWER1_HERO_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <sstream>
#include "Backpack.h"
#include "Bar.h"
#include "Creature.h"
#include "Map.h"
#include "Interface.h"

struct MapPosition {
    int line;
    int column;
};

//player �˺�������word.getEffect() �������������
class Player : public Creature {
public:
    Player() = default;

    explicit Player(string name);

    ~Player() override = default;

    void printStatus() const;

    MapPosition &getPos() { return pos; }

    MapPosition &getLastPos() { return lastPos; }

    Map &getMap() { return map; }

    Backpack &getBackpack() { return backpack; }

    Backpack &setBackpack(Backpack backpack) {
        if (backpack == this->backpack);
        else this->backpack = backpack;
        return this->backpack;
    }

    void setPos(int line, int column) {
        pos.line = line;
        pos.column = column;
    }

private:
    //Ӧ���ò����������������˺����㶼��ÿ��word��wordDamage
    Map map;
    Backpack backpack;
    MapPosition pos = {8, 6};
    MapPosition lastPos = {8, 6};
    int itemChance = 2;
};

Player::Player(string name) : Creature(100, name) {
    currHP = hp;
    resetCurrHP();
    // ��ձ���
    backpack.clear();
}

void Player::printStatus() const {
    Interface::setPos(0, 0);
    cout << "\33[46;33m" << "ľ" << "\33[0m" << endl;
    cout << endl;
    cout << "\33[46;33m" << "HP: " << "\33[0m" << currHP << endl;


    cout << endl;
    cout<< "\33[31m[[����˵��]]\33[0m" <<endl;
    cout << "\33[31m[B] \33[0m�򿪱���" << endl;
    cout << "\33[31m[E] \33[0m�鿴����" << endl;
    cout << "\33[31m[U] \33[0m����˵��" << endl;
    cout << "\33[31m[W][A][S][D] \33[0m�� \33[31m[��][��][��][��] \33[0m�ƶ�" << endl;
    cout << "\33[31m[F5] \33[0mˢ�µ�ͼ" << endl;
    cout << endl;
    cout << "\33[31m[Q] \33[0m�˳���Ϸ" << endl;

}

#endif //GAMETOWER1_HERO_H
