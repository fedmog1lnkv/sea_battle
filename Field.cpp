#include <algorithm>

#include "Field.h"

Field::Field() { fill_map(); }

#define FOR_MAP                  \
    for (int y = 0; y < 10; y++) \
        for (int x = 0; x < 10; x++)

void Field::fill_map() {
    FOR_MAP
        board[y][x] = Cell();
}

void Field::delete_ship(int type_ship) {
    for (int ship = 0; ship < 10; ship++) {
        if (type_ships[ship] == type_ship) {
            type_ships[ship] = 0;
            return;
        }
    }
}

coordinate Field::get_coords_x_y(string coords) {
    transform(coords.begin(), coords.end(), coords.begin(), ::toupper);
    coordinate point;

    point.x = static_cast<int>(letters.find(coords[0]));
    // проверка на длину
    point.y = coords.length() == 3 ? 9 : coords[1] - '0' - 1;
    return point;
}

string Field::get_coords_string(coordinate cell) {
    string hint_move;
    hint_move.push_back(letters[cell.x]);
    hint_move += to_string(cell.y + 1);
    return hint_move;
}

bool Field::check_area(int x, int y) {
    return (x < 0 || x > 9 || y < 0 || y > 9);
}

void Field::placement_ships() {
    cout << "Расставьте корабли" << endl;
    cout << "Координаты носа : Координаты кормы" << endl;

    string coords, bow, stern;
    for (int i = 9; i > -1; i--) {
        system("cls");

        show_field();

        cout << "Куда поставить " << name_ships[type_ships[i] - 1] << "?"
            << endl;
        while (true) {
            cin >> coords;

            // верхний регистр
            transform(coords.begin(), coords.end(), coords.begin(), ::toupper);
            int first_x, first_y, second_x, second_y;

            // расстановка однопалубного
            if (type_ships[i] == 1) {
                if (coords.length() == 3) {
                    bow = string(begin(coords), begin(coords) + 3);
                }
                else {
                    bow = string(begin(coords), begin(coords) + 2);
                }
                stern = bow;
            }
            else {
                if (string(begin(coords) + 2, begin(coords) + 3) == "0") {
                    bow = string(begin(coords), begin(coords) + 3);
                }
                else {
                    bow = string(begin(coords), begin(coords) + 2);
                }

                if (string(end(coords) - 1, end(coords)) == "0") {
                    stern = string(end(coords) - 3, end(coords));
                }
                else {
                    stern = string(end(coords) - 2, end(coords));
                }
            }

            coordinate first_coords = get_coords_x_y(bow);
            coordinate second_coords = get_coords_x_y(stern);

            first_x = first_coords.x;
            first_y = first_coords.y;
            second_x = second_coords.x;
            second_y = second_coords.y;

            // сортировка координат, т.к. всегда две координаты должны быть
            // одинаковые
            if (first_x == second_x) {
                if (first_y > second_y) {
                    swap(first_y, second_y);
                }
            }
            else {
                if (first_y == second_y) {
                    if (first_x > second_x) {
                        swap(first_x, second_x);
                    }
                }
            }

            if (check_ship_placement(first_x, first_y, second_x, second_y,
                type_ships[i], true)) {
                coordinate start_coords;
                start_coords.x = first_x;
                start_coords.y = first_y;
                int rotate;
                if (first_x == second_x) {
                    rotate = 0;
                }
                else {
                    rotate = 1;
                }
                ships[i] = Ship(start_coords, rotate, type_ships[i]);
                put_ship(first_x, first_y, second_x, second_y);
                break;
            }
        }
    }
}

bool Field::check_ship_placement(int first_x, int first_y, int second_x,
    int second_y, int type_ship, bool is_player) {
    if (check_area(first_x, first_y) || check_area(second_x, second_y)) {
        if (is_player == true) {
            cout << "Вернитесь в зону боевых действий" << endl;
            Sleep(1000);
        }
        return false;
    }

    int lenght_ship =
        static_cast<int>(sqrt(pow(second_x + 1 - first_x + 1, 2) +
            pow(second_y + 1 - first_y + 1, 2)) -
            1);

    if (lenght_ship != type_ship) {
        if (is_player == true) {
            cout << "Неверная длина корабля" << endl;
            Sleep(1000);
        }
        return false;
    }

    if (first_x != second_x && first_y != second_y) {
        if (is_player == true) {
            cout << "Неверные координаты расстановки" << endl;
            Sleep(1000);
        }
        return false;
    }

    // пробежка по координатам вокруг
    for (int x = first_x - 1; x <= second_x + 1; x++) {
        for (int y = first_y - 1; y <= second_y + 1; y++) {
            // проверка выхода из поля
            if (check_area(x, y)) {
                continue;
            }
            if (board[y][x].is_busy()) {
                if (is_player == true) {
                    cout << "Рядом стоит другой корабль" << endl;
                    Sleep(1000);
                }
                return false;
            }
        }
    }
    return true;
}

void Field::auto_placement_ships() {
    for (int i = 9; i > -1; i--) {
        int first_x, first_y, second_x, second_y;

        while (true) {
            // 0 - вертикаль
            // 1 - горизонталь
            int rand_rotate = rand() % 2;

            int rand_start_coords_x = (rand() % 10);
            int rand_start_coords_y = (rand() % 10);

            if (rand_rotate == 0) {
                first_x = rand_start_coords_x;
                first_y = rand_start_coords_y;
                second_x = rand_start_coords_x;
                second_y = rand_start_coords_y + type_ships[i] - 1;
            }
            else {
                first_x = rand_start_coords_x;
                first_y = rand_start_coords_y;
                second_x = rand_start_coords_x + type_ships[i] - 1;
                second_y = rand_start_coords_y;
            }

            if (check_ship_placement(first_x, first_y, second_x, second_y,
                type_ships[i], false)) {
                coordinate start_coords;
                start_coords.x = rand_start_coords_x;
                start_coords.y = rand_start_coords_y;
                ships[i] = Ship(start_coords, rand_rotate, type_ships[i]);
                put_ship(first_x, first_y, second_x, second_y);

                break;
            }
        }
    }
}

void Field::put_ship(int first_x, int first_y, int second_x, int second_y) {
    for (int x = first_x; x <= second_x; x++) {
        for (int y = first_y; y <= second_y; y++) {
            board[y][x].status = CSt_t::ship_cell;
            board[y][x].weight = 7;
        }
    }
}

void Field::mark_destroyed_ship_radar(int x_coord, int y_coord) {
    board[y_coord][x_coord].status = CSt_t::destroyed_ship;
    for (int x = x_coord - 1; x <= x_coord + 1; x++) {
        for (int y = y_coord - 1; y <= y_coord + 1; y++) {
            if (x < 0 || x > 9 || y < 0 || y > 9 ||
                (x == x_coord && y == y_coord)) {
                continue;
            }
            if (board[y][x].status == CSt_t::empty_cell) {
                board[y][x].status = CSt_t::miss_cell;
            }
            if (board[y][x].status == CSt_t::damaged_ship) {
                board[y][x].status = CSt_t::destroyed_ship;
                mark_destroyed_ship_radar(x, y);
            }
        }
    }
    recalculate_weight_board();
}

StatusAttack Field::make_attack(coordinate coords) {
    if (coords.x == -1 || coords.y == -1) {
        return SA_t::error;
    }

    // если в клеточке уже что-то происходило
    if (board[coords.y][coords.x].status == CSt_t::damaged_ship ||
        board[coords.y][coords.x].status == CSt_t::destroyed_ship ||
        board[coords.y][coords.x].status == CSt_t::miss_cell) {
        return SA_t::already_use;
    }

    // если в клеточке ничего нет
    if (board[coords.y][coords.x].status == CSt_t::empty_cell) {
        board[coords.y][coords.x].status = CSt_t::miss_cell;
        return SA_t::miss;
    }

    // если в клеточке корабль
    if (board[coords.y][coords.x].status == CSt_t::ship_cell) {
        int hp = injure_ship(coords);
        if (hp > 0) {
            board[coords.y][coords.x].status = CSt_t::damaged_ship;
            return SA_t::damage;
        }
        // убил
        else {
            mark_destroyed_ship_radar(coords.x, coords.y);
            return SA_t::destroy;
        }
    }
    return SA_t::error;
}

int Field::injure_ship(coordinate coord_attack_ship) {
    Ship& attacked_ship = find_ship(coord_attack_ship);
    attacked_ship.hp--;
    return attacked_ship.hp;
}

Ship& Field::find_ship(coordinate coord_cell) {
    for (int ship = 0; ship < 10; ship++) {
        for (int lenght_ship = 0; lenght_ship <= ships[ship].type_ship;
            lenght_ship++) {
            if (ships[ship].rotate == 0) {
                if ((ships[ship].start_coords.y + lenght_ship) ==
                    coord_cell.y &&
                    ships[ship].start_coords.x == coord_cell.x) {
                    return ships[ship];
                }
            }
            else {
                if ((ships[ship].start_coords.x + lenght_ship) ==
                    coord_cell.x &&
                    ships[ship].start_coords.y == coord_cell.y) {
                    return ships[ship];
                }
            }
        }
    }
}

void Field::change_cell_radar(coordinate coords, CSt_t new_status) {
    board[coords.y][coords.x].status = new_status;
    recalculate_weight_board();
}

void Field::recalculate_weight_board() {
    FOR_MAP
        board[y][x].weight = 1;

    FOR_MAP
        if (board[y][x].status == CSt_t::damaged_ship) {
            board[y][x].weight = 0;

            if (x - 1 >= 0) {
                if (y - 1 >= 0) {
                    board[y - 1][x - 1].weight = 0;
                }
                board[y][x - 1].weight *= 10;
                if (y + 1 < 10) {
                    board[y + 1][x - 1].weight = 0;
                }
            }

            if (y - 1 >= 0) {
                board[y - 1][x].weight *= 10;
            }
            if (y + 1 < 10) {
                board[y + 1][x].weight *= 10;
            }

            if (x + 1 < 10) {
                if (y - 1 >= 0) {
                    board[y - 1][x + 1].weight = 0;
                }
                board[y][x + 1].weight *= 10;
                if (y + 1 < 10) {
                    board[y + 1][x + 1].weight = 0;
                }
            }
        }

    // пробежка по всем координатам и чек можно ли хоть как-то поставить
    // оставшиеся корабли
    for (int ship = 0; ship < 10; ship++) {
        if (ships[ship].hp != 0) {
            FOR_MAP{
                if (board[y][x].status == CSt_t::damaged_ship ||
                    board[y][x].status == CSt_t::destroyed_ship ||
                    board[y][x].status == CSt_t::miss_cell) {
                    board[y][x].weight = 0;
                    continue;
                }
                if (check_ship_placement(x, y, x + ships[ship].type_ship, y,
                                         ships[ship].type_ship, false) ||
                    check_ship_placement(x, y, x, y + ships[ship].type_ship,
                                         ships[ship].type_ship, false)) {
                    board[y][x].weight++;
                }
            }
        }
    }
}

coordinate Field::get_coord_max_weight_cell() {
    map<int, coordinate> weights_cells;
    int max_weight = 0;

    FOR_MAP
        if (board[y][x].weight > max_weight) {
            max_weight = board[y][x].weight;
            weights_cells[board[y][x].weight] = { x, y };
        }

    if (max_weight == 1) {
        coordinate temp_coord = { rand() % 10, rand() % 10 };
        while (board[temp_coord.y][temp_coord.x].is_busy()) {
            temp_coord = { rand() % 10, rand() % 10 };
        }

        return temp_coord;
    }

    auto it = weights_cells.find(max_weight);
    if (it != weights_cells.end()) {
        return it->second;
    }

    return { rand() % 10, rand() % 10 };
}

void Field::show_field() {
    cout << setw(3) << " ";
    for (int i = 0; i < letters.size(); i++) {
        cout << setw(1) << letters[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i + 1 << ' ';
        for (int j = 0; j < 10; j++) {
            cout << setw(2) << board[i][j];
        }
        cout << endl;
    }
}