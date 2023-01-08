#include "Player.h"

Player::Player() : count_ships(10) {}

StatusAttack Player::attack(Player& player_for_attack, coordinate coords) {
    StatusAttack status_attack = player_for_attack.map.make_attack(coords);

    switch (status_attack) {
    case SA_t::miss:
        this->radar.change_cell_radar(coords, CSt_t::miss_cell);
        break;
    case SA_t::damage:
        this->radar.change_cell_radar(coords, CSt_t::damaged_ship);
        break;
    case SA_t::destroy:
        this->radar.mark_destroyed_ship_radar(coords);
        player_for_attack.count_ships--;
        this->radar.recalculate_weight_board();
    default:
        break;
    }

    return status_attack;
}
