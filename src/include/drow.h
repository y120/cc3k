#ifndef __DROW_H__
#define __DROW_H__

#include "player.h"

class AbstractEnemy;

class Drow : public Player {
public:
	Drow();

	void getHitBy(AbstractEnemy*);
	void strike(AbstractEnemy*);
};

#endif
