//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_WORD_H
#define GAMETOWER_WORD_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>
#include "Interface.h"

using namespace std;
using std::cout;

class Stripe {
public:
    Stripe();

    Stripe(int length, std::string word, char effect);

    void putWord(const string);

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
        std::uniform_int_distribution<> distr(1, 15); //���ʵķ�ĸ

        int random_number = distr(gen);
        if (random_number == 1) {  // ���ʷ���
            std::uniform_int_distribution<> distr_damage(200, 600);
            int boosted_damage = distr_damage(gen);  // ����һ�� 200 �� 600 �������
            return effect * boosted_damage / 100;  // �� effect ���ӵ� 200% �� 600%
        }
        return effect;
    }

    std::string getName() const { return word; }

    ~Stripe() = default;

private:
    std::string word;
    int length;
    int effect; // h: heal, d: damage
    bool isFinished; //����ʵ�ֱ�ɫ���֣���ʾ���Ƿ񱻴���
    int position; //����ʵ�ֿո�λ�ã������
    std::vector<int> color; //����ʵ�ֱ�ɫ���֣���ʾÿ����ĸ��color����
    int cur; //����ʵ�ֱ�ɫ���֣���ʾ��ǰ�򵽵ڼ�����

};

Stripe::Stripe() {

}



void Stripe::changeState(bool state) {

}

void Stripe::putWord(const string s) {
    if (s.empty()){

        random_device seed;//Ӳ���������������
        ranlux48 engine(seed());//���������������������
        uniform_int_distribution<> distrib(0, 17);//�����������Χ����Ϊ���ȷֲ�
        int randint = distrib(engine);//�����
        this->word = "";

        // �������
        for (int i = 0; i < randint; i ++){
            this -> word += "0";
        }
        this->word += "121";
        for (int i = 0; i < 18 - randint; i ++){
            this -> word += "0";
        }
    }

    this->length = 20;

//    for (int i = 0; i < position; i++)std::cout << ' ';
//        for (int i = 0; i < length; i++) {
//            cout << ' ';
//        }

    PosControl::setPos(29, (int) (50 - length/2));
    for (int i = 0; i < length; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[i]);
        cout << word[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}

void Stripe::changeColor(int pos, int co) {
    color[pos] = co;
}

Stripe::Stripe(int length, std::string word, char effect) {
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
