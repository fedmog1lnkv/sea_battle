#pragma once
#include <iostream>
#include <string>

#include "EnumClasses.h"
using CSt_t = CellStatus;

using namespace std;

class Cell {
public:
    Cell();

    CellStatus status;

    int weight;

    string empty_cell = "∟ ";
    string ship_cell = "■ ";
    string damaged_ship = "□ ";
    string destroyed_ship = "X ";
    string miss_cell = "• ";

    // проверка пустая клетка или нет
    bool isBusy();

    friend ostream& operator<<(ostream& out, const Cell& status_cell);
};
