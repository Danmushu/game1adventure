#ifndef GAMETOWER1_FIGHT_SCENE_H
#define GAMETOWER1_FIGHT_SCENE_H
#define getPlaceName(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getName()

#include <utility>
#include <vector>
#include "Monster.h"
#include <ctime>
#include <random>
#include "Interface.h"
#include "Bar.h"
#include "Player.h"
#include "Map.h"
#include "run.h"


const int ColorLighted = 5;
const int ColorDefault = 8;

void cls();

class Fight {
public:
    Fight(string name, int progress) : name(std::move(name)), monster(progress + 1) {};

    void loadScene(Player &player);//�ⲿ���ýӿ�
    static bool checkWin(Player &player);

    ~Fight() = default;

private:
    Monster monster;//��������ԵĹ���
    std::string name;

    void showScene(Backpack &backpack);

    void showHP(Player &player);

    void typeAndColor(std::vector<Bar> &upper, std::vector<Bar> &lower, Player &player);

    void useItem(Player &player, int effect);

    void updateScene(Player& player);

    static void showPlayerInfo(const string& msg);

    static void showMonsterInfo(const string& msg);
};

void Fight::showHP(Player &player)     {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
//    Interface::setPos(16, 1);
    Interface::setPos(3, 11);
    cout << monster.getName() ;
    Interface::setPos(4, 11);
    cout<< "[��Ѫ]";
    int curhp, HP;
    curhp = std::max(0, monster.getCurrHP()), HP = monster.getHP();
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
//    Interface::setPos(16, 1);
    Interface::setPos(3, 11);
    cout << monster.getName() ;
    Interface::setPos(4, 11);
    cout << "[��Ѫ]";
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    Interface::setPos(5, 11);
    curhp = std::max(0, player.getCurrHP()), HP = player.getHP();
    cout << player.getName();
    Interface::setPos(6, 11);
    cout<<"[��Ѫ]";
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    Interface::setPos(5, 11);
    cout << player.getName() ;
    Interface::setPos(6, 11);
    cout << "[��Ѫ]";
    cout << curhp << '/' << HP;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}

//�ⲿ�ӿ�
void Fight::loadScene(Player &player) {
    showScene(player.getBackpack());//�߿����
    Interface::HideCursor();//���ع��
    std::vector<Bar> upper, lower;//���ش����
    upper = monster.deliverWord();
    player.init();
    lower = player.deliverWord();
    showHP(player);//��ʾ��ʼѪ��
    typeAndColor(upper, lower, player);//���ĺ������жϴ��
}

void Fight::typeAndColor(std::vector<Bar> &upper, std::vector<Bar> &lower, Player &player) {
    int levelPlayer = player.getLevel();
    int levelMonster = monster.getLevel();
    lower[0].putWord("", levelPlayer);
    char next = ' '; //next����һ�������õ��ַ�
    int itemClock[10] = {0};
    int Direction = 1; // ��경������
    int interval = 0;
    int attackInterval = 8000;
    int sleep = 30;
    while (player.getCurrHP() > 0 && monster.getCurrHP() > 0) {//ս��ѭ����ֻҪ��û����һֱ����
        Sleep(sleep-levelMonster);
        next = ' ';
        if (_kbhit()) {//get�����ַ�
            next = _getch();
        }
        // ���Զ��������˺�
        char code;
        // ����߼�
        if (next == '\r' || next == '\n' || next == 'a') {
            // ����˺�
            code = lower[0].getString()[lower[0].getCur()];
            if (code != '0' && next != 'a') {
                int damage = ((int)code - 48) * 2 + Interface::randInt(0, 1);
                monster.getDamaged(damage);
                showHP(player);
                player.getBackpack().printItemList(true);
                if (monster.getCurrHP() <= 0) {
                    return;
                }
                //��˸���߼�
                if (code == '1') {
                    for (int j = 0; j < 10; j++){
                        lower[0].changeColor(lower[0].getCur(), 4); //
                        lower[0].putWord(lower[0].getString(), levelPlayer);
                        Sleep(30);

                        lower[0].changeColor(lower[0].getCur(), 8); //
                        lower[0].putWord(lower[0].getString(), levelPlayer);
                        Sleep(30);
                    }


                } else{
                    for (int j = 0; j < 10; j++){
                        lower[0].changeColor(lower[0].getCur(), 4); //
                        lower[0].putWord(lower[0].getString(), levelPlayer);
                        Sleep(40);

                        lower[0].changeColor(lower[0].getCur(), 6);
                        lower[0].putWord(lower[0].getString(), levelPlayer);
                        Sleep(40);
                    }
                }
                lower[0].putWord(lower[0].getString(), levelPlayer);
                showPlayerInfo("���е���! ���" + std::to_string(damage)  + "���˺�");
                Sleep(500);
                cls();
                showHP(player);
                showPlayerInfo("���� <Enter> ����");
                player.getBackpack().printItemList(true);
                lower[0].putWord("", levelPlayer);
            }else if (next == 'a') {
                monster.getDamaged(monster.getCurrHP());
                showHP(player);
                if (monster.getCurrHP() <= 0) {
                    Sleep(500);
                    return;
                }
                Sleep(500);
                lower[0].putWord("", levelPlayer);
            } else{
                // û����˺� �����﹥��
                // ���¹�� ����lower[0]
                lower[0].changeColor(lower[0].getCur(), 1); // ��Ϊ1
                player.setCurrHP(player.getCurrHP() - monster.getDamage());
                showHP(player);
                lower[0].putWord(lower[0].getString(), levelPlayer);
                showPlayerInfo("δ���� �����۳�" + std::to_string(monster.getDamage()) + "������");
                Sleep(500);
                showHP(player);
                updateScene(player);
                showPlayerInfo("���� <Enter> ����");
                lower[0].putWord("", levelPlayer);
            };  // ��ǰλ��
            Direction = 1;
        } else if (next <= '9' && next >= '0') {  // ʹ�õ���

            if (itemClock[next - '0'] == 0) {
                if (player.getBackpack().isItemExist(next - '0') && !player.getBackpack().useItem(next - '0')) {
                    useItem(player, player.getBackpack().getItemEffect(next - '0'));
                    showHP(player);
                    player.getBackpack().printItemList(true);
                }
            }
            if (player.getBackpack().isItemExist(next - '0')) {
                itemClock[next - '0'] = player.getBackpack().getItemClock(next - '0');
                showPlayerInfo("ʹ�õ���");
                Sleep(500);
                updateScene(player);
            }
        }else {  // �����޶�Ӧ
            int cur = lower[0].getCur();
            if (cur >= lower[0].getLength() - 1){
                Direction = -1;
            }
            if (cur <= 0 && Direction == -1){
                Direction = 1;
            }
            // ����
            if (Direction > 0) {
                lower[0].changeCur(cur + 1);
                lower[0].changeColor(cur + 1, ColorLighted);
                lower[0].changeColor(cur, ColorDefault );

            }else{
                // ����
                lower[0].changeCur(cur - 1);
                lower[0].changeColor(cur - 1, ColorLighted );
                lower[0].changeColor(cur, ColorDefault);
            }
        }
        // �����߼��ж�
        for (int & i : itemClock) {
            if (i > 0) {
                i--;
            }
        }
        lower[0].putWord(lower[0].getString(), levelPlayer);
        // ���﹥���ж�
        interval += sleep;
        if (interval > attackInterval){
            interval = 0;
            player.setCurrHP(player.getCurrHP() - monster.getDamage());
            showMonsterInfo("���˷�������! ���������" + std::to_string(monster.getDamage())  + "���˺�");
            showHP(player);
            player.getBackpack().printItemList(true);
            Sleep(500);
            updateScene(player);
            continue;
        }
    }
}

void Fight::showPlayerInfo (const string& msg) {
    Interface::setPos(8, 52);
    cout << msg;
}

void Fight::showMonsterInfo (const string& msg) {
    Interface::setPos(5, 52);
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
    ifstream sceneFile("./assets/.fightFrame");
    string scene;
    while (getline(sceneFile, scene)) {
        cout << scene << endl;
    }
    sceneFile.close();
    Interface::setPos(14, 0);
    Interface::printMsg("./assets/Scene/BeforeFight/" + name + ".txt", true);
    Interface::setPos(14, 0);
    // �������
    for (int i = 0; i < 4; i++) {
        cout << "\33[2K" << endl;
    }
    Interface::setPos(10, 17);
    backpack.printItemList(true);
}

bool Fight::checkWin(Player &player) {
    if (player.getCurrHP() <= 0) return false;
    return true;
}

void cls() {
    for (int i = 2; i <= 11; i++) {
        Interface::setPos(i, 1);
        for (int j = 1; j < 105; j++) {
            cout << ' ';
        }
    }
}

void Fight::updateScene(Player& player) {
    cls();
    showHP(player);
    player.getBackpack().printItemList(true);
}


#endif //GAMETOWER1_FIGHT_SCENE_H
