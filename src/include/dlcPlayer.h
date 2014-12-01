#ifndef __DLCENEMY_H__
#define __DLCENEMY_H__

#include "player.h"

class AbstractEnemy;

class SuperVillan : public Player {
public:
	SuperVillan();

	std::string getRace() const;

	void getHitBy(AbstractEnemy*);
	void strike(AbstractEnemy*);
};

class VampTrol : public Player {
public:
	VampTrol();

	std::string getRace() const;

	void getHitBy(AbstractEnemy*);
	void strike(AbstractEnemy*);
	Player *tickEffects();
};

#endif
