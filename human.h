#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "abstractEnemy.h"

class Human : public AbstractEnemy {
public:
	Human();

	void getHitBy(Player*);
	void strike(Player*);

	void die();

	std::string render();
};

#endif
