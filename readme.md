# BLOCK WORLD
## Quick simulation description
The game works based on interacting with a world made of cells arranged in a matrix where there are monsters that engage in combat, hidden bombs, medkits and powerups. They might be on the surface or you might need to dig down to find them. Defeat monsters, get strong and defeat the bosses on all dimensions to win.

## How to compile
The project was made in CLion and CMake.
1. Open the project folder from CLion
2. Let it load the CMake configuration
3. Run the project using the Run option in the top menu, or by pressing Shift+F10

## How to run
After compiling, you can run the executable file generated in the cmake-build-debug folder, which is located in the project folder. The executable file is called Proyecto_II.exe.

You can also run it by pressing the Run button on the top right, or by pressing SHIFT+F10, which will run the executable file for you.

Please note that the project expects the following file on the project folder to load all the data for the world:
- `map_data.txt`

And during runtime, the program generates two files on the project folder:
- `log.txt` for all the actions and events that happen during the game
- `final_report.txt` for the summary of the adventure when the game ends, either by winning, losing or exiting the game.

## How to play
The whole game is played inside the console, so it is recommended that you adjust the console height to your liking, since the default height is too low and will obstruct most of the interface.

## Project structure
Main.cpp is responsible for managing the game logic with different functions for portions of code that are reused multiple times or complex situations, like the combat logic, on a separate mainspace for legibility.

