#include <algorithm>

#include "Field.h"


Field::Field() { fill_map(); }

#define FOR_MAP for(int i=0;i<10; i++) for (int j=0; j<10; j++)

void Field::fill_map() {
    FOR_MAP 
        board[i][j] = Cell();
}

coordinate Field::get_coords_x_y(string coords) {
    transform(coords.begin(), coords.end(), coords.begin(), ::toupper);
    coordinate point;

    point.x = static_cast<int>(letters.find(coords[0]));
    // проверка на длину
    if (coords.length() == 3) {
        point.y = 9;
    }
    else {
        point.y = coords[1] - '0' - 1;
    }
    return point;
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
            cin >> coords;  // "B1 : C4"

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

            // cout << bow << " " << stern << endl;

            // cout << first_x << first_y << " " << second_x << second_y <<
            // endl;

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
                type_ships[i], 1)) {
                put_ship(first_x, first_y, second_x, second_y);
                break;
            }
        }
    }
}

bool Field::check_ship_placement(int first_x, int first_y, int second_x,
    int second_y, int type_ship, int is_player) {
    // cout << first_x << first_y << " " << second_x << second_y << endl;

    if (type_ship == 1) {
        for (int x = first_x - 1; x <= second_x + 1; x++) {
            for (int y = first_y - 1; y <= second_y + 1; y++) {
                // проверка выхода из поля
                if (x < 0 || x > 9 || y < 0 || y > 9) {
                    continue;
                }
                if (board[y][x].is_busy()) {
                    if (is_player == 1) {
                        cout << "Рядом стоит другой корабль" << endl;
                    }
                    return false;
                }
            }
        }
        return true;
    }

    if (first_x > 9 || first_y > 9 || second_x > 9 || second_y > 9 ||
        first_x < 0 || first_y < 0 || second_x < 0 || second_y < 0) {
        if (is_player == 1) {
            cout << "Вернитесь в зону боевых действий" << endl;
        }
        return false;
    }

    int lenght_ship =
        static_cast<int>(sqrt(pow(second_x + 1 - first_x + 1, 2) +
            pow(second_y + 1 - first_y + 1, 2)) -
            1);
    // cout << lenght_ship << " " << first_x << first_y << " " << second_x <<
    // second_y << endl;

    if (lenght_ship != type_ship) {
        if (is_player == 1) {
            cout << "Неверная длина корабля" << endl;
        }
        return false;
    }

    if (first_x != second_x && first_y != second_y) {
        if (is_player == 1) {
            cout << "Неверные координаты расстановки" << endl;
        }
        return false;
    }

    // пробежка по координатам вокруг
    for (int x = first_x - 1; x <= second_x + 1; x++) {
        for (int y = first_y - 1; y <= second_y + 1; y++) {
            // проверка выхода из поля
            if (x < 0 || x > 9 || y < 0 || y > 9) {
                continue;
            }
            if (board[y][x].is_busy()) {
                if (is_player == 1) {
                    cout << "Рядом стоит другой корабль" << endl;
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

            int rand_start_coords_x = (rand() % 9);
            int rand_start_coords_y = (rand() % 9);

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
                type_ships[i], 0)) {
                put_ship(first_x, first_y, second_x, second_y);
                break;
            }
        }
    }
}

void Field::put_ship(int first_x, int first_y, int second_x, int second_y) {
    for (int x = first_x; x <= second_x; x++) {
        for (int y = first_y; y <= second_y; y++) {
            board[y][x].status = CSt::ship_cell;
        }
    }
}

void Field::mark_destroyed_ship(int x_coord, int y_coord, string coord = "") {
    if (coord != "") {
        coordinate cell_coord = get_coords_x_y(coord);
        x_coord = cell_coord.x;
        y_coord = cell_coord.y;
    }

    for (int x = x_coord - 1; x <= x_coord + 1; x++) {
        for (int y = y_coord - 1; y <= y_coord + 1; y++) {
            if (x < 0 || x > 9 || y < 0 || y > 9 ||
                (x == x_coord && y == y_coord)) {
                continue;
            }
            if (board[y][x].status == CSt::empty_cell) {
                board[y][x].status = CSt::miss_cell;
            }
            if (board[y][x].status == CSt::damaged_ship) {
                board[y][x].status = CSt::destroyed_ship;
                mark_destroyed_ship(x, y);
            }
        }
    }
}

int Field::make_attack(string coords) {
    coordinate cell_coord = get_coords_x_y(coords);
    if (cell_coord.x == -1 || cell_coord.y == -1) {
        return -1;
    }
    // cout << cell_coord.x << " " << cell_coord.y << endl;

    // если в клеточке уже что-то происходило
    if (board[cell_coord.y][cell_coord.x].status == CSt::damaged_ship ||
        board[cell_coord.y][cell_coord.x].status == CSt::destroyed_ship ||
        board[cell_coord.y][cell_coord.x].status == CSt::miss_cell) {
        return 3;
    }

    // если в клеточке ничего нет
    if (board[cell_coord.y][cell_coord.x].status == CSt::empty_cell) {
        board[cell_coord.y][cell_coord.x].status = CSt::miss_cell;
        return 0;
    }

    // если в клеточке корабль
    if (board[cell_coord.y][cell_coord.x].status == CSt::ship_cell) {
        // проверка есть ли у корабля продолжение
        bool ind_ship_nearby = false;
        for (int x = cell_coord.x - 1; x <= cell_coord.x + 1; x++) {
            for (int y = cell_coord.y - 1; y <= cell_coord.y + 1; y++) {
                if (x < 0 || x > 9 || y < 0 || y > 9 ||
                    (cell_coord.x == x && cell_coord.y == y)) {
                    continue;
                }
                if (board[y][x].status == CSt::ship_cell) {
                    ind_ship_nearby = true;
                }
            }
        }
        // ранил
        if (ind_ship_nearby == true) {
            board[cell_coord.y][cell_coord.x].status = CSt::damaged_ship;
            return 1;
        }
        // убил
        else {
            board[cell_coord.y][cell_coord.x].status = CSt::destroyed_ship;
            mark_destroyed_ship(cell_coord.x, cell_coord.y);
            return 2;
        }
    }
    return -1;
}

void Field::change_cell_radar(string coords, CSt new_status) {
    coordinate cell_coord = get_coords_x_y(coords);
    board[cell_coord.y][cell_coord.x].status = new_status;
}

void Field::show_field() {
    cout << setw(4);
    for (int i = 0; i < letters.size(); i++) {
        cout << ' ' << letters[i];
    }
    cout << endl;

    for (int i = 0; i < 10; i++) {
        cout << ' ' << setw(2) << i + 1 << ' ';
        for (int j = 0; j < 10; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}
