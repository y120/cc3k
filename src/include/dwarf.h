#ifndef __DWARF_H__
#define __DWARF_H__

#include <string>
#include "abstractEnemy.h"

class Vampire;

class Dwarf : public AbstractEnemy {
public:
	Dwarf();

	void getHitBy(Player*);
	void strike(Player*);
};

#endif
