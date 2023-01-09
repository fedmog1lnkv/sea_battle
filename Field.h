#pragma once
#include <Windows.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Cell.h"
#include "EnumClasses.h"
#include "Ship.h"

using CSt_t = CellStatus;
using GS_t = GameStatus;
using SA_t = StatusAttack;

using namespace std;

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
    void fillMap();

    void deleteShip(int type_ship);

    // возвращает координаты из строки
    coordinate getCoordsXY(string coords);

    // делает из координаты строку
    string getCoordsString(coordinate cell);

    // проверка выходит ли x и y из поля
    bool checkArea(int x, int y);

    // расстановки кораблей
    void placementShips();
    void autoPlacementShips();
    void putShip(coordinate first, coordinate second);

    // проверка можно ли поставить корабль по заданным координатам
    bool checkShipPlacement(coordinate first, coordinate second, int type_ship, bool is_player);

    // возвращает статус атаки
    StatusAttack makeAttack(coordinate coords);

    // возвращает сколько у корабля осталось hp
    int injureShip(coordinate coord_ship);

    // отмечает на радаре уничтоженный корабль
    void markDestroyedShipRadar(coordinate coord);

    // меняет на радаре статус клетки
    void changeCellRadar(coordinate coords, CSt_t new_status);

    // возвращает индекс корабля в массиве ships
    Ship& findShip(coordinate coord_cell);

    // расчёт веса клеток на поле
    void recalculateWeightBoard();

    // поиск клетки с макисмальным весом
    coordinate getCoordMaxWeightCell();

    void showField();
};
