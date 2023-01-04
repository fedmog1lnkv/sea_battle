#include "Cell.h"

using CSt = Cell::Status;

Cell::Cell() : status(CSt::empty_cell) {}

bool Cell::is_busy() {
    return status != CSt::empty_cell;
}

ostream& operator<<(ostream& out, const Cell& status_cell) {
    switch (status_cell.status) {
    case CSt::empty_cell:
        out << status_cell.empty_cell;
        break;
    case CSt::ship_cell:
        out << status_cell.ship_cell;
        break;
    case CSt::damaged_ship:
        out << status_cell.damaged_ship;
        break;
    case CSt::destroyed_ship:
        out << status_cell.destroyed_ship;
        break;
    case CSt::miss_cell:
        out << status_cell.miss_cell;
        break;
    default:
        break;
    }
    return out;
}
