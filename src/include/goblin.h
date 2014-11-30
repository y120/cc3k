#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "player.h"

class AbstractEnemy;

class Goblin : public Player {
public:
	Goblin();

	std::string getRace() const;

	void getHitBy(AbstractEnemy*);
	void getHitBy(Orc*);
	void strike(AbstractEnemy*);
};

#endif
