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

    void startPreparation();
    void inGame();
    void endGame();

    void statusSwitch();

    // определение типа расстановки кораблей и сама расстановка
    void typePlacementShips();

    void log(const string& shoot_cell, StatusAttack status_attack);

    // возвращает описание атаки
    string getDescriptionStatusAttack(StatusAttack status_attack);

    // возвращает ход основываясь на весе поля
    coordinate getHelperCoord();
};