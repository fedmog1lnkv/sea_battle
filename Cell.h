#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cell {
public:
    int status;

    string empty_cell = "∟ ";      // 0
    string ship_cell = "■ ";       // 1
    string damaged_ship = "□ ";    // 2
    string destroyed_ship = "X ";  // 3
    string miss_cell = "• ";       // 4

    Cell();

    void set_cell_status(int st) { status = st; };

    bool is_busy();

    // string get_cell_image();

    friend ostream& operator<<(ostream& out, const Cell& status_cell);
};
