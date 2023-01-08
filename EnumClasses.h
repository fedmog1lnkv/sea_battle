#pragma once

// статусы ячейки
enum class CellStatus {
    empty_cell = 0,    // 0 - пустая клетка
    ship_cell = 1,     // 1 - клетка с кораблём
    damaged_ship = 2,  // 2 - клетка с раненым кораблём
    destroyed_ship = 3,  // 3 - клетка с уничтоженным кораблём
    miss_cell = 4  // 4 - клетка с промахом
};

// статусы игры
enum class GameStatus {
    preparation = 0,  // 0 - подготовка
    game = 1,         // 1 - игра
    end = 2,          // 2 - конец игры
};

// типы атаки
enum class StatusAttack {
    miss = 0,         // 0 - мимо
    damage = 1,       // 1 - ранил
    destroy = 2,      // 2 - убил
    already_use = 3,  // 3 - уже использована
    error = -1        // -1 - ошибка
};