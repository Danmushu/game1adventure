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
    // ת�����ַ���
    std::string numberString = std::to_string(monsterNumber);
    // �����ļ���·��
    std::string filePath = "./assets/Enemies/.enemy" + numberString;
    std::ifstream file(filePath);
    // ����һ���ַ����������ڶ�ȡ�ļ��еĵ���
    std::string word;
    // ���bar
    bar.clear();
    // ��ȡ��������
    cout << "reading monster ..." << endl;
    // ��ȡ�������֡�����ֵ�͹�����
    file >> name;
    file >> hp;
    file >> damage;
    // ����ȡ��������ֵ��ֵ����ǰ����ֵ
    currHP = hp;
    // ��ȡ�����������std::ws��һ�����ݷ�����������ǰ���հ��ַ�
    std::getline(file >> std::ws, description);
    file >> level;
}

#endif //GAMETOWER1_MONSTER_H
