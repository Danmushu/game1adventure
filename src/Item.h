
#ifndef GAMETOWER1_ITEM_H
#define GAMETOWER1_ITEM_H

#include <iostream>
#include <utility>

class Item {
public:
    Item(std::string name, int effect, int cooldown)
            : name(std::move(name)), effect(effect), cooldown(cooldown) {}
    ~Item() = default;

    std::string getName() const { return name; }
    int getEffect() const { return effect; }
    int getCooldown() const { return cooldown; }

    int getClock() const { return cooldown; }

private:
    std::string name;
    int effect;
    int cooldown;
};

#endif //GAMETOWER1_ITEM_H
