#ifndef GAMETOWER1_FIGHT_SCENE_H
#define GAMETOWER1_FIGHT_SCENE_H
#define getPlaceName(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getName()

#include <utility>
#include <vector>
#include "Monster.h"
#include <ctime>
#include <random>
#include "Interface.h"
#include "Stripe.h"
#include "Player.h"
#include "Map.h"
#include "run.h"


const int ColorLighted = 5;
const int ColorDefault = 8;

void cls();

void updatePrint(std::vector<Stripe> upper, std::vector<Stripe> lower);

int deeper(int &t, Stripe &word, std::vector<Stripe> &upper, std::vector<Stripe> &lower);


class Fight {
public:
    Fight(string name, int progress) : name(std::move(name)), monster(progress + 1) {};

//    Fight(std::string id, int b);

    void loadScene(Player &player);//外部调用接口
    static bool checkWin(Player &player);
    //字符下落，由loadScene调用

    //调控打字变色并check，由loadScene调用
    //检查真言
//    int checkWord(string s);

    ~Fight() = default;

private:
    Monster monster;//本关所面对的怪物
    std::string name;

    void showScene(Backpack &backpack);

    void showHP(Player &player);

    void typeAndColor(std::vector<Stripe> &upper, std::vector<Stripe> &lower, Player &player);

    void useItem(Player &player, int effect);


    static void showPlayerInfo(const string& msg);

    static void showMonsterInfo(const string& msg);
};

void Fight::showHP(Player &player)     {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
//    PosControl::setPos(16, 1);
    PosControl::setPos(3,11);
    cout << monster.getName() ;
    PosControl::setPos(4,11);
    cout<< "[气血]";
    int curhp, HP;
    curhp = std::max(0, monster.getCurrHP()), HP = monster.getHP();
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
//    PosControl::setPos(16, 1);
    PosControl::setPos(3, 11);
    cout << monster.getName() ;
    PosControl::setPos(4,11);
    cout << "[气血]";
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    PosControl::setPos(5, 11);
    curhp = std::max(0, player.getCurrHP()), HP = player.getHP();
    cout << player.getName();
    PosControl::setPos(6, 11);
    cout<<"[气血]";
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    PosControl::setPos(5, 11);
    cout << player.getName() ;
    PosControl::setPos(6,11);
    cout << "[气血]";
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}

//外部接口
void Fight::loadScene(Player &player) {
    showScene(player.getBackpack());//边框绘制
    PosControl::HideCursor();//隐藏光标
    std::vector<Stripe> upper, lower;//加载打击条
    upper = monster.deliverWord();
    player.init();
    lower = player.deliverWord();
    showHP(player);//显示初始血量
    typeAndColor(upper, lower, player);//核心函数，判断打击
}

void Fight::typeAndColor(std::vector<Stripe> &upper, std::vector<Stripe> &lower, Player &player) {
    int level = player.getLevel();
    lower[0].putWord("", level);
    char next = ' '; //next是下一个键盘敲得字符
    int itemClock[10] = {0};
    int Direction = 1; // 光标步进方向
    int interval = 0;
    int attackInterval = 8000;
    int sleep = 30;
    while (player.getCurrHP() > 0 && monster.getCurrHP() > 0) {//战斗循环，只要都没死就一直进行

        Sleep(sleep);


        next = ' ';
        if (_kbhit()) {//get键盘字符
            next = _getch();
        }

        // 电脑对玩家造成伤害
        char code;
        // 玩家逻辑
        if (next == '\r' || next == '\n' || next == 'a') {
            // 造成伤寒

            code = lower[0].getString()[lower[0].getCur()];


            if (code != '0' && next != 'a') {

                int damage = ((int)code - 48) * 2 + randInt(0, 1);
                monster.getDamaged(damage);
                showHP(player);
                player.getBackpack().printItemList(true);


                if (monster.getCurrHP() <= 0) {
                    return;
                }
                if (code == '1') {
                    for (int j = 0; j < 10; j++){
                        lower[0].changeColor(lower[0].getCur(), 4); //
                        lower[0].putWord(lower[0].getString(), level);
                        Sleep(30);

                        lower[0].changeColor(lower[0].getCur(), 8); //
                        lower[0].putWord(lower[0].getString(), level);
                        Sleep(30);
                    }


                } else{
                    for (int j = 0; j < 10; j++){
                        lower[0].changeColor(lower[0].getCur(), 4); //
                        lower[0].putWord(lower[0].getString(), level);
                        Sleep(40);

                        lower[0].changeColor(lower[0].getCur(), 6);
                        lower[0].putWord(lower[0].getString(), level);
                        Sleep(40);
                    }
                }

                lower[0].putWord(lower[0].getString(), level);
                showPlayerInfo("命中敌人! 造成" + std::to_string(damage)  + "点伤害");
                Sleep(500);
                cls();
                showHP(player);
                showPlayerInfo("按下 <Enter> 攻击");
                player.getBackpack().printItemList(true);
                lower[0].putWord("", level);

            }else if (next == 'a') {
                monster.getDamaged(monster.getCurrHP());
                showHP(player);
                if (monster.getCurrHP() <= 0) {
                    Sleep(500);
                    return;
                }
                Sleep(500);
                lower[0].putWord("", level);

            } else{
                // 没造成伤害 被怪物攻击
                // 更新指针 更新lower[0]
                lower[0].changeColor(lower[0].getCur(), 1); // 变为1
                player.setCurrHP(player.getCurrHP() - monster.getDamage());
                showHP(player);
                lower[0].putWord(lower[0].getString(), level);
                showPlayerInfo("未命中 反击扣除" + std::to_string(monster.getDamage()) + "点生命");
                Sleep(500);
                showHP(player);
                cls();
                showHP(player);
                player.getBackpack().printItemList(true);
                showPlayerInfo("按下 <Enter> 攻击");
                lower[0].putWord("", level);
            };  // 当前位置

            Direction = 1;

        } else if (next <= '9' && next >= '0') {  // 使用道具

            if (itemClock[next - '0'] == 0) {
                if (player.getBackpack().isItemExist(next - '0') && !player.getBackpack().useItem(next - '0')) {
                    useItem(player, player.getBackpack().getItemEffect(next - '0'));
                    showHP(player);
                    player.getBackpack().printItemList(true);
                }
            }
            if (player.getBackpack().isItemExist(next - '0')) {
                itemClock[next - '0'] = player.getBackpack().getItemClock(next - '0');
                showPlayerInfo("使用道具");
                Sleep(500);
                cls();
                showHP(player);
                player.getBackpack().printItemList(true);
            }

        }else {  // 按键无对应
            //
            int cur = lower[0].getCur();
            if (cur >= lower[0].getLength() - 1){
                Direction = -1;
            }
            if (cur <= 0 && Direction == -1){
                Direction = 1;
            }
            // 正向
            if (Direction > 0) {
                lower[0].changeCur(cur + 1);
                lower[0].changeColor(cur + 1, ColorLighted);
                lower[0].changeColor(cur, ColorDefault );

            }else{
                // 反向
                lower[0].changeCur(cur - 1);
                lower[0].changeColor(cur - 1, ColorLighted );
                lower[0].changeColor(cur, ColorDefault);
            }
        }


        // 道具逻辑判断
        for (int & i : itemClock) {
            if (i > 0) {
                i--;
            }
        }

        lower[0].putWord(lower[0].getString(), level);

        // 怪物攻击判断
        interval += sleep;
        if (interval > attackInterval){
            interval = 0;
            player.setCurrHP(player.getCurrHP() - monster.getDamage());
            showMonsterInfo("敌人发动攻击! 对你造成了" + std::to_string(monster.getDamage())  + "点伤害");
            showHP(player);
            player.getBackpack().printItemList(true);
            Sleep(500);
            cls();
            showHP(player);
            player.getBackpack().printItemList(true);
            continue;
        }

    }
}

void Fight::showPlayerInfo (const string& msg) {
    PosControl::setPos(8, 52);
    cout << msg;
}

void Fight::showMonsterInfo (const string& msg) {
    PosControl::setPos(5,  52);
    cout << msg;
}

void Fight::useItem(Player &player, int effect) {
    if (effect > 0) {
        player.getDamaged(-effect);
        if (player.getCurrHP() > player.getHP()) {
            player.resetCurrHP();
        }
    }
    if (effect < 0) {
        monster.getDamaged(-effect);
    }
}

void Fight::showScene(Backpack &backpack) {
    system("cls");
    ifstream sceneFile("./Assets/.fightFrame");
    string scene;
    while (getline(sceneFile, scene)) {
        cout << scene << endl;
    }
    sceneFile.close();
    PosControl::setPos(14, 0);
    printMsg("./Assets/Scene/BeforeFight/" + name + ".txt", true);
    PosControl::setPos(14, 0);
    // 清除四行
    for (int i = 0; i < 4; i++) {
        cout << "\33[2K" << endl;
    }
    PosControl::setPos(10, 17);
    backpack.printItemList(true);
}

bool Fight::checkWin(Player &player) {
    if (player.getCurrHP() <= 0) return false;
    return true;
}

void cls() {
    for (int i = 2; i <= 11; i++) {
        PosControl::setPos(i, 1);
        for (int j = 1; j < 105; j++) {
            cout << ' ';
        }
    }
}
//
//int Fight::checkWord(string s){
//    char c;
//    if (s=='破')
//    switch(c){
//
//        case '':
//            return 3
//    }
//}


#endif //GAMETOWER1_FIGHT_SCENE_H
