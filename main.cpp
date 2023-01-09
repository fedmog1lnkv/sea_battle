#include <fcntl.h>
#include <io.h>

#include <iostream>

#include "Game.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    srand(static_cast<int>(time(0)));

    Game game;
    game.startPreparation();

    return 0;
}
