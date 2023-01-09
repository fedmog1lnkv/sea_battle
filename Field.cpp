#include <algorithm>

#include "Field.h"

Field::Field() { fillMap(); }

#define FOR_MAP                  \
    for (int y = 0; y < 10; y++) \
        for (int x = 0; x < 10; x++)

void Field::fillMap() {
	FOR_MAP
		board[y][x] = Cell();
}

void Field::deleteShip(int type_ship) {
	for (int ship = 0; ship < 10; ship++) {
		if (type_ships[ship] == type_ship) {
			type_ships[ship] = 0;
			return;
		}
	}
}

coordinate Field::getCoordsXY(string coords) {
	transform(coords.begin(), coords.end(), coords.begin(), ::toupper);
	coordinate point;

	point.x = static_cast<int>(letters.find(coords[0]));
	// проверка на длину
	point.y = coords.length() == 3 ? 9 : coords[1] - '0' - 1;
	return point;
}

string Field::getCoordsString(coordinate cell) {
	string hint_move;
	hint_move.push_back(letters[cell.x]);
	hint_move += to_string(cell.y + 1);
	return hint_move;
}

bool Field::checkArea(int x, int y) {
	return (x < 0 || x > 9 || y < 0 || y > 9);
}

void Field::placementShips() {
	cout << "Расставьте корабли" << endl;

	string coords, bow, stern;
	for (int i = 9; i > -1; i--) {
		system("cls");

		showField();

		cout << "Куда поставить " << name_ships[type_ships[i] - 1] << "?"
			<< endl;
		while (true) {
			cin >> coords;

			// верхний регистр
			transform(coords.begin(), coords.end(), coords.begin(), ::toupper);

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

			coordinate first_coord = getCoordsXY(bow);
			coordinate second_coord = getCoordsXY(stern);

			// сортировка координат, т.к. всегда две координаты должны быть
			// одинаковые
			if (first_coord.x == second_coord.x) {
				if (first_coord.y > second_coord.y) {
					swap(first_coord, second_coord);
				}
			}
			else {
				if (first_coord.y == second_coord.y) {
					if (first_coord.x > second_coord.x) {
						swap(first_coord.x, second_coord.x);
					}
				}
			}

			if (checkShipPlacement(first_coord, second_coord, type_ships[i],
				true)) {
				int rotate;
				if (first_coord.x == second_coord.x) {
					rotate = 0;
				}
				else {
					rotate = 1;
				}
				ships[i] = Ship(first_coord, rotate, type_ships[i]);
				putShip(first_coord, second_coord);
				break;
			}
		}
	}
}

bool Field::checkShipPlacement(coordinate first, coordinate second,
	int type_ship, bool is_player) {
	if (checkArea(first.x, first.y) || checkArea(second.x, second.y)) {
		if (is_player == true) {
			cout << "Вернитесь в зону боевых действий" << endl;
			Sleep(1000);
		}
		return false;
	}

	int lenght_ship =
		static_cast<int>(sqrt(pow(second.x + 1 - first.x + 1, 2) +
			pow(second.y + 1 - first.y + 1, 2)) -
			1);

	if (lenght_ship != type_ship) {
		if (is_player == true) {
			cout << "Неверная длина корабля" << endl;
			Sleep(1000);
		}
		return false;
	}

	if (first.x != second.x && first.y != second.y) {
		if (is_player == true) {
			cout << "Неверные координаты расстановки" << endl;
			Sleep(1000);
		}
		return false;
	}

	// пробежка по координатам вокруг
	for (int x = first.x - 1; x <= second.x + 1; x++) {
		for (int y = first.y - 1; y <= second.y + 1; y++) {
			// проверка выхода из поля
			if (checkArea(x, y)) {
				continue;
			}
			if (board[y][x].isBusy()) {
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

void Field::autoPlacementShips() {
	for (int i = 9; i > -1; i--) {
		coordinate first_coord, second_coord;

		while (true) {
			// 0 - вертикаль
			// 1 - горизонталь
			int rand_rotate = rand() % 2;

			int rand_start_coords_x = (rand() % 10);
			int rand_start_coords_y = (rand() % 10);

			first_coord = { rand_start_coords_x, rand_start_coords_y };
			if (rand_rotate == 0) {
				second_coord = { rand_start_coords_x,
								rand_start_coords_y + type_ships[i] - 1 };
			}
			else {
				second_coord = { rand_start_coords_x + type_ships[i] - 1,
								rand_start_coords_y };
			}

			if (checkShipPlacement(first_coord, second_coord, type_ships[i],
				false)) {
				ships[i] = Ship(first_coord, rand_rotate, type_ships[i]);
				putShip(first_coord, second_coord);

				break;
			}
		}
	}
}

void Field::putShip(coordinate first, coordinate second) {
	for (int x = first.x; x <= second.x; x++) {
		for (int y = first.y; y <= second.y; y++) {
			board[y][x].status = CSt_t::ship_cell;
			board[y][x].weight = 7;
		}
	}
}

void Field::markDestroyedShipRadar(coordinate coord) {
	board[coord.y][coord.x].status = CSt_t::destroyed_ship;
	for (int x = coord.x - 1; x <= coord.x + 1; x++) {
		for (int y = coord.y - 1; y <= coord.y + 1; y++) {
			if (checkArea(x, y) || (x == coord.x && y == coord.y)) {
				continue;
			}
			if (board[y][x].status == CSt_t::empty_cell) {
				board[y][x].status = CSt_t::miss_cell;
			}
			if (board[y][x].status == CSt_t::damaged_ship) {
				board[y][x].status = CSt_t::destroyed_ship;
				markDestroyedShipRadar({ x, y });
			}
		}
	}
}

StatusAttack Field::makeAttack(coordinate coords) {
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
		int hp = injureShip(coords);
		if (hp > 0) {
			board[coords.y][coords.x].status = CSt_t::damaged_ship;
			return SA_t::damage;
		}
		// убил
		else {
			markDestroyedShipRadar(coords);
			return SA_t::destroy;
		}
	}
	return SA_t::error;
}

int Field::injureShip(coordinate coord_attack_ship) {
	Ship& attacked_ship = findShip(coord_attack_ship);
	attacked_ship.hp--;
	return attacked_ship.hp;
}

Ship& Field::findShip(coordinate coord_cell) {
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

void Field::changeCellRadar(coordinate coords, CSt_t new_status) {
	board[coords.y][coords.x].status = new_status;
	recalculateWeightBoard();
}

void Field::recalculateWeightBoard() {
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
				if (checkShipPlacement({x, y}, {x + ships[ship].type_ship, y},
										 ships[ship].type_ship, false) ||
					checkShipPlacement({x, y}, {x, y + ships[ship].type_ship},
										 ships[ship].type_ship, false)) {
					board[y][x].weight++;
				}
			}
		}
	}
}

coordinate Field::getCoordMaxWeightCell() {
	map<int, coordinate> weights_cells;
	int max_weight = 0;

	FOR_MAP
		if (board[y][x].weight > max_weight) {
			max_weight = board[y][x].weight;
			weights_cells[board[y][x].weight] = { x, y };
		}

	if (max_weight == 1) {
		coordinate temp_coord = { rand() % 10, rand() % 10 };
		while (board[temp_coord.y][temp_coord.x].isBusy()) {
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

void Field::showField() {
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

void Field::dumpFieldLog(ofstream& log_file)
{
	for (int ship = 0; ship < 10; ship++) {
		log_file << name_ships[ships[ship].type_ship - 1] << ": ";
		log_file << getCoordsString(ships[ship].start_coords);
		if (ships[ship].type_ship == 1) {
			log_file << endl;
			continue;
		}
		if (ships[ship].rotate == 0) {
			log_file << ":" << getCoordsString({ ships[ship].start_coords.x,  ships[ship].start_coords.y + ships[ship].type_ship }) << endl;
		}
		else {
			log_file << ":" << getCoordsString({ ships[ship].start_coords.x + ships[ship].type_ship,  ships[ship].start_coords.y }) << endl;
		}

	}
}