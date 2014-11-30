/*
#include "game.h"
#include "basePlayers.h"

using namespace std;

int main() {
	//cerr << "1\n";
	Game::getInstance()->load("cc3kfloor.txt");
	//cerr << "2\n";
	Game::getInstance()->setPlayer(new Shade());
	//cerr << "3\n";
	Game::getInstance()->initFloor(1);
	//cerr << "4\n";
	Game::getInstance()->render();
	//cerr << "5\n";
	Game::cleanup();
	return 0;
}

/*
*/
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
