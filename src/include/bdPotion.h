#ifndef __BD_POTION_H__
#define __BD_POTION_H__

#include "abstractPotion.h"

class AbstractEffect;

class BDPotion : public AbstractPotion {
public:
	BDPotion();
protected:
	std::string getNameInternal() const;
};

#endif
