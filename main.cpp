#include <fcntl.h>
#include <io.h>

#include <iostream>

#include "Game.h"

using namespace std;

int main() {
  setlocale(LC_ALL, "");

  srand(static_cast <int> (time(0)));

  Game game;
  game.start_preparation();
  /*Field f;
  f.placement_ships();
  f.show_field();*/
  // рандомное предложение хода

  // игра между двумя ботами
  // 1 игра = 3 секунды
  // для 100 игр = 335,1 секунды

  return 0;
}
