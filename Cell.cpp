#include "Cell.h"

using CSt_t = Cell::Status;

Cell::Cell() : status(CSt_t::empty_cell) {}

bool Cell::is_busy() { return status != CSt_t::empty_cell; }

ostream& operator<<(ostream& out, const Cell& status_cell) {
    switch (status_cell.status) {
    case CSt_t::empty_cell:
        out << status_cell.empty_cell;
        break;
    case CSt_t::ship_cell:
        out << status_cell.ship_cell;
        break;
    case CSt_t::damaged_ship:
        out << status_cell.damaged_ship;
        break;
    case CSt_t::destroyed_ship:
        out << status_cell.destroyed_ship;
        break;
    case CSt_t::miss_cell:
        out << status_cell.miss_cell;
        break;
    default:
        break;
    }
    return out;
}
