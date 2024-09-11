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


class FightScene {
public:
    FightScene(string name, int progress) : name(std::move(name)), monster(progress + 1) {};

//    FightScene(std::string id, int b);

    void loadScene(Player &player);//外部调用接口
    static bool checkWin(Player &player);
    //字符下落，由loadScene调用

    //调控打字变色并check，由loadScene调用


    ~FightScene() = default;

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

void FightScene::showHP(Player &player) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    PosControl::setPos(16, 1);
    cout << "MonsterHP:";
    int curhp, HP;
    curhp = std::max(0, monster.getCurrHP()), HP = monster.getHP();
    cout << curhp << '/' << HP;
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    PosControl::setPos(16, 1);
    cout << "MonsterHP:";
    cout << curhp << '/' << HP;
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }
    PosControl::setPos(21, 1);
    curhp = std::max(0, player.getCurrHP()), HP = player.getHP();
    cout << "PlayerHP:";
    cout << curhp << '/' << HP;
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    PosControl::setPos(21, 1);
    cout << "PlayerHP:";
    cout << curhp << '/' << HP;
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}

void FightScene::loadScene(Player &player) {//最主要的函数，万物的起源
    showScene(player.getBackpack());//打印一下边框
    PosControl::HideCursor();//隐藏光标
    std::vector<Stripe> upper, lower;//核心单词表，直接源自monster和player，分别代表上下
    upper = monster.deliverWord();
    player.init();
    lower = player.deliverWord();
    showHP(player);//显示初始血量
    typeAndColor(upper, lower, player);//核心函数，判断打字用的

}

void FightScene::typeAndColor(std::vector<Stripe> &upper, std::vector<Stripe> &lower, Player &player) {


    lower[0].putWord("");
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


                if (monster.getCurrHP() <= 0) {
                    return;
                }
                if (code == '1') {
                    for (int j = 0; j < 10; j++){
                        lower[0].changeColor(lower[0].getCur(), 4); // 变为金色
                        lower[0].putWord(lower[0].getString());
                        Sleep(30);

                        lower[0].changeColor(lower[0].getCur(), 8); // 变为金色
                        lower[0].putWord(lower[0].getString());
                        Sleep(30);
                    }


                } else{
                    for (int j = 0; j < 10; j++){
                        lower[0].changeColor(lower[0].getCur(), 4); // 变为金色
                        lower[0].putWord(lower[0].getString());
                        Sleep(40);

                        lower[0].changeColor(lower[0].getCur(), 6); // 变为金色
                        lower[0].putWord(lower[0].getString());
                        Sleep(40);
                    }
                }

                lower[0].putWord(lower[0].getString());
                showPlayerInfo("命中敌人! 造成" + std::to_string(damage)  + "点伤害");
                Sleep(500);
                cls();
                showPlayerInfo("按下 <Enter> 攻击");

                lower[0].putWord("");




            }else if (next == 'a') {
                monster.getDamaged(monster.getCurrHP());
                showHP(player);
                if (monster.getCurrHP() <= 0) {
                    Sleep(500);
                    return;
                }


                Sleep(500);
                lower[0].putWord("");

            } else{
                // 没造成伤害 被怪物攻击
                // 更新指针 更新lower[0]
                lower[0].changeColor(lower[0].getCur(), 1); // 变为1
                player.setCurrHP(player.getCurrHP() - monster.getDamage());
                showHP(player);
                lower[0].putWord(lower[0].getString());
                showPlayerInfo("未命中 反击扣除" + std::to_string(monster.getDamage()) + "点生命");
                Sleep(500);
                cls();

                showPlayerInfo("按下 <Enter> 攻击");
                lower[0].putWord("");
            };  // 当前位置

            Direction = 1;

        } else if (next <= '9' && next >= '0') {  // 使用道具



            if (itemClock[next - '0'] == 0) {
                if (player.getBackpack().isItemExist(next - '0') && !player.getBackpack().useItem(next - '0'))
                    useItem(player, player.getBackpack().getItemEffect(next - '0'));

            }
            if (player.getBackpack().isItemExist(next - '0')) {


                itemClock[next - '0'] = player.getBackpack().getItemClock(next - '0');
                showPlayerInfo("使用道具");
                Sleep(500);
                cls();
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

        lower[0].putWord(lower[0].getString());

        // 怪物攻击判断
        interval += sleep;
        if (interval > attackInterval){
            interval = 0;
            player.setCurrHP(player.getCurrHP() - monster.getDamage());
            showMonsterInfo("敌人发动攻击! 对你造成了" + std::to_string(monster.getDamage())  + "点伤害");
            showHP(player);
            Sleep(500);
            cls();
            continue;
        }

    }
}

void FightScene::showPlayerInfo (const string& msg) {
    PosControl::setPos(28, 40);
    cout << msg;
}

void FightScene::showMonsterInfo (const string& msg) {
    PosControl::setPos(8,  40);
    cout << msg;
}

void FightScene::useItem(Player &player, int effect) {
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

void FightScene::showScene(Backpack &backpack) {
    system("cls");
    ifstream sceneFile("./Assets/.fightScene");
    string scene;
    while (getline(sceneFile, scene)) {
        cout << scene << endl;
    }
    sceneFile.close();
    PosControl::setPos(17, 0);
    printMsg("./Assets/Scene/BeforeFight/" + name + ".txt", true);
    PosControl::setPos(17, 0);
    // 清除四行
    for (int i = 0; i < 4; i++) {
        cout << "\33[2K" << endl;
    }
    PosControl::setPos(17, 0);
    backpack.printItemList(1);
}

bool FightScene::checkWin(Player &player) {
    if (player.getCurrHP() <= 0) return false;
    return true;
}

void cls() {
    for (int i = 1; i <= 15; i++) {
        PosControl::setPos(i, 1);
        for (int j = 1; j < 101; j++) {
            cout << ' ';
        }
    }
    for (int i = 1; i <= 10; i++) {
        PosControl::setPos(i + 21, 1);
        for (int j = 1; j < 101; j++) {
            cout << ' ';
        }
    }
}


#endif //GAMETOWER1_FIGHT_SCENE_H
