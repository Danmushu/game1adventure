//
// Created by Jiarong on 2023/8/21.
//

// A MUD Game

#define NOMINMAX  // 防止 Windows.h 头文件定义 min 和 max 宏，避免与标准库中的 std::min/std::max 冲突

#include <iostream>  // 提供标准输入输出功能
#include <csignal>  // 提供信号处理功能
#include "Interface.h"  // 包含游戏界面相关的函数和类
#include "GameController.h"  // 包含游戏数据相关的类和函数

using std::cout, std::cin, std::endl, std::ifstream, std::string;

void checkValidation(string name, int x) {
    // 验证玩家输入的名字是否合法
    while (name.length() > 15 || name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != string::npos) {
        // 如果名字不合法，重新设置光标并提示玩家重新输入
        PosControl::setPos(x, 0);
        // 清除当前行内容
        cout << "\33[2K" << endl;
        // 检查名字是否包含非法字符或名字长度是否超过15个字符
        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != string::npos) {
            // 如果包含非法字符，提示玩家重新输入合法名字
            cout << "名字中含有非法字符，请重新输入：";
        } else {
            // 如果名字过长，提示玩家重新输入短一点的名字
            cout << "名字过长，请重新输入：";
        }
        cin >> name;  // 重新获取玩家输入的名字
    }
    // 清除输入提示行
    PosControl::setPos(x, 0);
}

void helloPlayer(const string& name){
    // 向玩家打招呼并显示其名字
    cout << "    你好，名为 ";
    // 将文字颜色设置为黄色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << name;
    // 恢复文字颜色为默认值（白色）
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << " 的道友！" << endl;

    // 输出两行空行，视觉上清理输出区域
    string spaceLine(100, ' ');

    cout << spaceLine << endl << spaceLine << endl;
}

int main() {
    //setDPI();  // 如果需要，可以设置 DPI 缩放，暂时注释掉
    PosControl::centerWindow();
    PosControl::HideCursor();
    Player player1("123");
    Game game1(player1);
    game1.newGame();
    return 0;
    // 显示欢迎页面
    welcomePage();

    int x, y;  // 用于存储光标位置的变量
    string name;  // 存储玩家输入的名字

    // 获取当前光标位置
    PosControl::getPos(x, y);
    // 设置光标位置到当前行的起始位置
    PosControl::setPos(x, 0);
    // 清除当前行的内容
    cout << "\33[2K";
    // 提示玩家输入名字
    cout << "请输入你的尊姓大名：";
    cin >> name;
    checkValidation(name, x);
    helloPlayer(name);
    Player player(name);
    Game game(player);
    // 定义游戏主菜单的选项
    Menu menu[3]{
            "新游戏",  // 新游戏选项
            "加载游戏",  // 加载游戏选项
            "退出游戏"  // 退出游戏选项
    };

    // 调用 switcher 函数显示主菜单，并根据玩家选择执行相应的操作
    switch (switcher(menu, 3)) {
        case 0:
            // 如果玩家选择了“新游戏”，则启动新游戏
            game.newGame();
            break;
        case 1:
            // 如果玩家选择了“加载游戏”，则加载游戏数据
            game.loadGame();
            break;
        case 2:
            // 如果玩家选择了“退出游戏”，则显示退出页面，并退出程序
            goodbye();
            system("pause");  // 暂停等待用户按键
            return 0;  // 退出程序
    }

    return 0;  // 程序正常结束
}

