#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Cell.h"

using namespace std;
using CSt = Cell::Status;

constexpr int MAP_SIZE = 10;

struct coordinate {
    int x;
    int y;
};

class Field {
private:
    Cell board[MAP_SIZE][MAP_SIZE];

    // буквы для обозначения координат
    string letters = "ABCDEFGHIJ";

    // массив названий кораблей
    string name_ships[4] = { "торпедный катер", "эсминец", "крейсер", "линкор" };

    // количество каждого корабля (для проверок)
    int type_ships[MAP_SIZE] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 };

public:
    Field();
    void fill_map();

    coordinate get_coords_x_y(string coords);

    void placement_ships();
    void put_ship(int first_x, int first_y, int second_x, int second_y);

    // True - поставил, False - ошибка
    bool check_ship_placement(int first_x, int first_y, int second_x,
        int second_y, int type_ship, int is_player);
    void auto_placement_ships();

    void mark_destroyed_ship(int x, int y, string coord);

    // 0 - мимо
    // 1 - попал
    // 2 - убил
    // 3 - выстрел уже был
    int make_attack(string coords);

    void change_cell_radar(string coords, CSt new_status);

    void show_field();
};
