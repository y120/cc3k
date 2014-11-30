#ifndef __TROLL_H__
#define __TROLL_H__

#include "player.h"

class AbstractEnemy;

class Troll : public Player {
public:
	Troll();

	std::string getRace() const;

	void getHitBy(AbstractEnemy*);
	void strike(AbstractEnemy*);
	Player* tickEffects();
};

#endif
