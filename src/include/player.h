#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include "character.h"

class AbstractEnemy;

class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;

class Inventory;

class Player : public Character {
public:
	~Player();

	// Score is the same as total gold earned (including spent gold).
	virtual int getScore() const;
	virtual int getGold() const;

	// If positive, addGold() should also addScore().
	virtual void addGold(int);
	virtual void addScore(int);

	virtual Inventory* getInventory() const;

	virtual bool canMove(int, int) const;
	virtual bool canMoveTo(int, int) const;
	virtual bool canMoveTo(Tile*) const;

	// See explanation in abstractEnemy.h
	// Generic.
	virtual void getHitBy(AbstractEnemy*) = 0;
	// Player races.
	virtual void getHitBy(Human*);
	virtual void getHitBy(Dwarf*);
	virtual void getHitBy(Elf*);
	virtual void getHitBy(Orc*);
	virtual void getHitBy(Merchant*);
	virtual void getHitBy(Dragon*);
	// [DLC]

	// Dispatch a hit to an enemy.
	virtual void strike(AbstractEnemy*) = 0;

	virtual void die();
	virtual Player* tickEffects();

protected:
	Player(); // We provide an empty constructor for the Decorator.
	Player(int, int, int);

	int score;
	int gold;

	Inventory *inventory;
};

#endif
