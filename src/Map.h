//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_MAP_H
#define GAMETOWER_MAP_H

#include "Interface.h"
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Location.h"

using std::cout;
using std::endl;

// Map �����ڹ�����Ϸ��ͼ��������ͼλ�á����Ⱥ���ز���
class Map {
public:
    Map();  // ���캯������ʼ����ͼ
    ~Map() = default;  // Ĭ����������
    static void printMap();  // ��̬�����������ڿ���̨�д�ӡ��ͼ
    Location *getLocation(int line, int column) const { return locations[line][column]; }  // ��ȡָ��λ�õ� Location ����
    void loadMap(std::istream &is = std::cin);  // ���������м��ص�ͼ״̬
    void showMap(std::ostream &os = std::cout);  // ����ͼ״̬������������
    // ����ָ��λ�õ����������״̬����������Ϸ����
    void setHasDone(int line, int column) {
        dynamic_cast<Place*>(locations[line][column])->setHasDone(true);  // ����ָ��λ�õ����������
        if (line == 2 && column == 4) dynamic_cast<Place*>(locations[4][4])->setHasDone(true);  // �����ָ��λ�ã�������һλ�õ����������
        setProgress(currProgress + 1);  // ���½���
    }
    void setProgress(int progress);  // ���õ�ǰ���Ȳ����µ�ͼ״̬
    int getProgress() const { return currProgress; }  // ��ȡ��ǰ����
    string getDefaultMsgDir() const { return currDefaultMsgDir; }  // ��ȡ��ǰĬ����Ϣ�ļ�·��
private:
    Location *locations[10][10]{};  // 10x10�� Location ָ�����飬���ڴ洢��ͼλ�ö���
    int currProgress = 0;  // ��ǰ��Ϸ����
    string currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheGate.txt";  // ��ǰĬ����Ϣ�ļ�·��
};

// Map �๹�캯������ʼ����ͼλ�ö���
Map::Map() {
    // ��ʼ��ÿ��λ��Ϊ Location ����
    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
            locations[i][j] = new Location();

    // �����ض�λ��Ϊ Place �� Road ���󣬲�ָ�����ơ����������
//    locations[8][4] = new Place("�ؾ����", 25, 45, false);  // �ؾ���ڣ�δ����
//    locations[7][4] = new Road(true);  // �����ؾ���ڵĵ�·���ѽ���
//    locations[6][4] = new Place("�ؾ�һ��", 20, 66);  // �ؾ�һ�㣬Ĭ������
//    locations[5][4] = new Road(true);  // �����ؾ�2��ĵ�·���ѽ���
//    locations[4][4] = new Place("�����", 20, 48);  // �����λ�ã�Ĭ������
//    locations[3][6] = new Road(true);  // ���ӱ����ĵ�·���ѽ���
//    locations[2][4] = new Place("�ؾ�����", 7, 47);  // �ؾ�����λ�ã�Ĭ������
//    locations[4][2] = new Place("�ؾ��в�", 15, 29);  // �ؾ��ռ�в㣬Ĭ������
//    locations[4][3] = new Road(true);  // �����ؾ��ռ�в�ĵ�·���ѽ���
//    locations[4][5] = new Road(true);  // ���ӱ�������һ����·���ѽ���
//    locations[4][6] = new Place("�ؾ�����", 15, 47);  // �����ؾ����㣬Ĭ������
//    locations[2][5] = new Road(true);  // �����ؾ����ĵĵ�·���ѽ���
//    locations[2][6] = new Place("�ؾ�����",11, 47);  // �ؾ����㣬Ĭ������

    locations[8][6] = new Place("�ؾ����", 25, 45, false);  // �ؾ���ڣ�δ����
    locations[7][6] = new Road(true);  // �����ؾ���ڵĵ�·���ѽ���
    locations[6][6] = new Place("�ؾ�һ��", 20, 66);  // �ؾ�һ�㣬Ĭ������
    locations[6][5] = new Road(true);  // �����ؾ�2��ĵ�·���ѽ���->6,5
    locations[6][4] = new Place("�����", 20, 48);  // �����λ�ã�Ĭ������->6,4
    locations[6][3] = new Road(true);  // �����ؾ��ռ�в�ĵ�·���ѽ���->6,3
    locations[6][2] = new Place("�ؾ��в�", 15, 29);  // �ؾ��ռ�в㣬Ĭ������->6,2
    locations[5][4] = new Road(true);  // ����2���·���ѽ���->5,4
    locations[4][4] = new Place("�ؾ�����", 15, 47);  // �����ؾ����㣬Ĭ������4,4
    locations[3][4] = new Road(true);  // ����3��ĵ�·���ѽ���3,4
    locations[2][4] = new Place("�ؾ�����",11, 47);  // �ؾ����㣬Ĭ������2,4
    locations[1][4] = new Road(true);  // �����ؾ����ĵĵ�·���ѽ���1,4
    locations[0][4] = new Place("�ؾ�����", 7, 47);  // �ؾ�����λ�ã�Ĭ������0,4
}

// ��̬�����������ڿ���̨�д�ӡ��ͼ
void Map::printMap(){
    system("cls");  // �������̨����
    PosControl::setPos(0, 0);  // ��������õ�����̨�����Ͻ�
    std::ifstream mapFile("./Assets/.map");  // �򿪴洢��ͼͼ����ļ�
    char map;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // �����ı���ɫΪ��ɫ
    while (mapFile.get(map)) {  // ���ַ���ȡ����ӡ��ͼ
        cout << map;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // �ָ��ı���ɫΪĬ����ɫ
    mapFile.close();  // �رյ�ͼ�ļ�

    // �û�ɫ��ǵ�··��
    PosControl::setPos(0, 0);  // ��������õ�����̨�����Ͻ�
    std::ifstream pathFile("./Assets/.map_path");  // �򿪴洢��··�����ļ�
    char path;
    while (pathFile.get(path)) {  // ���ַ���ȡ����ӡ·��
        if (path != ' ') {  // ������ǿո�
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);  // �����ı���ɫΪ��ɫ
            cout << path;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // �ָ��ı���ɫΪĬ����ɫ
        } else if (path == '\n') {  // ����ǻ��з�������
            cout << endl;
        } else {
            cout << "\033[1C";  // ����ǿո񣬹������һ��
        }
    }
    pathFile.close();  // �ر�·���ļ�

    // �ڵ�ͼ�ϱ���ض�λ�õ����ƣ��������ı���ɫΪ��ɫ
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);  // �����ı���ɫΪ��ɫ
    cout << "\033[25;45H�ؾ����";  // ���ض�λ����ʾ�ؾ����
    cout << "\033[20;66H�ؾ�һ��";  // ���ض�λ����ʾ�ؾ���һ��
    cout << "\033[20;48H�����";  // ���ض�λ����ʾ�����
    cout << "\033[7;47H�ؾ�����";  // ���ض�λ����ʾ�ؾ�����
    cout << "\033[15;29H�ؾ��в�";  // ���ض�λ����ʾ�ؾ��ռ�в�
    cout << "\033[15;47H�ؾ�����";  // ���ض�λ����ʾ�ؾ�����
    cout << "\033[11;47H�ؾ�����";  // ���ض�λ����ʾ�ؾ�����
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // �ָ��ı���ɫΪĬ����ɫ

    PosControl::setPos(0, 0);  // ��������õ�����̨�����Ͻ�
}

// ���������м��ص�ͼ״̬�������������״̬������״̬
void Map::loadMap(std::istream &is) {
    int line, column;
    bool hasDone, isLocked;
    while (is >> line >> column >> hasDone >> isLocked) {  // ���������ж�ȡÿ��λ�õ�״̬
        dynamic_cast<Place*>(locations[line][column])->setHasDone(hasDone);  // �����������״̬
        dynamic_cast<Place*>(locations[line][column])->setIsLocked(isLocked);  // ��������״̬
    }
}

// ����ͼ״̬�����������У������������״̬������״̬
void Map::showMap(std::ostream &os) {
    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
        {
            if (locations[i][j]->isPlace())  // �����ǰλ���� Place ����
            {
                Place *place = dynamic_cast<Place*>(locations[i][j]);  // �� Location ����ת��Ϊ Place ����
                os << i << " " << j << " " << place->getHasDone() << " " << place->getIsLocked() << endl;  // ���λ����Ϣ
            }
        }
}

// ���õ�ǰ���Ȳ����ݽ��Ƚ�����ͼ�ϵ�λ��
void Map::setProgress(int progress) {
    currProgress = std::min(5,progress);  // ȷ�����Ȳ�����5

    // ���ݵ�ǰ���Ƚ����ض�λ��
    switch (progress) { // ������ã��������½���ʱ��ǰ��ĳ���Ҳ�ܽ���
//        case 4:
//            dynamic_cast<Place*>(locations[4][2])->setIsLocked(false);�ؾ�����
//            dynamic_cast<Place*>(locations[2][6])->setHasDone(true);�ؾ�����
//            dynamic_cast<Place*>(locations[4][4])->setIsLocked(true); �����
//            dynamic_cast<Place*>(locations[4][4])->setHasDone(true); �����
//        case 3:
//            dynamic_cast<Place*>(locations[2][6])->setIsLocked(false);�ؾ�����
//            dynamic_cast<Place*>(locations[4][4])->setHasDone(false);�����
//            dynamic_cast<Place*>(locations[4][6])->setHasDone(true);�ؾ�����
//        case 2:
//            dynamic_cast<Place*>(locations[4][4])->setIsLocked(false);�����
//            dynamic_cast<Place*>(locations[4][6])->setIsLocked(false);�ؾ�����
//            dynamic_cast<Place*>(locations[6][4])->setHasDone(true);�ؾ�һ��
//        case 1:
//            dynamic_cast<Place*>(locations[6][4])->setIsLocked(false);�ؾ�һ��
//            dynamic_cast<Place*>(locations[8][4])->setHasDone(true);�ؾ����
//        case 0:
//            dynamic_cast<Place*>(locations[8][4])->setIsLocked(false);�ؾ����

        case 4:
            dynamic_cast<Place*>(locations[0][4])->setIsLocked(false);
            dynamic_cast<Place*>(locations[2][4])->setHasDone(true);
            dynamic_cast<Place*>(locations[6][4])->setIsLocked(true);
            dynamic_cast<Place*>(locations[6][4])->setHasDone(true);
        case 3:
            dynamic_cast<Place*>(locations[2][5])->setIsLocked(false);
            dynamic_cast<Place*>(locations[6][4])->setHasDone(false);
            dynamic_cast<Place*>(locations[4][4])->setHasDone(true);
        case 2:
            dynamic_cast<Place*>(locations[6][4])->setIsLocked(false);
            dynamic_cast<Place*>(locations[4][4])->setIsLocked(false);
            dynamic_cast<Place*>(locations[6][6])->setHasDone(true);
        case 1:
            dynamic_cast<Place*>(locations[6][6])->setIsLocked(false);
            dynamic_cast<Place*>(locations[8][6])->setHasDone(true);
        case 0:
            dynamic_cast<Place*>(locations[8][6])->setIsLocked(false);

    }

    // ���ݵ�ǰ��������Ĭ����Ϣ�ļ�·��
    switch (progress) {
        case 0:
            currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheGate.txt";  // ����Ϊ����ǰ��Ϣ�ļ�
            break;
        case 1:
            currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheFirstLayer.txt";  // ����Ϊ��ӭ�´���ǰ��Ϣ�ļ�
            break;
        case 2:
            currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheSecondLayer.txt";  // ����Ϊ̽��ǰ��Ϣ�ļ�
            break;
        case 3:
            currDefaultMsgDir = "./Assets/Scene/Other/Faith.txt";  // ����Ϊս����־��Ϣ�ļ�
            break;
        case 4:
        case 5:
            currDefaultMsgDir = "";  // �����Ϣ�ļ�·��
            break;
    }
}


#endif //GAMETOWER_MAP_H
