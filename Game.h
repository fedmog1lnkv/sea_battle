#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Field.h"
#include "Player.h"

using namespace std;

class Game {
private:
    // Статусы игры
    // 0 - подготовка
    // 1 - игра
    // 2 - конец игры
    int game_status;
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

    void log(string shoot_cell, int status_attack);

    // возвращает описание атаки
    string description_status_attack(int status_atack);

    // возвращает ход основываясь на весе поля
    coordinate get_helper_coord();
};
