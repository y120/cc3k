#ifndef __ABSTRACT_ENEMY_H__
#define __ABSTRACT_ENEMY_H__

#include "character.h"

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;
class Tile;

class AbstractEnemy : public Character {
public:
	AbstractEnemy(int, int, int);

	/*
	 *	An explanation is order. We apply the Visitor pattern in both
	 *	directions. Also, to avoid having to implement useless stubs, well...
	 *	see implementation file.
	 */
	// Generic.
	virtual void getHitBy(Player*) = 0;
	// Player races.
	virtual void getHitBy(Shade*);
	virtual void getHitBy(Drow*);
	virtual void getHitBy(Vampire*);
	virtual void getHitBy(Troll*);
	virtual void getHitBy(Goblin*);
	// [DLC]

	// Dispatch a hit to a player.
	virtual void strike(Player*) = 0;

	bool canMove(int, int) const;
	bool canMoveTo(int, int) const;
	bool canMoveTo(Tile*) const;

	virtual void die();

	virtual Character *tickEffects();

	// By default, the Enemy's turn follows this logic: If canHitPlayer(), then
	// attack Player. Otherwise, move a random space.
	virtual void doTurn();

protected:
	// Default range is within 1!
	virtual bool canHitPlayer() const;

};

#endif
