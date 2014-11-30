#include "game.h"

int main() {
	Game::getInstance()->load("cc3kfloor.txt");
	Game::getInstance()->render();
}
