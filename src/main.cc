
#include "game.h"
#include "basePlayers.h"

using namespace std;

int main() {
	Game::getInstance()->setPlayer(new Shade());
	Game::getInstance()->load("cc3kfloor.txt");
	Game::getInstance()->initFloor(1);
	Game::getInstance()->render();
	Game::cleanup();
	return 0;
}

/*

#include "game.h"
#include "floor.h"
#include <ctime>
#include <cstdio>

int main() {
	int seed = 1417316571;
	seed = time(NULL);
	Game::getInstance()->srand(seed);
	Floor f;
	f.generate();
	printf("Seed: %d\n", seed);
}
//*/
