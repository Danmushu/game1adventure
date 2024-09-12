#ifndef GAMETOWER1_MONSTER_H
#define GAMETOWER1_MONSTER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Creature.h"
#include "Bar.h"

class Monster : public Creature {
public:
    Monster() = default;
    Monster(int monsterNumber);
//    Monster(int HP, int damage, std::vector<Bar> wordList, const std::string description);

    int getDamage() const { return damage; }
    void readMonsterData(int monsterNumber);
    ~Monster() override = default;
private:
    int damage;
    std::string description;
};

Monster::Monster(int monsterNumber) {
    this->readMonsterData(monsterNumber);
}

void Monster::readMonsterData(int monsterNumber) {
    // 转换成字符串
    std::string numberString = std::to_string(monsterNumber);
    // 数据文件的路径
    std::string filePath = "./assets/Enemies/.enemy" + numberString;
    std::ifstream file(filePath);
    // 定义一个字符串变量用于读取文件中的单词
    std::string word;
    // 清空bar
    bar.clear();
    // 读取怪物数据
    cout << "reading monster ..." << endl;
    // 读取怪物名字、生命值和攻击力
    file >> name;
    file >> hp;
    file >> damage;
    // 将读取到的生命值赋值给当前生命值
    currHP = hp;
    // 读取怪物的描述，std::ws是一个操纵符，用于吸收前导空白字符
    std::getline(file >> std::ws, description);
    file >> level;
}

#endif //GAMETOWER1_MONSTER_H
