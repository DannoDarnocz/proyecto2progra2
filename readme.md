# BLOCK WORLD

## How to compile
The project was made in CLion; it should compile right away and should work on all operative systems since the libraries used don’t have any OS specific quirks.

## How to play
The whole game is played inside the console, so it is recommended that you adjust the console height to your liking, since the default height is too low and will obstruct most of the interface.

## Project structure
Main.cpp is responsible for managing the game logic with different functions for portions of code that are reused multiple times or complex situations, like the combat logic, on a separate mainspace for legibility.

## Quick simulation description
The game works based on interacting with a world made of cells arranged in a matrix where there are monsters that engage in combat, hidden bombs, medkits and powerups. They might be on the surface or you might need to dig down to find them. Defeat monsters, get strong and defeat the bosses on all dimensions to win.
