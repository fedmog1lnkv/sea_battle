#include "Player.h"

using CSt = Cell::Status;

int Player::attack(Player& player_for_attack, string coords) {

    // 0 - мимо
    // 1 - ранил
    // 2 - убил
    // 3 - уже использована
    int status_attack = player_for_attack.map.make_attack(coords);
    
    switch (status_attack)
    {
    case 0:
        this->radar.change_cell_radar(coords, CSt::miss_cell);
        break;
    case 1:
        this->radar.change_cell_radar(coords, CSt::damaged_ship);
        break;
    case 2:
        this->radar.change_cell_radar(coords, CSt::destroyed_ship);
        this->radar.mark_destroyed_ship(-1, -1, coords);
        count_ships--;
    default:
        break;
    }

    return status_attack;
}
