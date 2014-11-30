#ifndef __ORC_H__
#define __ORC_H__

#include "abstractEnemy.h"

class Orc : public AbstractEnemy {
public:
	Orc();

	void getHitBy(Player*);
	void strike(Player*);
};

#endif
