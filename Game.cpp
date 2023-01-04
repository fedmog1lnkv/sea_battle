#include "Game.h"
#include "windows.h"

Game::Game() {
    game_status = 0;
    /* Статусы игры
    0 - подготовка
    1 - игра
    2 - конец игры
    */
}

void Game::start_preparation() {
    system("cls");

    string name_player1, name_player2;
    cout << "Введите имя игрока: ";
    cin >> name_player1;

    cout << "Введите имя игрока: ";
    cin >> name_player2;

    if (name_player1 == name_player2) {
        cout << "Имена игроков одинаковые\n		Перезагрузка..."
            << endl;
        Sleep(1500);
        start_preparation();
        return;
    }

    cout << "Выполняется жеребьёвка";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << "." << endl;
    Sleep(500);

    current_player.name = rand() % 2 ? name_player1 : name_player2;
    next_player.name =
        current_player.name == name_player2 ? name_player1 : name_player2;
    cout << "Первый ходит: " << current_player.name << endl;
    Sleep(2000);

    type_placement_ships();

    status_switch();

    return;
}

void Game::type_placement_ships() {
    int type_placement;
    system("cls");
    cout << current_player.name
        << ", как разместить корабли?\n[1] в ручную\n[2] автоматически"
        << endl;
    cin >> type_placement;
    if (type_placement == 1) {
        current_player.map.placement_ships();
    }
    else {
        current_player.map.auto_placement_ships();
    }

    system("cls");
    cout << "Переход к игроку: " << next_player.name << endl;
    cout << "Как разместить корабли?\n[1] в ручную\n[2] автоматически" << endl;
    cin >> type_placement;
    if (type_placement == 1) {
        next_player.map.placement_ships();
    }
    else {
        next_player.map.auto_placement_ships();
    }
}

void Game::status_switch() {
    if (game_status == 0) {
        game_status = 1;
        in_game();
    }

    if (game_status == 1) {
        in_game();
    }
    if (game_status == 1 && next_player.count_ships == 0) {
        game_status = 2;
        end_game();
    }
    in_game();
}

void Game::in_game() {
    system("cls");
    cout << "\nРАДАР" << endl;
    current_player.radar.show_field();
    cout << "\nКАРТА" << endl;
    current_player.map.show_field();

    string coords_for_attack;
    cout << "Ждём приказа, " << current_player.name << " : ";
    cin >> coords_for_attack;

    int status_attack = current_player.attack(next_player, coords_for_attack);
    if (status_attack == 0) {
        cout << "Мимо" << endl;
        swap(current_player, next_player);
        Sleep(1000);
    }
    if (status_attack == 1) {
        cout << "Корабль подбит" << endl;
        Sleep(500);
    }
    if (status_attack == 2) {
        cout << "Корабль уничтожен" << endl;
        Sleep(500);
    }
    if (status_attack == 3) {
        cout << "Выстрел по таким координатам уже был" << endl;
        Sleep(500);
    }

    status_switch();
}

void Game::end_game() {
    current_player.map.show_field();
    next_player.map.show_field();
}
