#ifndef __HALFLING_H__
#define __HALFLING_H__

#include "abstractEnemy.h"

class Halfling : public AbstractEnemy {
public:
	Halfling();

	void getHitBy(Player*);
	void strike(Player*);

	std::string render();
};

#endif
