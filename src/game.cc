#include "game.h"
#include "abstractPlayerEffect.h"
#include "player.h"
#include "floor.h"
#include "dlc.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

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

Game::Game() : player(NULL), currentFloor(1), potionModifier(1) {}

Game* Game::getInstance() {
	static Game instance;
	return &instance;
}

bool Game::hasDLC(DLC dlc) const {
	return this->dlcs.count(dlc);
}

Player* Game::getPlayer() {
	return this->player;
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
