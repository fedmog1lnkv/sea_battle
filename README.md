# Sea Battle
Welcome to the Sea Battle game! This is a classic battleship game played on a 10x10 grid. Your goal is to sink all of your opponent's ships before they sink yours.

## How to Play
- Clone the repository using git clone https://github.com/fedmog1lnkv/sea_battle.git.
- Navigate to the project directory using cd sea_battle.
- Run the game using gcc.
- Follow the instructions printed in the console to play the game.
- To place your ships, enter the start and end coordinates of each ship. For example, to place a ship from (0, 0) to (0, 3), enter "0 0 0 3" when prompted.
- To make a guess, enter a coordinate in the format "row column". For example, to guess A4, enter "A 4" when prompted.
## Rules
- Each player has 5 ships: one battleship (4 cells), one cruiser (3 cells), one destroyer (2 cells), and two submarines (1 cell each).
- Players take turns guessing the location of their opponent's ships by entering coordinates.
- If you hit a ship, you will see an 'X' on the board. If you miss, you will see an 'O'.
- The game ends when one player sinks all of their opponent's ships.
