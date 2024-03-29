#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <set>

// Give access to cerr for debug purposes
#include <iostream>

// Explicitly provide access to DLC whenever we include game.h.
#include "dlc.h"
#include "display.h"

class AbstractPlayerEffect;
class Player;
class Floor;
enum class DLC;

class Game {
public:
	static Game *getInstance();
	static void cleanup();

	bool hasDLC(DLC) const;
	void setDLC(DLC, bool = true);

	Player* getPlayer();
	void setPlayer(Player*);
	void addPlayerEffect(AbstractPlayerEffect*);

	int getFloorNumber() const;

	// Get current floor, or floor by ID
	Floor* getFloor() const;
	Floor* getFloor(int) const;

	// The main game loop.
	void displayMenu();
	Player *titleScreen();
	void loop(std::string);
	bool getInput();
	bool attack(int, int);
	bool use(int, int);
	bool move(int, int);
	void nextLevel();
	void renderUi();
	void render();
	bool gameOver();
	bool gameOver(bool);

	// Various helpers!
	void load(std::string);
	void initFloor(int);
	int getPotionStrength(bool = true) const;
	void setPotionModifier(double);

	// Various settings.
	int getMaxChambers() const;
	int getMaxEnemies() const;
	int getMaxPotions() const;
	int getMaxGoldPiles() const;

	// Provide a wrapper for rand() so that all functions share a single
	// prng.
	void srand(int);
	double rand();
	int rand(int);
	int rand(int, int);

private:
	static Game *instance;

	bool bgameOver;
	Player* player;
	int currentFloor;
	Floor *floors[5];
	double potionModifier;

	bool won;
	int score;

	std::set<DLC> dlcs;

	Game();
	~Game();
	// Not implemented as part of the singleton pattern
	Game(const Game&);
	Game &operator=(const Game&);
};

#endif
