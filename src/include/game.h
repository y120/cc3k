#ifndef __GAME_H__
#define __GAME_H__

#include <set>

// Explicitly provide access to DLC whenever we include game.h.
#include "dlc.h"

class AbstractPlayerEffect;
class Player;
class Floor;
enum class DLC;

class Game {
public:
	// Note: we use a modified form of the regular Singleton pattern, where we
	// use a static instance within the getInstance function. This permits us
	// to not worry about deleting the instance (yay, RAII / DIRR / RRID!)
	static Game *getInstance();

	bool hasDLC(DLC) const;
	void setDLC(DLC, bool = true);

	Player* getPlayer();
	void addPlayerEffect(AbstractPlayerEffect*);

	int getFloorNumber() const;

	// Get current floor, or floor by ID
	Floor* getFloor() const;
	Floor* getFloor(int) const;

	// The main game loop.
	void loop();

	// Various helpers!
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
	Player* player;
	int currentFloor;
	Floor *floors[5];
	double potionModifier;

	std::set<DLC> dlcs;

	Game();
	// Not implemented as part of the singleton pattern
	Game(const Game&);
	Game &operator=(const Game&);
};

#endif
