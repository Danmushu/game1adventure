#ifndef GAMETOWER_CREATURE_H
#define GAMETOWER_CREATURE_H

#include <iostream>
#include <string>
#include <utility>
#include "Map.h"

class Creature {
public:
    Creature(): hp(0){};
    Creature(int hp, std::string name): hp(hp), name(std::move(name)) {};
    virtual ~Creature() = default;
    void setHP(const int& hp) { this->hp = hp; }
    int getHP() const { return hp; }
    void setName(const std::string& name) { this->name = name; }
    std::string getName() const { return name; }
    void getDamaged(int damage){ currHP-=damage; };
    int getCurrHP() const{ return currHP; }
    void setCurrHP(int currHP){ this->currHP = currHP; };
    void resetCurrHP(){ currHP = hp; }
    int getLevel(){ return level;}
    void setLevel(int level){ this->level = level; }
    const std::vector<Stripe>& deliverWord() { return this->wordList; };

    void init();
protected:
    int hp; // health point
    std::string name;
    std::vector<Stripe> wordList;
    int currHP{};
    int level;//用来决定战斗难度

};

void Creature::init() {

    this->wordList = vector<Stripe>();
    this->wordList.emplace_back(20, "", '1');
}

#endif //GAMETOWER_CREATURE_H
