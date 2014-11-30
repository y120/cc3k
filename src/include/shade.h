#ifndef __SHADE_H__
#define __SHADE_H__

#include "player.h"

class AbstractEnemy;

class Shade : public Player {
public:
	Shade();

	std::string getRace() const;

	void getHitBy(AbstractEnemy*);
	void strike(AbstractEnemy*);
};

#endif
