
#ifndef GAMETOWER_WORD_H
#define GAMETOWER_WORD_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>
#include "Interface.h"

using namespace std;
using std::cout;

class Bar {
public:
    Bar();

    Bar(int length, std::string word, char effect);

    void putWord(const string, int level);

    void changeColor(int pos, int co);

    int getLength() { return length; }

    std::string getString() { return word; }

    void changeState(bool state);

    bool getState() { return isFinished; }

    int getCur() { return cur; }

    void changeCur(int cur) { this->cur = cur; }

    int getEffect() {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, 15); //概率的分母

        int random_number = distr(gen);
        if (random_number == 1) {  // 概率分子
            std::uniform_int_distribution<> distr_damage(200, 600);
            int boosted_damage = distr_damage(gen);  // 生成一个 200 到 600 的随机数
            return effect * boosted_damage / 100;  // 将 effect 增加到 200% 到 600%
        }
        return effect;
    }

    std::string getName() const { return word; }

    ~Bar() = default;

private:
    std::string word;
    int length;
    int effect; // h: heal, d: damage
    bool isFinished; //用于实现变色打字，表示字是否被打完
    int position; //用于实现空格位置，随机化
    std::vector<int> color; //用于实现变色打字，表示每个字母的color属性
    int cur; //用于实现变色打字，表示当前打到第几个字

};

Bar::Bar() {

}



void Bar::changeState(bool state) {

}

// 增加根据等级增加伤害的逻辑
void Bar::putWord(const string s, int level) {
    if (s.empty()){
        random_device seed;//硬件生成随机数种子
        ranlux48 engine(seed());//利用种子生成随机数引擎
        uniform_int_distribution<> distrib(0, 17);//设置随机数范围，并为均匀分布
        int randint = distrib(engine);//随机数
        this->word = "";

        // 随机构造
        for (int i = 0; i < randint; i ++){
            this -> word += "0";
        }
        switch (level) {
            case 1:
                this->word += "242";
                break;
            case 2:
                this->word += "474";
                break;
            case 3:
                this->word += "686";
                break;
            case 4:
                this->word += "898";
                break;
            case 5:
                this->word += "999";
                break;
        }
//        this->word += "121";
        for (int i = 0; i < 18 - randint; i ++){
            this -> word += "0";
        }
    }

    this->length = 20;

    Interface::setPos(7, (int) (40 - length / 2));
    for (int i = 0; i < length; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[i]);
        cout << word[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}

void Bar::changeColor(int pos, int co) {
    color[pos] = co;
}

Bar::Bar(int length, std::string word, char effect) {
    this->length = 20;
    this->effect = effect;
    this->word = word;
    this->position=0;
    this->cur = 0;
    for (int i = 0; i < length; i++) {
        color.push_back(8);
    }

}

#endif //GAMETOWER_WORD_H
