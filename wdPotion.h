#ifndef __WD_POTION_H__
#define __WD_POTION_H__

#include "abstractPotion.h"

class AbstractPlayerEffect;

class WDPotion : public AbstractPotion {
public:
	WDPotion();
protected:
	std::string getNameInternal() const;
};

#endif
