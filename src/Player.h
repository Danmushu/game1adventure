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

//player 伤害结算用word.getEffect() 里读出来的数字
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
    //应该用不到这个东西。玩家伤害结算都靠每个word的wordDamage
    Map map;
    Backpack backpack;
    MapPosition pos = {8, 6};
    MapPosition lastPos = {8, 6};
    int itemChance = 2;
};

Player::Player(string name) : Creature(100, name) {
    currHP = hp;
    resetCurrHP();
    // 清空背包
    backpack.clear();
}

void Player::printStatus() const {
    Interface::setPos(0, 0);
    cout << "\33[46;33m" << "木" << "\33[0m" << endl;
    cout << endl;
    cout << "\33[46;33m" << "HP: " << "\33[0m" << currHP << endl;


    cout << endl;
    cout<< "\33[31m[[按键说明]]\33[0m" <<endl;
    cout << "\33[31m[B] \33[0m打开背包" << endl;
    cout << "\33[31m[E] \33[0m查看帮助" << endl;
    cout << "\33[31m[U] \33[0m怪物说明" << endl;
    cout << "\33[31m[W][A][S][D] \33[0m或 \33[31m[↑][←][↓][→] \33[0m移动" << endl;
    cout << "\33[31m[F5] \33[0m刷新地图" << endl;
    cout << endl;
    cout << "\33[31m[Q] \33[0m退出游戏" << endl;

}

#endif //GAMETOWER1_HERO_H
