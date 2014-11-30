#include "game.h"
#include "display.h"
#include "abstractPlayerEffect.h"
#include "player.h"
#include "abstractEnemy.h"
#include "floor.h"
#include "dlc.h"
#include "basePlayers.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef POTION_STRENGTH
	#define POTION_STRENGTH 5
#endif
#ifndef MAX_CHAMBERS
	#define MAX_CHAMBERS 5
#endif
#ifndef MAX_ENEMIES
	#define MAX_ENEMIES 10
#endif
#ifndef MAX_POTIONS
	#define MAX_POTIONS 10
#endif
#ifndef MAX_GOLD_PILES
	#define MAX_GOLD_PILES 10
#endif

Game *Game::instance = NULL;

Game::Game()
	: bgameOver(false), player(NULL), currentFloor(0), potionModifier(1)
{
	// NOTE: We cannot initialise Floors here because that introduces infinite
	// recursion... oops!
	// currentFloor 0 is invalid. We must call initFloor(1) once
	// floors are loaded 
}
Game::~Game() {
	delete this->player;
	for (int i = 0; i < 5; i++) {
		delete this->floors[i];
	}
}

Game* Game::getInstance() {
	if (!Game::instance) {
		Game::instance = new Game();
		for (int i = 0; i < 5; i++) {
			Game::instance->floors[i] = new Floor(i + 1);
		}
		atexit(Game::cleanup);
	}
	return Game::instance;
}

void Game::cleanup() {
	delete Game::instance;
	Game::instance = NULL;
}

bool Game::hasDLC(DLC dlc) const {
	return this->dlcs.count(dlc);
}

void Game::setDLC(DLC dlc, bool b) {
	if (b) {
		this->dlcs.insert(dlc);
	} else {
		this->dlcs.erase(dlc);
	}
}

Player* Game::getPlayer() {
	return this->player;
}

void Game::setPlayer(Player *player) {
	//std::cerr << "Game - setting player:" << player << std::endl;
	this->player = player;
}

void Game::addPlayerEffect(AbstractPlayerEffect *effect) {
	AbstractPlayerEffect *newEffect = effect->clone();
	newEffect->base = this->player;
	this->player = newEffect;
}

int Game::getFloorNumber() const {
	return this->currentFloor;
}

Floor *Game::getFloor() const {
	return this->getFloor(this->getFloorNumber());
}

Floor *Game::getFloor(int floor) const {
	return this->floors[floor - 1];
}

namespace {
	void displayMenu() {
		using std::cout;
		std::string desc[] = {
			"Generated DLC (randomly generated dungeons)",
			"Inventory DLC (store and use items later)"
		};
		Display::getInstance()->draw("ChamberCrawler3000 Main Menu", 0, 0);

		// DLC select
		Display::getInstance()->draw("Enter a number to enable or disable that DLC, or a race to start.", 2, 0);
		std::ostringstream oss;
		for (int i = 0; i < static_cast<int>(DLC::LAST); i++) {
			oss.str("");
			oss << "[";
			oss << (Game::getInstance()->hasDLC(static_cast<DLC>(i)) ? 'X' : ' ');
			oss << "] " << i << ": " << desc[i] << "\n";
			Display::getInstance()->draw(oss.str(), 4 + i, 0);
		}

		// Race select
		Display::getInstance()->draw("Races:", 4 + int(DLC::LAST), 0);
		Display::getInstance()->draw("s: Shade. No special bonus.", 5 + int(DLC::LAST), 0);
		Display::getInstance()->draw("d: Drow. Potions are more impactful.", 6 + int(DLC::LAST), 0);
		Display::getInstance()->draw("v: Vampire. Steal HP on hit.", 7 + int(DLC::LAST), 0);
		Display::getInstance()->draw("g: Goblin. Get an extra 5 gold every time you kill.", 8 + int(DLC::LAST), 0);
		Display::getInstance()->draw("t: Troll. Regenerate health every turn.", 9 + int(DLC::LAST), 0);
		Display::getInstance()->draw("Press q to quit.", 10 + int(DLC::LAST), 0);
		
		Display::getInstance()->render();
	}
}

Player* Game::titleScreen() {
	using std::cout;
	using std::cin;
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
			case 'q': return NULL;
		}
		int dlcNum = ch - '0';
		if (dlcNum >= 0 && dlcNum < static_cast<int>(DLC::LAST)) {
			DLC dlc = static_cast<DLC>(dlcNum);
			this->setDLC(dlc, !this->hasDLC(dlc));
		}
	};
}


void Game::loop(std::string floorFile) {
	while ((player = titleScreen()) != NULL) {
		gameOver(false);
		Display::getInstance()->addMessage("Player character has spawned.");

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
		Game::getInstance()->initFloor(1);

		while (!gameOver()) {
			render();
			getInput();
			std::vector<AbstractEnemy*> &flEnemies = getFloor()->getEnemies();
			std::cerr << &flEnemies << std::endl;
			for (int l0 = 0; l0 < (int)flEnemies.size(); l0++) {
				if ((flEnemies[l0] != NULL) && (!flEnemies[l0]->isDead())) {
					std::cerr << "gameloop - enemy" << l0 << '-' << flEnemies[l0] << " doing turn\n";
					std::cerr << flEnemies[l0]->getR() << ' ' << flEnemies[l0]->getC() << '\n';
					flEnemies[l0]->doTurn();
					std::cerr << "Gameloop - enemy done turn " << std::endl;
				}
			}
		}
	}
}

void Game::getInput() {
	std::string input;
	std::cin >> input;
	transform(input.begin(), input.end(), input.begin(), ::tolower);

	if (input[0] == 'u') {
		// use potion
	} else if (input[0] == 'a') {
		// ATTACK!!
	} else if (input[0] == 'r') {
		// restart
	}
}

// called once player reaches last level
void Game::nextLevel() {
	if (currentFloor == 5) {
		// YOU WIN!
		gameOver(true);
	} else {
		initFloor(currentFloor + 1);
	}
}

void Game::renderUi() {
	std::ostringstream oss;
	oss << "Race: " << player->getRace()
		<< " Gold: " << player->getGold();
	Display::getInstance()->draw(oss.str(), 25, 0);
	oss.str("");
	oss << "Floor " << currentFloor;
	Display::getInstance()->draw(oss.str(), 25, 77 - oss.str().length());
	oss.str("");
	oss << "HP: " << player->getHP();
	Display::getInstance()->draw(oss.str(), 26, 0);
	oss.str("");
	oss << "Atk: " << player->getAtk();
	Display::getInstance()->draw(oss.str(), 27, 0);
	oss.str("");
	oss << "Def: " << player->getDef();
	Display::getInstance()->draw(oss.str(), 28, 0);
	Display::getInstance()->drawMessage();
}

void Game::render() {
	//std::cerr << "Game: render " << std::endl;
	this->getFloor()->render();
	// draw border
	std::string border = "|-----------------------------------------------------------------------------|";
	Display::getInstance()->draw(border, 0, 0);
	Display::getInstance()->draw(border, 24, 0);
	for (int l0 = 0; l0 < 25; l0++) {
		// draw border edges
		Display::getInstance()->draw("|", l0, 0);
		Display::getInstance()->draw("|", l0, 78);
	}
	renderUi();
	Display::getInstance()->render();
}

bool Game::gameOver() {
	return bgameOver;
}

bool Game::gameOver(bool set) {
	bgameOver = set;
	return bgameOver;
}

void Game::initFloor(int flr) {
	currentFloor = flr;
	player->setFloor(flr);
	player->move(floors[currentFloor]->getPlayerR(), floors[currentFloor]->getPlayerC());
}

void Game::load(std::string filename) {
	std::ifstream fin(filename.c_str());
	for (int l0 = 0; l0 < 5; l0++) {
		//std::cerr << "Game:load " << l0 << std::endl;
		delete floors[l0];
		floors[l0] = new Floor(l0 + 1, fin);
	}
}

int Game::getPotionStrength(bool withModifiers) const {
	return std::ceil(POTION_STRENGTH * (withModifiers ? this->potionModifier : 1));
}

void Game::setPotionModifier(double newModifier) {
	this->potionModifier = newModifier;
}

int Game::getMaxChambers() const {
	return MAX_CHAMBERS;
}

int Game::getMaxEnemies() const {
	return MAX_ENEMIES;
}

int Game::getMaxPotions() const {
	return MAX_POTIONS;
}

int Game::getMaxGoldPiles() const {
	return MAX_GOLD_PILES;
}

void Game::srand(int seed) {
	std::srand(seed);
}

double Game::rand() {
	return 1.0 * std::rand() / RAND_MAX;
}

// [0, max)
int Game::rand(int max) {
	return std::rand() % max;
}

int Game::rand(int min, int max) {
	return this->rand(max - min + 1) + min;
}
