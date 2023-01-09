#include "Player.h"

Player::Player() : count_ships(10) {}

StatusAttack Player::attack(Player& player_for_attack, coordinate coords) {
    StatusAttack status_attack = player_for_attack.map.makeAttack(coords);

    switch (status_attack) {
    case SA_t::miss:
        this->radar.changeCellRadar(coords, CSt_t::miss_cell);
        break;
    case SA_t::damage:
        this->radar.changeCellRadar(coords, CSt_t::damaged_ship);
        break;
    case SA_t::destroy:
        this->radar.markDestroyedShipRadar(coords);
        player_for_attack.count_ships--;
        this->radar.recalculateWeightBoard();
    }

    return status_attack;
}
