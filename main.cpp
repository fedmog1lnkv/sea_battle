#include <fcntl.h>
#include <io.h>

#include <iostream>

#include "Game.h"

using namespace std;

int main() {
  setlocale(LC_ALL, "");

  srand(static_cast <int> (time(0)));

  /* string s = "B1:D1";
   cout << s.find("10");*/
  Game game;

   game.start_preparation();

  /*Field f;
  f.auto_placement_ships();
  f.show_field();*/

  return 0;
}
