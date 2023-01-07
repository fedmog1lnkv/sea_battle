#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "EnumClasses.h"
#include "Field.h"
#include "Player.h"
using GS_t = GameStatus;
using SA_t = StatusAttack;

using namespace std;

class Game {
private:
    GameStatus game_status;
    Player current_player;
    Player next_player;

    string letters = "ABCDEFGHIJ";

public:
    Game();

    void start_preparation();
    void in_game();
    void end_game();

    void status_switch();

    // определение типа расстановки кораблей и сама расстановка
    void type_placement_ships();

    void log(string shoot_cell, StatusAttack status_attack);

    // возвращает описание атаки
    string description_status_attack(StatusAttack status_attack);

    // возвращает ход основываясь на весе поля
    coordinate get_helper_coord();
};