#ifndef __ELF_H__
#define __ELF_H__

#include "abstractEnemy.h"

class Elf : public AbstractEnemy {
public:
	Elf();

	void getHitBy(Player*);
	void strike(Player*);
};

#endif
