#include "game.h"
#include "floor.h"

#include <iostream>
#include <sstream>

using namespace std;

/*
 *	Permissible command line arguments:
 *	./cc3k <floorFile> <seed>
 */
int main(int argc, char *argv[]) {
	string floorFile;
	int seed = time(NULL);
	if (argc >= 2) {
		// Parameter one: the floor file.
		floorFile = argv[1];
	}
	if (argc >= 3) {
		// Parameter two: the seed.
		istringstream iss(argv[2]);
		iss >> seed;
	}
	Game::getInstance()->srand(seed);
	Game::getInstance()->loop(floorFile);
	return 0;
}
