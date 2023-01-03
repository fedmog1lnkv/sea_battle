#include "Player.h"

int Player::attack(Player& player_for_attack, string coords) {
    int status_attack = player_for_attack.map.make_attack(coords);
    // 0 - мимо
    // 1 - ранил
    // 2 - убил
    // 3 - уже использована

    if (status_attack == 0) {
        this->radar.change_cell_radar(coords, 4);
    }
    else {
        if (status_attack == 1) {
            this->radar.change_cell_radar(coords, 2);
        }
        else {
            if (status_attack == 2) {
                this->radar.change_cell_radar(coords, 3);
                this->radar.mark_destroyed_ship(-1, -1, coords);
                count_ships--;
            }
        }
    }

    return status_attack;
}
