#include "game.h"

int main() {
	Game::getInstance()->load("cc3kfloor.txt");
	Game::getInstance()->render();
/*#include "floor.h"
#include <ctime>
#include <cstdio>

int main() {
	int seed = 1417316571;
	seed = time(NULL);
	Game::getInstance()->srand(seed);
	Floor f;
	f.generate();
	printf("Seed: %d\n", seed);*/
}
