#include "game.h"
#include "display.h"
#include "abstractPlayerEffect.h"
#include "player.h"
#include "floor.h"
#include "dlc.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

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

Game::Game() : player(NULL), currentFloor(0), potionModifier(1) {
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

void Game::loop() {
	// TODO
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
	Display::getInstance()->draw("Action: "/* + message*/, 29, 0);
	/**** TODO: Action message *****/
}

void Game::render() {
	//std::cerr << "Game: render " << std::endl;
	this->getFloor()->render();
	// draw border
	Display::getInstance()->draw("|-----------------------------------------------------------------------------|",
		 0, 0);
	Display::getInstance()->draw("|-----------------------------------------------------------------------------|",
		 24, 0);
	for (int l0 = 0; l0 < 25; l0++) {
		// draw border edges
		Display::getInstance()->draw("|", l0, 0);
		Display::getInstance()->draw("|", l0, 78);
	}
	renderUi();
	Display::getInstance()->render();
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
	return this->rand(max + 1) + min;
}
