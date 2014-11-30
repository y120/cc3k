#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "abstractEnemy.h"

class Tile;
class DragonHoard;

class Dragon : public AbstractEnemy {
public:
	Dragon();
	Dragon(Tile*);

	void setHoard(DragonHoard *);

	void getHitBy(Player*);
	void strike(Player*);

	// Note: we could perform some logic on the GoldPile, but we don't need to,
	// since it's implemented in DragonHoard!
	void doTurn();

protected:
	bool canHitPlayer() const;

private:
	/*
	 *	More accurately, this could be a DragonHoard. However, since
	 *	AbstractItems do not store their position, we instead maintain a link to
	 *	the Tile that the dragon's hoard rests on.
	 */
	Tile *hoard;
};

#endif
