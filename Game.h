#pragma once
#include <iostream>
#include <string>

#include "Field.h"
#include "Player.h"

using namespace std;

class Game {
private:
    int game_status;
    Player current_player;
    Player next_player;

public:
    Game();

    void start_preparation();
    void in_game();
    void end_game();

    void status_switch();

    // определение типа расстановки кораблей и сама расстановка
    void type_placement_ships();
};
