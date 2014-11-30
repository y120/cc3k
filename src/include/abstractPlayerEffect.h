#ifndef __ABSTRACT_PLAYER_EFFECT_H__
#define __ABSTRACT_PLAYER_EFFECT_H__

#include "player.h"

class Tile;
class Inventory;
class AbstractEnemy;
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;

class AbstractPlayerEffect : public Player {
public:
	friend class Game;

	AbstractPlayerEffect(Player *base);
	virtual ~AbstractPlayerEffect();

	// By default, all functions will just pipe through. However, only the
	// getStat() functions need to be virtual. (getHP() is not virtual because
	// no Effect can directly modify HP like this; instead, they apply HP
	// changes in the tick() function.)
	virtual int getMaxHP() const;
	virtual int getAtk() const;
	virtual int getDef() const;
	virtual int getDodge() const;
	std::string getRace() const;

	// BEGIN pipe through
	int getHP() const;
	int getR() const;
	int getC() const;
	Tile* getTile() const;
	void move(int, int);
	void moveTo(int, int);
	void moveTo(Tile*);
	void setMaxHP(int);
	void setHP(int);
	void setAtk(int);
	void setDef(int);
	void setDodge(int);
	void addMaxHP(int);
	void addHP(int);
	void addAtk(int);
	void addDef(int);
	void addDodge(int);
	bool isDead() const;
	void die();
	bool wasHit() const;
	int getScore() const;
	int getGold() const;
	void addGold(int);
	void addScore(int);
	Inventory* getInventory() const;
	bool canMove(int, int) const;
	bool canMoveTo(int, int) const;
	bool canMoveTo(Tile*) const;
	void getHitBy(AbstractEnemy*);
	void getHitBy(Human*);
	void getHitBy(Dwarf*);
	void getHitBy(Elf*);
	void getHitBy(Orc*);
	void getHitBy(Merchant*);
	void getHitBy(Dragon*);
	void strike(AbstractEnemy*);
	// END pipe through

	// Effects should be removed when expired. At the end of each tick phase,
	// this is evaluated for truthiness. If false, it is removed as a decorator.
	virtual bool isExpired() const = 0;

	virtual Player* tickEffects();

	// Returns a clone of the current effect
	virtual AbstractPlayerEffect *clone() = 0;

protected:
	Player *base;
};

#endif
