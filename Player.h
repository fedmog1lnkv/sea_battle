#pragma once
#include <iostream>

#include "EnumClasses.h"
#include "Field.h"

using CSt_t = CellStatus;
using SA_t = StatusAttack;

using namespace std;

class Player {
public:
    Player();

    string name;

    bool is_bot;
    bool helper;

    int count_ships;

    Field map;
    Field radar;

    StatusAttack attack(Player& player_for_attack, coordinate coords);
};