#ifndef __WA_POTION_H__
#define __WA_POTION_H__

#include "abstractPotion.h"

class AbstractPlayerEffect;

class WAPotion : public AbstractPotion {
public:
	WAPotion();
protected:
	std::string getNameInternal() const;
};

#endif
