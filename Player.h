﻿#pragma once
#include <iostream>

#include "Field.h"

using namespace std;

class Player {
public:
    string name;

    // 0 - не бот
    // 1 - бот
    int is_bot = 0;
    int count_ships = 10;

    Field map;
    Field radar;

    Player() = default;

    // 0 - мимо
    // 1 - ранил
    // 2 - убил
    // 3 - уже использована
    int attack(Player& player_for_attack, string coords);
};