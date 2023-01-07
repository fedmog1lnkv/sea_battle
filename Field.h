#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

#include "Cell.h"
#include "Ship.h"

using namespace std;
using CSt_t = Cell::Status;

constexpr int MAP_SIZE = 10;

class Field {
private:
    Cell board[MAP_SIZE][MAP_SIZE];

    // буквы для обозначения координат
    string letters = "ABCDEFGHIJ";

    // массив названий кораблей
    string name_ships[4] = { "торпедный катер", "эсминец", "крейсер", "линкор" };

    // количество каждого корабля (для проверок)
    int type_ships[MAP_SIZE] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 };

    // список кораблей
    Ship ships[10];

public:
    // переместить в приват

    Field();
    void fill_map();

    void delete_ship(int type_ship);

    // возвращает координаты из строки
    coordinate get_coords_x_y(string coords);

    // делает из координаты строку
    string get_coords_string(coordinate cell);

    // проверка выходит ли x и y из поля
    bool check_area(int x, int y);

    // расстановки кораблей
    void placement_ships();
    void auto_placement_ships();
    void put_ship(int first_x, int first_y, int second_x, int second_y);

    // проверка можно ли поставить корабль по заданным координатам
    bool check_ship_placement(int first_x, int first_y, int second_x,
        int second_y, int type_ship, bool is_player);

    // возвращает статус атаки
    // 0 - мимо
    // 1 - попал
    // 2 - убил
    // 3 - выстрел уже был
    int make_attack(coordinate coords);

    // возвращает сколько у корабля осталось hp
    int injure_ship(coordinate coord_ship);

    // отмечает на радаре уничтоженный корабль
    void mark_destroyed_ship_radar(int x_coord, int y_coord);

    // меняет на радаре статус клетки
    void change_cell_radar(coordinate coords, CSt_t new_status);

    // возвращает индекс корабля в массиве ships
    Ship& find_ship(coordinate coord_cell);

    // расчёт веса клеток на поле
    void recalculate_weight_board();

    // поиск клетки с макисмальным весом
    coordinate get_coord_max_weight_cell();

    void show_field();
};
