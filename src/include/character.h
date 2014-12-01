#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "renderable.h"
#include <string>

struct CharacterImpl;
class Tile;

class Character : public Renderable {
public:
	Character(int, int, int, int);
	virtual ~Character();

	// Getters for the stats. May be overridden by potion effects, except HP.
	// (HP is always the same, and is not directly modified by virtue of an
	// active effect, though effects can modify HP).
	virtual int getMaxHP() const;
	virtual int getHP() const;
	virtual int getAtk() const;
	virtual int getDef() const;
	virtual int getDodge() const;

	virtual int getR() const;
	virtual int getC() const;
	virtual Tile *getTile() const;
	virtual int getFloor() const;
	virtual void setFloor(int);
	// move functions. The first is relative, the second is absolute.
	// note no direct setter!
	virtual void move(int, int);
	virtual void moveTo(int, int);
	virtual void moveTo(Tile*);

	void setMaxHP(int);
	void setHP(int);
	void setAtk(int);
	void setDef(int);
	void setDodge(int);

	virtual bool canMove(int, int) const = 0;
	virtual bool canMoveTo(int, int) const = 0;
	virtual bool canMoveTo(Tile*) const = 0;

	// For convenience. We may wish sometimes to add stats instead of just
	// overwriting them.
	virtual void addMaxHP(int);
	virtual void addHP(int);
	virtual void addAtk(int);
	virtual void addDef(int);
	virtual void addDodge(int);

	virtual bool isDead() const;
	virtual void die();
	int calculateDamage(Character*) const;
	void getHitBy(Character*);
	virtual bool wasHit() const;

	/**
	 *	Applies a tick of each effect, checks for effect expiry, and returns the
	 *	new, potentially undecorated Character.
	 *
	 *	Removed (enemies have no effects).
	 */
	//virtual Character* tickEffects() = 0;

	// do not implement render() here!

protected:
	// Stats make no sense for Effects, so leave that as a protected constructor.
	Character();
	bool hit;

private:
	// The stats of the character.
	CharacterImpl *pImpl;

	// A pointer to the current tile, for convenience.
};

#endif
