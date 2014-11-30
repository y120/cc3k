#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__

#include "player.h"

class AbstractEnemy;

class Vampire : public Player {
public:
	Vampire();

	std::string getRace() const;

	void getHitBy(AbstractEnemy*);
	void strike(AbstractEnemy*);
};

#endif
