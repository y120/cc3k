#include "game.h"
#include "basePlayers.h"

using namespace std;

int main() {
	cerr << "1\n";
	Game::getInstance()->load("cc3kfloor.txt");
	cerr << "2\n";
	Game::getInstance()->setPlayer(new Shade());
	cerr << "3\n";
	Game::getInstance()->initFloor(1);
	cerr << "4\n";
	Game::getInstance()->render();
	cerr << "5\n";
	return 0;
}
