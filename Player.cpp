#include "Player.h"

using CSt_t = Cell::Status;

Player::Player() {}

int Player::attack(Player& player_for_attack, coordinate coords) {

    // 0 - мимо
    // 1 - ранил
    // 2 - убил
    // 3 - уже использована
    int status_attack = player_for_attack.map.make_attack(coords);

    switch (status_attack) {
    case 0:
        this->radar.change_cell_radar(coords, CSt_t::miss_cell);
        break;
    case 1:
        this->radar.change_cell_radar(coords, CSt_t::damaged_ship);
        break;
    case 2:
        this->radar.mark_destroyed_ship_radar(coords.x, coords.y);
        player_for_attack.count_ships--;
    default:
        break;
    }

    return status_attack;
}
