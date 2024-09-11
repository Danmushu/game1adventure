//
// Created by hang on 2023-08-22.
//

#ifndef GAMETOWER1_MONSTER_H
#define GAMETOWER1_MONSTER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Creature.h"
#include "Stripe.h"

class Monster : public Creature {
public:
    Monster() = default;
    Monster(int monsterNumber);
    Monster(int HP, int damage, std::vector<Stripe> wordList, const std::string description);

    int getDamage() const { return damage; }
    std::string des() { return this->description; }
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
    std::string numberString = std::to_string(monsterNumber);
    std::string filePath = "./Assets/Enemies/.enemy" + numberString;
    std::ifstream file(filePath);
    std::string word;
    wordList.clear();
    cout << "reading monster ..." << endl;
    file >> name;
    file >> hp;
    file >> damage;

    currHP = hp;
    std::getline(file >> std::ws, description);
    file >> level;

//    while (file >> word)
//        wordList.emplace_back(word.size(), word, damage);
//    for(auto &i:wordList) cout<<i.getName()<<endl;
}

#endif //GAMETOWER1_MONSTER_H
