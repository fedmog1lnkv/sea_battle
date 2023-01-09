#include "Game.h"
#include "windows.h"

Game::Game() : game_status(GS_t::preparation) {}

void Game::startPreparation() {
    system("cls");

    string name_player1, name_player2;
    cout << "Введите имя игрока: ";
    cin >> name_player1;

    int second_player_is_bot;
    cout << "Сделать второго игрока ботом?\n[1] да\n[2] нет" << endl;
    cin >> second_player_is_bot;

    cout << "Введите имя игрока: ";
    cin >> name_player2;

    if (name_player1 == name_player2) {
        cout << "Имена игроков одинаковые\n		Перезагрузка..."
            << endl;
        Sleep(1500);
        startPreparation();
        return;
    }

    if (second_player_is_bot == 1) {
        next_player.is_bot = true;
        current_player.name = name_player1;
        next_player.name = name_player2;
    }
    else {
        current_player.name = rand() % 2 ? name_player1 : name_player2;
        next_player.name =
            current_player.name == name_player2 ? name_player1 : name_player2;

        cout << "Выполняется жеребьёвка";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << "." << endl;
        Sleep(500);
    }

    current_player.is_bot = true;

    cout << "Первый ходит: " << current_player.name << endl;
    Sleep(2000);

    typePlacementShips();

    statusSwitch();

    return;
}

void Game::inGame() {
    system("cls");
    if (current_player.is_bot == true) {
        coordinate attack_cell =
            current_player.radar.getCoordMaxWeightCell();
        string hint_move = current_player.map.getCoordsString(attack_cell);

        StatusAttack status_attack =
            current_player.attack(next_player, attack_cell);
        log(hint_move, status_attack);

        if (status_attack == SA_t::miss) {
            swap(current_player, next_player);
        }
        cout << "Бот атакует: " << hint_move << endl;
        cout << getDescriptionStatusAttack(status_attack) << endl;
        //system("pause");
    }

    else {
        cout << "\nРАДАР" << endl;
        current_player.radar.showField();
        cout << "\nКАРТА" << endl;
        current_player.map.showField();

        string coords_for_attack;

        if (current_player.helper == true) {
            coordinate attack_cell =
                current_player.radar.getCoordMaxWeightCell();
            string hint_move =
                current_player.map.getCoordsString(attack_cell);
            cout << "Боцман: атакуйте " << hint_move << endl;
        }

        cout << "Ждём приказа, " << current_player.name << " : ";
        cin >> coords_for_attack;

        coordinate attack_cell =
            current_player.map.getCoordsXY(coords_for_attack);
        StatusAttack status_attack =
            current_player.attack(next_player, attack_cell);
        log(coords_for_attack, status_attack);

        string d_status_attack = getDescriptionStatusAttack(status_attack);
        if (status_attack == SA_t::miss) {
            cout << d_status_attack << endl;
            swap(current_player, next_player);
            Sleep(1000);
        }
        else {
            cout << d_status_attack << endl;
            Sleep(500);
        }
    }

    statusSwitch();
}

void Game::endGame() {
    system("cls");
    cout << current_player.name << " выиграл!\n" << endl;
    cout << "ПОЛЕ " << current_player.name << endl;
    current_player.map.showField();
    cout << "\nПОЛЕ " << next_player.name << endl;
    next_player.map.showField();
    return;
}

void Game::statusSwitch() {
    if (game_status == GS_t::preparation) {
        ofstream log_file("log_file.txt");
        log_file << "Лог игры\n";
        log_file.close();
        game_status = GS_t::game;
        inGame();
    }

    if (game_status == GS_t::game && next_player.count_ships != 0) {
        inGame();
    }

    if (game_status == GS_t::game && next_player.count_ships <= 0) {
        game_status = GS_t::end;
        endGame();
    }
}

void Game::typePlacementShips() {
    int type_placement;
    system("cls");
    cout << current_player.name
        << ", как разместить корабли?\n[1] в ручную\n[2] автоматически"
        << endl;
    cin >> type_placement;
    if (type_placement == 1) {
        current_player.map.placementShips();
    }
    else {
        current_player.map.autoPlacementShips();
    }

    int on_helper;
    cout << "Включить помощника?\n[1] да\n[2] нет" << endl;
    cin >> on_helper;
    if (on_helper == 1) {
        current_player.helper = true;
    }

    if (next_player.is_bot == true) {
        next_player.map.autoPlacementShips();
        return;
    }
    system("cls");
    cout << "Переход к игроку: " << next_player.name << endl;
    cout << "Как разместить корабли?\n[1] в ручную\n[2] автоматически" << endl;
    cin >> type_placement;
    if (type_placement == 1) {
        next_player.map.placementShips();
    }
    else {
        next_player.map.autoPlacementShips();
    }
    cout << "Включить помощника?\n[1] да\n[2] нет" << endl;
    cin >> on_helper;

    if (on_helper == 1) {
        current_player.helper = true;
    }
}

void Game::log(const string& shoot_cell, StatusAttack status_attack) {
    ofstream log_file;
    log_file.open("log_file.txt", ios_base::app);
    if (status_attack == SA_t::miss || status_attack == SA_t::damage ||
        status_attack == SA_t::destroy && log_file.is_open()) {
        log_file << setw(20) << current_player.name << '\t' << setw(3)
            << shoot_cell << '\t' << setw(20)
            << getDescriptionStatusAttack(status_attack) << "\n";
    }
    log_file.close();
}

string Game::getDescriptionStatusAttack(StatusAttack status_attack) {
    switch (status_attack) {
    case SA_t::miss:
        return "Мимо";
    case SA_t::damage:
        return "Корабль подбит";
    case SA_t::destroy:
        return "Корабль уничтожен";
    case SA_t::already_use:
        return "Выстрел по таким координатам уже был";
    }
}

coordinate Game::getHelperCoord() {
    coordinate attack_cell;
    attack_cell = current_player.radar.getCoordMaxWeightCell();
    return attack_cell;
}
