#include "Ship.h"

Ship::Ship(coordinate coords, int r, int type) {
    start_coords = coords;
    rotate = r;
    hp = type;
    type_ship = type;
}