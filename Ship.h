#pragma once
#include <iostream>
#include <string>

struct coordinate {
    int x;
    int y;
};

using namespace std;

class Ship {
public:
    Ship(coordinate coords, int r, int type);
    Ship() {};

    coordinate start_coords;

    // 0 - вертикаль
    // 1 - горизонталь
    int rotate;

    int hp;
    int type_ship;
};