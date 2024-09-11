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

// Map 类用于管理游戏地图，包含地图位置、进度和相关操作
class Map {
public:
    Map();  // 构造函数，初始化地图
    ~Map() = default;  // 默认析构函数
    static void printMap();  // 静态函数，用于在控制台中打印地图
    Location *getLocation(int line, int column) const { return locations[line][column]; }  // 获取指定位置的 Location 对象
    void loadMap(std::istream &is = std::cin);  // 从输入流中加载地图状态
    void showMap(std::ostream &os = std::cout);  // 将地图状态输出到输出流中
    // 设置指定位置的任务已完成状态，并更新游戏进度
    void setHasDone(int line, int column) {
        dynamic_cast<Place*>(locations[line][column])->setHasDone(true);  // 设置指定位置的任务已完成
        if (line == 2 && column == 4) dynamic_cast<Place*>(locations[4][4])->setHasDone(true);  // 如果在指定位置，设置另一位置的任务已完成
        setProgress(currProgress + 1);  // 更新进度
    }
    void setProgress(int progress);  // 设置当前进度并更新地图状态
    int getProgress() const { return currProgress; }  // 获取当前进度
    string getDefaultMsgDir() const { return currDefaultMsgDir; }  // 获取当前默认消息文件路径
private:
    Location *locations[10][10]{};  // 10x10的 Location 指针数组，用于存储地图位置对象
    int currProgress = 0;  // 当前游戏进度
    string currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheGate.txt";  // 当前默认消息文件路径
};

// Map 类构造函数，初始化地图位置对象
Map::Map() {
    // 初始化每个位置为 Location 对象
    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
            locations[i][j] = new Location();

    // 设置特定位置为 Place 或 Road 对象，并指定名称、坐标等属性
//    locations[8][4] = new Place("秘境入口", 25, 45, false);  // 秘境入口，未锁定
//    locations[7][4] = new Road(true);  // 连接秘境入口的道路，已解锁
//    locations[6][4] = new Place("秘境一层", 20, 66);  // 秘境一层，默认锁定
//    locations[5][4] = new Road(true);  // 连接秘境2层的道路，已解锁
//    locations[4][4] = new Place("宝光阁", 20, 48);  // 宝光阁位置，默认锁定
//    locations[3][6] = new Road(true);  // 连接宝光阁的道路，已解锁
//    locations[2][4] = new Place("秘境核心", 7, 47);  // 秘境核心位置，默认锁定
//    locations[4][2] = new Place("秘境夹层", 15, 29);  // 秘境空间夹层，默认锁定
//    locations[4][3] = new Road(true);  // 连接秘境空间夹层的道路，已解锁
//    locations[4][5] = new Road(true);  // 连接宝光阁的另一条道路，已解锁
//    locations[4][6] = new Place("秘境二层", 15, 47);  // 秘密秘境二层，默认锁定
//    locations[2][5] = new Road(true);  // 连接秘境核心的道路，已解锁
//    locations[2][6] = new Place("秘境三层",11, 47);  // 秘境三层，默认锁定

    locations[8][6] = new Place("秘境入口", 25, 45, false);  // 秘境入口，未锁定
    locations[7][6] = new Road(true);  // 连接秘境入口的道路，已解锁
    locations[6][6] = new Place("秘境一层", 20, 66);  // 秘境一层，默认锁定
    locations[6][5] = new Road(true);  // 连接秘境2层的道路，已解锁->6,5
    locations[6][4] = new Place("宝光阁", 20, 48);  // 宝光阁位置，默认锁定->6,4
    locations[6][3] = new Road(true);  // 连接秘境空间夹层的道路，已解锁->6,3
    locations[6][2] = new Place("秘境夹层", 15, 29);  // 秘境空间夹层，默认锁定->6,2
    locations[5][4] = new Road(true);  // 连接2层道路，已解锁->5,4
    locations[4][4] = new Place("秘境二层", 15, 47);  // 秘密秘境二层，默认锁定4,4
    locations[3][4] = new Road(true);  // 连接3层的道路，已解锁3,4
    locations[2][4] = new Place("秘境三层",11, 47);  // 秘境三层，默认锁定2,4
    locations[1][4] = new Road(true);  // 连接秘境核心的道路，已解锁1,4
    locations[0][4] = new Place("秘境核心", 7, 47);  // 秘境核心位置，默认锁定0,4
}

// 静态函数，用于在控制台中打印地图
void Map::printMap(){
    system("cls");  // 清除控制台内容
    PosControl::setPos(0, 0);  // 将光标设置到控制台的左上角
    std::ifstream mapFile("./Assets/.map");  // 打开存储地图图像的文件
    char map;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // 设置文本颜色为白色
    while (mapFile.get(map)) {  // 逐字符读取并打印地图
        cout << map;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // 恢复文本颜色为默认颜色
    mapFile.close();  // 关闭地图文件

    // 用灰色标记道路路径
    PosControl::setPos(0, 0);  // 将光标设置到控制台的左上角
    std::ifstream pathFile("./Assets/.map_path");  // 打开存储道路路径的文件
    char path;
    while (pathFile.get(path)) {  // 逐字符读取并打印路径
        if (path != ' ') {  // 如果不是空格
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);  // 设置文本颜色为灰色
            cout << path;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // 恢复文本颜色为默认颜色
        } else if (path == '\n') {  // 如果是换行符，换行
            cout << endl;
        } else {
            cout << "\033[1C";  // 如果是空格，光标右移一格
        }
    }
    pathFile.close();  // 关闭路径文件

    // 在地图上标记特定位置的名称，并设置文本颜色为黄色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);  // 设置文本颜色为黄色
    cout << "\033[25;45H秘境入口";  // 在特定位置显示秘境入口
    cout << "\033[20;66H秘境一层";  // 在特定位置显示秘境第一层
    cout << "\033[20;48H宝光阁";  // 在特定位置显示宝光阁
    cout << "\033[7;47H秘境核心";  // 在特定位置显示秘境核心
    cout << "\033[15;29H秘境夹层";  // 在特定位置显示秘境空间夹层
    cout << "\033[15;47H秘境二层";  // 在特定位置显示秘境二层
    cout << "\033[11;47H秘境三层";  // 在特定位置显示秘境三层
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // 恢复文本颜色为默认颜色

    PosControl::setPos(0, 0);  // 将光标设置到控制台的左上角
}

// 从输入流中加载地图状态，包括任务完成状态和锁定状态
void Map::loadMap(std::istream &is) {
    int line, column;
    bool hasDone, isLocked;
    while (is >> line >> column >> hasDone >> isLocked) {  // 从输入流中读取每个位置的状态
        dynamic_cast<Place*>(locations[line][column])->setHasDone(hasDone);  // 设置任务完成状态
        dynamic_cast<Place*>(locations[line][column])->setIsLocked(isLocked);  // 设置锁定状态
    }
}

// 将地图状态输出到输出流中，包括任务完成状态和锁定状态
void Map::showMap(std::ostream &os) {
    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
        {
            if (locations[i][j]->isPlace())  // 如果当前位置是 Place 对象
            {
                Place *place = dynamic_cast<Place*>(locations[i][j]);  // 将 Location 对象转换为 Place 对象
                os << i << " " << j << " " << place->getHasDone() << " " << place->getIsLocked() << endl;  // 输出位置信息
            }
        }
}

// 设置当前进度并根据进度解锁地图上的位置
void Map::setProgress(int progress) {
    currProgress = std::min(5,progress);  // 确保进度不超过5

    // 根据当前进度解锁特定位置
    switch (progress) { // 倒序放置，当导入新进度时，前面的场景也能解锁
//        case 4:
//            dynamic_cast<Place*>(locations[4][2])->setIsLocked(false);秘境核心
//            dynamic_cast<Place*>(locations[2][6])->setHasDone(true);秘境三层
//            dynamic_cast<Place*>(locations[4][4])->setIsLocked(true); 宝光阁
//            dynamic_cast<Place*>(locations[4][4])->setHasDone(true); 宝光阁
//        case 3:
//            dynamic_cast<Place*>(locations[2][6])->setIsLocked(false);秘境三层
//            dynamic_cast<Place*>(locations[4][4])->setHasDone(false);宝光阁
//            dynamic_cast<Place*>(locations[4][6])->setHasDone(true);秘境二层
//        case 2:
//            dynamic_cast<Place*>(locations[4][4])->setIsLocked(false);宝光阁
//            dynamic_cast<Place*>(locations[4][6])->setIsLocked(false);秘境二层
//            dynamic_cast<Place*>(locations[6][4])->setHasDone(true);秘境一层
//        case 1:
//            dynamic_cast<Place*>(locations[6][4])->setIsLocked(false);秘境一层
//            dynamic_cast<Place*>(locations[8][4])->setHasDone(true);秘境入口
//        case 0:
//            dynamic_cast<Place*>(locations[8][4])->setIsLocked(false);秘境入口

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

    // 根据当前进度设置默认消息文件路径
    switch (progress) {
        case 0:
            currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheGate.txt";  // 设置为进门前消息文件
            break;
        case 1:
            currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheFirstLayer.txt";  // 设置为进迎新大厅前消息文件
            break;
        case 2:
            currDefaultMsgDir = "./Assets/Scene/Other/BeforeTheSecondLayer.txt";  // 设置为探险前消息文件
            break;
        case 3:
            currDefaultMsgDir = "./Assets/Scene/Other/Faith.txt";  // 设置为战斗意志消息文件
            break;
        case 4:
        case 5:
            currDefaultMsgDir = "";  // 清空消息文件路径
            break;
    }
}


#endif //GAMETOWER_MAP_H
