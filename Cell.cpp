#include "Cell.h"

Cell::Cell() { status = 0; }

bool Cell::is_busy() {
    if (status != 0) {
        return true;
    }
    return false;
}

ostream& operator<<(ostream& out, const Cell& status_cell) {
    switch (status_cell.status) {
    case 0:
        out << status_cell.empty_cell;
        break;
    case 1:
        out << status_cell.ship_cell;
        break;
    case 2:
        out << status_cell.damaged_ship;
        break;
    case 3:
        out << status_cell.destroyed_ship;
        break;
    case 4:
        out << status_cell.miss_cell;
        break;
    }
    return out;
}
