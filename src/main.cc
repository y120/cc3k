//*
#include "game.h"
#include "floor.h"
#include "basePlayers.h"

#include <iostream>
#include <sstream>

using namespace std;

void displayMenu();
Player* selectPlayer();

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

	// Display a menu to select DLCs and player race.
	Player *p = selectPlayer();

	// If no floor is specified, then behaviour depends on whether the Generated
	// DLC is loaded. If so, generate; otherwise, load the default
	if (floorFile == "") {
		if (Game::getInstance()->hasDLC(DLC::Generated)) {
			for (int i = 1; i <= 5; i++) {
				Game::getInstance()->getFloor(i)->generate();
			}
		} else {
			Game::getInstance()->load("cc3kempty.txt");
			for (int i = 1; i <= 5; i++) {
				Game::getInstance()->getFloor(i)->fill();
			}
		}
	} else {
		Game::getInstance()->load(floorFile);
	}
	Game::getInstance()->setPlayer(p);
	Game::getInstance()->initFloor(1);
	Game::getInstance()->render();
	Game::cleanup();
	return 0;
}

void displayMenu() {
	string desc[] = {
		"Generated DLC (randomly generated dungeons)",
		"Inventory DLC (store and use items later"
	};
	cout << "ChamberCrawler3000 Main Menu\n\n";

	// DLC select
	cout << "Enter a number to enable or disable that DLC, or a race to start.\n\n";
	for (int i = 0; i < static_cast<int>(DLC::LAST); i++) {
		cout << "[";
		cout << (Game::getInstance()->hasDLC(static_cast<DLC>(i)) ? 'X' : ' ');
		cout << "] " << i << ": " << desc[i] << "\n";
	}

	// Race select
	cout << "\n\nRaces:\n";
	cout << "s: Shade. No special bonus.\n";
	cout << "d: Drow. Potions are more impactful.\n";
	cout << "v: Vampire. Steal HP on hit.\n";
	cout << "g: Goblin. Get an extra 5 gold every time you kill.\n";
	cout << "t: Troll. Regenerate health every turn.\n";
	cout << "\n";
}

Player* selectPlayer() {
	while (true) {
		displayMenu();
		char ch;
		cout << "\nYour input: ";
		cin >> ch;
		switch (ch) {
			case 's': return new Shade();
			case 'd': return new Drow();
			case 'v': return new Vampire();
			case 'g': return new Goblin();
			case 't': return new Troll();
		}
		int dlcNum = ch - '0';
		if (dlcNum >= 0 && dlcNum < static_cast<int>(DLC::LAST)) {
			DLC dlc = static_cast<DLC>(dlcNum);
			Game::getInstance()->setDLC(dlc, !Game::getInstance()->hasDLC(dlc));
		}
	};
}
